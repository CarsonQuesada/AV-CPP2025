#include "vehicle_core/drive_arbiter_node.hpp"
#include <rclcpp_components/register_node_macro.hpp>
#include <algorithm>
#include <cmath>

using namespace vehicle_core;

static inline uint8_t clamp_u8(int v)  { return static_cast<uint8_t>(std::clamp(v, 0, 100)); }
static inline int16_t clamp_i16(int v) { return static_cast<int16_t>(std::clamp(v, -32768, 32767)); }

DriveArbiterNode::DriveArbiterNode(const rclcpp::NodeOptions& opts)
: rclcpp::Node("drive_arbiter_node", opts)
{
  // ---- Params ----
  top_speed_mps_         = declare_parameter<double>("vehicle.top_speed_mps", 12.0);
  steer_max_rad_         = declare_parameter<double>("steer.max_rad", 0.5);
  override_deadband_     = declare_parameter<int>("override.deadband_percent", 2);
  publish_when_inactive_ = declare_parameter<bool>("publish_when_inactive", false);


 // Obstacle detection parameters
  emergency_zone_ = 1.0f;
  slow_down_zone_ = 2.0f;
  warning_zone_ = 6.0f;
  speed_reduction_factor_ = 0.5f;
  warning_speed_factor_ = 0.8f;

  // Initialize angle zone
  closest_angle_zone_ = "ignore_angle";

  RCLCPP_INFO(get_logger(), "Obstacle zones: Emergency=%.1fm Slow=%.1fm Warning=%.1fm",
            emergency_zone_, slow_down_zone_, warning_zone_);

  // ---- Subs ----
  sub_mode_ = create_subscription<msg::StateMode>(
      "/vehicle/state_mode", 10,
      std::bind(&DriveArbiterNode::onStateMode, this, std::placeholders::_1));

  sub_internal_ = create_subscription<msg::InternalDriveCommand>(
      "/vehicle/internal_drive_cmd", 10,
      std::bind(&DriveArbiterNode::onInternal, this, std::placeholders::_1));

  sub_manual_ = create_subscription<msg::ManualDriveCommand>(
      "/vehicle/manual_drive_cmd", 10,
      std::bind(&DriveArbiterNode::onManual, this, std::placeholders::_1));

  sub_max_ = create_subscription<msg::MaxSpeed>(
      "/vehicle/max_speed_cmd", 10,
      std::bind(&DriveArbiterNode::onMaxSpeed, this, std::placeholders::_1));
  ////////////////////////////////////////////////////////////////////////////////////////
   sub_obstacle_ = create_subscription<std_msgs::msg::Bool>(
      "/sensors/obstacle_detected", 10,
      [this](const std_msgs::msg::Bool::SharedPtr msg) {
        this->onObstacleDetected(msg);
      });

    sub_obstacle_distance_ = create_subscription<std_msgs::msg::Float32>(
      "/sensors/closest_object_distance", 10,
      [this](const std_msgs::msg::Float32::SharedPtr msg) {
        this->onObstacleDistance(msg);
      });

    sub_obstacle_angle_ = create_subscription<std_msgs::msg::String>(
        "/sensors/closest_object_angle_zone", 10,
        [this](const std_msgs::msg::String::SharedPtr msg) {
          this->onObstacleAngleZone(msg);
        });

  ////////////////////////////////////////////////////////////////////////////////////////

  // ---- Pubs ----
  pub_target_ = create_publisher<msg::DriveTarget>("/vehicle/drive_target", 10);
  pub_override_evt_ = create_publisher<std_msgs::msg::Empty>("/vehicle/events/manual_override", 1);
  ////////////////////////////////////////////////////////////////////////////////

  pub_emergency_stop_evt_ = create_publisher<std_msgs::msg::Empty>("/vehicle/events/emergency_stop", 1);  
  
  ////////////////////////////////////////////////////////////////////////////////

  // ---- Services ----
  using vehicle_core::srv::RequestInternalControl;
  using vehicle_core::srv::ReleaseInternalControl;
  srv_req_internal_ctrl_ = create_service<RequestInternalControl>(
    "/drive_arbiter/request_internal_control",
    [this](
      const std::shared_ptr<RequestInternalControl::Request> req,
      std::shared_ptr<RequestInternalControl::Response> res)
    {
      const std::string& who = req->controller;
      if (grant_owner_.empty() || grant_owner_ == who) {
        const bool first = grant_owner_.empty();
        grant_owner_ = who;
        res->success = true;
        res->message = "granted to " + who;
        if (first) RCLCPP_INFO(get_logger(), "Internal control GRANTED to %s", who.c_str());
        internal_control_ = true;
      } else {
        res->success = false;
        res->message = "busy (owned by " + grant_owner_ + ")";
        RCLCPP_WARN(get_logger(), "Grant denied: %s requested, owned by %s",
                    who.c_str(), grant_owner_.c_str());
        internal_control_ = false;
      }
    });

  srv_rel_internal_ctrl_ = create_service<ReleaseInternalControl>(
    "/drive_arbiter/release_internal_control",
    [this](
      const std::shared_ptr<ReleaseInternalControl::Request> req,
      std::shared_ptr<ReleaseInternalControl::Response> res)
    {
      const std::string& who = req->controller;
      if (!grant_owner_.empty() && grant_owner_ == who) {
        grant_owner_.clear();
        res->success = true;
        res->message = "released by " + who;
        RCLCPP_INFO(get_logger(), "Internal control RELEASED by %s", who.c_str());
        msg::DriveTarget z{}; pub_target_->publish(z);
      } else {
        res->success = false;
        res->message = grant_owner_.empty()
          ? "no owner"
          : "owner is " + grant_owner_ + ", not " + who;
        RCLCPP_WARN(get_logger(), "Release denied by %s (owner=%s)",
                    who.c_str(), grant_owner_.c_str());
      }
    });

  req_mode_client_ = create_client<std_srvs::srv::Trigger>("/state_manager/request_manual");

  RCLCPP_INFO(get_logger(), "drive_arbiter_node up: top_speed=%.2f m/s steer_max=%.2f rad",
              top_speed_mps_, steer_max_rad_);
}

// ---------------- Callbacks ----------------

void DriveArbiterNode::onStateMode(const msg::StateMode::SharedPtr m) {
  last_mode_ = m;
  maybePublish();
}

void DriveArbiterNode::onInternal(const msg::InternalDriveCommand::SharedPtr m) {
  last_internal_ = m;
  maybePublish();
}

void DriveArbiterNode::onManual(const msg::ManualDriveCommand::SharedPtr m) {
  const bool in_auto = last_mode_ && last_mode_->mode == 3 /*AUTO*/;
  const bool meaningful = manualIsMeaningful(*m);

  if (meaningful && internal_control_) {
    internal_control_ = false;
    std_msgs::msg::Empty e; pub_override_evt_->publish(e);
    if (req_mode_client_ && req_mode_client_->service_is_ready()) {
      auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
      req_mode_client_->async_send_request(req);
    }
    RCLCPP_INFO(get_logger(), "Manual override: internal control revoked");
  } else if (meaningful && in_auto) {
    std_msgs::msg::Empty e; pub_override_evt_->publish(e);
    if (req_mode_client_->service_is_ready()) {
      auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
      req_mode_client_->async_send_request(req);
    }
  }

  last_manual_ = m;
  maybePublish();
}

void DriveArbiterNode::onMaxSpeed(const msg::MaxSpeed::SharedPtr m) {
  max_speed_percent_ = std::clamp<uint8_t>(m->percent, 0, 100);
  maybePublish();
}

/////////////////////////////////////////////////////////////////////////////////////////

//Obstacle detection callback
void DriveArbiterNode::onObstacleDetected(const std_msgs::msg::Bool::SharedPtr msg) {
  if (msg->data && !obstacle_detected_) {
    // Only trigger emergency stop if object is in emergency angle zone
    if (closest_angle_zone_ == "emergency_angle") {
      triggerEmergencyStop();
      RCLCPP_WARN(get_logger(), "OBSTACLE DETECTED in emergency angle zone! Emergency stop activated.");
    } else if (closest_angle_zone_ == "caution_angle") {
      // Caution zone objects don't trigger emergency stop, just speed reduction
      RCLCPP_WARN(get_logger(), "OBSTACLE DETECTED in caution angle zone. Speed will be reduced.");
      obstacle_detected_ = true;  // Flag for speed reduction but not emergency stop
    }
  } else if (!msg->data && obstacle_detected_) {
    // Obstacle cleared
    obstacle_detected_ = false;
    RCLCPP_INFO(get_logger(), "Obstacle zone cleared.");
  }
}



void DriveArbiterNode::onObstacleDistance(const std_msgs::msg::Float32::SharedPtr msg) {
  closest_object_distance_ = msg->data;
  
  // Log zone changes for debugging
  static float last_logged_distance = 0.0f;
  static std::string last_zone = "";
  
  if (abs(closest_object_distance_ - last_logged_distance) > 0.1f || closest_angle_zone_ != last_zone) {
    if (closest_object_distance_ <= emergency_zone_) {
      if (closest_angle_zone_ == "emergency_angle") {
        RCLCPP_WARN(get_logger(), "Object in EMERGENCY zone: %.2fm in %s zone", 
                   closest_object_distance_, closest_angle_zone_.c_str());
      } else if (closest_angle_zone_ == "caution_angle") {
        RCLCPP_WARN(get_logger(), "Object in CAUTION zone: %.2fm in %s zone", 
                   closest_object_distance_, closest_angle_zone_.c_str());
      }
    } else if (closest_object_distance_ <= slow_down_zone_) {
      RCLCPP_WARN(get_logger(), "Object in SLOW DOWN zone: %.2fm in %s zone", 
                 closest_object_distance_, closest_angle_zone_.c_str());
    } else if (closest_object_distance_ <= warning_zone_) {
      RCLCPP_INFO(get_logger(), "Object in WARNING zone: %.2fm in %s zone", 
                 closest_object_distance_, closest_angle_zone_.c_str());
    }
    last_logged_distance = closest_object_distance_;
    last_zone = closest_angle_zone_;
  }
}

void DriveArbiterNode::onObstacleAngleZone(const std_msgs::msg::String::SharedPtr msg) {
  closest_angle_zone_ = msg->data;
  RCLCPP_DEBUG(get_logger(), "Obstacle angle zone: %s", closest_angle_zone_.c_str());
}

// ---------------- Graduated Speed Reduction ----------------

float DriveArbiterNode::calculateSpeedReductionFactor(float distance) const {
  if (distance <= emergency_zone_) {
    return 0.0f; // Full stop
  } else if (distance <= slow_down_zone_) {
    // Linear interpolation between full reduction and warning reduction
    float t = (distance - emergency_zone_) / (slow_down_zone_ - emergency_zone_);
    return speed_reduction_factor_ + (warning_speed_factor_ - speed_reduction_factor_) * t;
  } else if (distance <= warning_zone_) {
    // Linear interpolation between warning reduction and normal speed
    float t = (distance - slow_down_zone_) / (warning_zone_ - slow_down_zone_);
    return warning_speed_factor_ + (1.0f - warning_speed_factor_) * t;
  } else {
    return 1.0f; // Normal speed
  }
}

void DriveArbiterNode::applySpeedReduction(msg::DriveTarget& out, float distance) {
  // Apply different logic based on angle zone
  if (closest_angle_zone_ == "emergency_angle") {
    // Objects directly in front get full graduated response
    if (distance <= emergency_zone_) {
      // Emergency stop - full brake
      out.brake_percent = 100;
      out.target_speed_mmps = 0;
      if (!obstacle_detected_) {
        obstacle_detected_ = true;
        triggerEmergencyStop();
      }
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 1000,
                          "EMERGENCY STOP: Object at %.2fm directly in front", distance);
    } else if (distance <= warning_zone_) {
      // Graduated speed reduction for front objects
      float reduction_factor = calculateSpeedReductionFactor(distance);
      
      if (distance <= slow_down_zone_) {
        RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 1000,
                            "SLOWING DOWN: Object at %.2fm directly in front, speed reduced to %.0f%%",
                            distance, reduction_factor * 100);
      } else {
        RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000,
                            "WARNING: Object at %.2fm directly in front, speed reduced to %.0f%%",
                            distance, reduction_factor * 100);
      }
      
      // Apply speed reduction
      out.target_speed_mmps = static_cast<int16_t>(out.target_speed_mmps * reduction_factor);
    }
  } 
  else if (closest_angle_zone_ == "caution_angle") {
    // Objects at sides get more aggressive reduction
    if (distance <= emergency_zone_) {
      // Side objects in emergency zone get strong braking but not full emergency stop
      out.brake_percent = 80;  // Strong brake but not 100%
      out.target_speed_mmps = static_cast<int16_t>(out.target_speed_mmps * 0.2f);  // 20% speed
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 1000,
                          "CAUTION: Object at %.2fm at side, strong braking applied", distance);
    } else if (distance <= warning_zone_) {
      // Apply more aggressive reduction for side objects
      float reduction_factor = calculateSpeedReductionFactor(distance) * 0.7f;  // 30% extra reduction
      
      if (distance <= slow_down_zone_) {
        RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 1000,
                            "CAUTION: Object at %.2fm at side, aggressive speed reduction to %.0f%%",
                            distance, reduction_factor * 100);
      } else {
        RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 1000,
                            "WARNING: Object at %.2fm at side, speed reduced to %.0f%%",
                            distance, reduction_factor * 100);
      }
      
      out.target_speed_mmps = static_cast<int16_t>(out.target_speed_mmps * reduction_factor);
    }
  }
  // Ignore objects in "ignore_angle" zone - no speed reduction
}

//////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Emergency stop function
void DriveArbiterNode::triggerEmergencyStop() {
  obstacle_detected_ = true;
  internal_control_ = false;  // Revoke autonomous control
  
  // Publish emergency stop event
  std_msgs::msg::Empty e;
  pub_emergency_stop_evt_->publish(e);
  
  // Immediately publish stop command
  msg::DriveTarget stop_cmd{};
  stop_cmd.brake_percent = 100;
  stop_cmd.target_speed_mmps = 0;
  stop_cmd.target_steer_millirad = 0;
  pub_target_->publish(stop_cmd);
  
  RCLCPP_ERROR(get_logger(), "EMERGENCY STOP: Obstacle detected!");
}
///////////////////////////////////////////////////////////////////////////////

// ---------------- Helpers ----------------

bool DriveArbiterNode::manualIsMeaningful(const msg::ManualDriveCommand& m) const {
  if (m.brake > 0) return true;
  const int db = override_deadband_;
  if (m.speed > db) return true;
  if (m.steer > (50 + db) || m.steer < (50 - db)) return true;
  return false;
}

static inline int gearSign(uint8_t gear) {
  if (gear == 3) return -1; // Reverse
  if (gear == 2) return +1; // Forward
  return 0;
}

// ---------------- Drive selection ----------------
void DriveArbiterNode::maybePublish() {
  if (!last_mode_) return;

  const uint8_t mode = last_mode_->mode;
  const bool active_like =
      (mode == 1 /*MANUAL*/ || mode == 3 /*AUTO*/ || internal_control_);
  if (!active_like && !publish_when_inactive_) return;

  msg::DriveTarget out{};
  out.brake_percent = 0;
  out.target_speed_mmps = 0;
  out.target_steer_millirad = 0;

  // Internal if we have control and not overridden by manual
  bool use_manual = (last_manual_ && manualIsMeaningful(*last_manual_));
  bool use_internal = (!use_manual && !grant_owner_.empty() && last_internal_ != nullptr);

  if (use_manual && last_manual_) {
    const auto& m = *last_manual_;
    out.brake_percent = clamp_u8(m.brake);
    if (out.brake_percent > 0)
      out.target_speed_mmps = 0;
    else
      out.target_speed_mmps = manualPercentToMmpsSigned(m.speed, m.gear);
    out.target_steer_millirad = percentSteerToMradSigned(m.steer);
    
    // Apply graduated speed reduction for manual mode too
    if (closest_object_distance_ <= warning_zone_ && out.target_speed_mmps > 0) {
      float reduction_factor = calculateSpeedReductionFactor(closest_object_distance_);
      out.target_speed_mmps = static_cast<int16_t>(out.target_speed_mmps * reduction_factor);
      
      if (closest_object_distance_ <= emergency_zone_) {
        out.brake_percent = 100;
        out.target_speed_mmps = 0;
        triggerEmergencyStop();
      }
    }
  }
  else if (use_internal) {
    const auto& cmd = *last_internal_;
    out.brake_percent = clamp_u8(cmd.brake);
    if (out.brake_percent > 0) {
      out.target_speed_mmps = 0;
    } else {
      const int sgn = gearSign(cmd.gear);
      const double mmps_signed = sgn * (cmd.speed_mps * 1000.0);
      out.target_speed_mmps = capSpeedMmpsSigned(mmps_signed);
    }
    out.target_steer_millirad = capSteerMradSigned(cmd.steer_rad * 1000.0);
    
    // Apply graduated speed reduction based on obstacle distance
    if (closest_object_distance_ <= warning_zone_ && out.target_speed_mmps > 0) {
      applySpeedReduction(out, closest_object_distance_);
    }
  }

  // Apply emergency stop if obstacle detected (overrides everything)
  if (obstacle_detected_ && out.target_speed_mmps >= 0) {
    out.brake_percent = 100;
    out.target_speed_mmps = 0;
  }

  pub_target_->publish(out);
}

// ---------------- Mapping helpers ----------------

int16_t DriveArbiterNode::capSpeedMmpsSigned(double mmps_signed) const {
  const double cap_abs = std::max(0.0, top_speed_mps_ * 1000.0 *
                                  (std::max<uint8_t>(1, max_speed_percent_) / 100.0));
  const double s = std::clamp(mmps_signed, -cap_abs, cap_abs);
  return clamp_i16(static_cast<int>(std::lround(s)));
}

int16_t DriveArbiterNode::capSteerMradSigned(double mrad_signed) const {
  const double max_mrad = std::max(0.0, steer_max_rad_ * 1000.0);
  const double s = std::clamp(mrad_signed, -max_mrad, max_mrad);
  return clamp_i16(static_cast<int>(std::lround(s)));
}

int16_t DriveArbiterNode::manualPercentToMmpsSigned(uint8_t speed_percent, uint8_t gear) const {
  const int sgn = gearSign(gear);
  if (sgn == 0) return 0;
  const double abs_cap = std::max(0.0, top_speed_mps_ * 1000.0 *
                                  (max_speed_percent_ / 100.0));
  const double mmps = (std::clamp<int>(speed_percent, 0, 100) / 100.0) * abs_cap;
  return capSpeedMmpsSigned(sgn * mmps);
}

int16_t DriveArbiterNode::percentSteerToMradSigned(uint8_t steer_percent) const {
  const double x = (static_cast<int>(steer_percent) - 50) / 50.0; // -1..+1
  const double max_mrad = steer_max_rad_ * 1000.0;
  return capSteerMradSigned(x * max_mrad);
}


RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::DriveArbiterNode)
