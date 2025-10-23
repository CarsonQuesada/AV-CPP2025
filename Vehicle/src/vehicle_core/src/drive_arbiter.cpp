#include "vehicle_core/drive_arbiter_node.hpp"

#include <algorithm>
#include <cmath>

using namespace vehicle_core;

static inline uint8_t clamp_u8(int v)   { return static_cast<uint8_t>(std::clamp(v, 0, 100)); }
static inline int16_t clamp_i16(int v)  { return static_cast<int16_t>(std::clamp(v, -32768, 32767)); }

DriveArbiterNode::DriveArbiterNode(const rclcpp::NodeOptions& opts)
: rclcpp::Node("drive_arbiter_node", opts)
{
  // Params
  top_speed_mps_         = this->declare_parameter<double>("vehicle.top_speed_mps", 12.0);
  steer_max_rad_         = this->declare_parameter<double>("steer.max_rad", 0.5);
  override_deadband_     = this->declare_parameter<int>("override.deadband_percent", 2);
  publish_when_inactive_ = this->declare_parameter<bool>("publish_when_inactive", false);

  // Subs
  sub_mode_ = this->create_subscription<msg::StateMode>("/vehicle/state_mode", 10,
      std::bind(&DriveArbiterNode::onStateMode, this, std::placeholders::_1));

  sub_ap_ = this->create_subscription<msg::AutopilotDriveCommand>("/vehicle/autopilot_drive_cmd", 10,
      std::bind(&DriveArbiterNode::onAP, this, std::placeholders::_1));

  sub_manual_ = this->create_subscription<msg::ManualDriveCommand>("/vehicle/manual_drive_cmd", 10,
      std::bind(&DriveArbiterNode::onManual, this, std::placeholders::_1));

  sub_max_ = this->create_subscription<msg::MaxSpeed>("/vehicle/max_speed", 10,
      std::bind(&DriveArbiterNode::onMaxSpeed, this, std::placeholders::_1));

  // Pubs
  pub_target_ = this->create_publisher<msg::DriveTarget>("/vehicle/drive_target", 10);
  pub_override_evt_ = this->create_publisher<std_msgs::msg::Empty>("/vehicle/events/manual_override", 1);

  // Service client (optional)
  req_mode_client_ = this->create_client<std_srvs::srv::Trigger>("/state_manager/request_manual");

  RCLCPP_INFO(get_logger(), "drive_arbiter_node up. top_speed=%.3f m/s steer_max=%.3f rad",
              top_speed_mps_, steer_max_rad_);
}

void DriveArbiterNode::onStateMode(const msg::StateMode::SharedPtr m) {
  last_mode_ = m;
  maybePublish();
}
void DriveArbiterNode::onAP(const msg::AutopilotDriveCommand::SharedPtr m) {
  last_ap_ = m;
  maybePublish();
}
void DriveArbiterNode::onManual(const msg::ManualDriveCommand::SharedPtr m) {
  if (last_mode_ && last_mode_->mode == 3 /*AUTO*/ && manualIsMeaningful(*m)) {
    std_msgs::msg::Empty e;
    pub_override_evt_->publish(e);
    if (req_mode_client_ && req_mode_client_->service_is_ready()) {
      auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
      (void)req_mode_client_->async_send_request(req);
    } else {
      RCLCPP_WARN_THROTTLE(get_logger(), *this->get_clock(), 2000, "request_manual service not ready");
    }
  }
  last_manual_ = m;
  maybePublish();
}
void DriveArbiterNode::onMaxSpeed(const msg::MaxSpeed::SharedPtr m) {
  max_speed_percent_ = std::clamp<uint8_t>(m->percent, 0, 100);
  maybePublish();
}

bool DriveArbiterNode::manualIsMeaningful(const msg::ManualDriveCommand& m) const {
  if (m.brake > 0) return true;
  const int db = override_deadband_;
  if (m.speed > db) return true;
  if (m.steer > (50 + db) || m.steer < (50 - db)) return true;
  return false;
}

// ---- helpers: limits / conversions ----

int16_t DriveArbiterNode::capSpeedMmpsSigned(double mmps_signed) const {
  // Apply global cap AND MaxSpeed percent (cap applies to magnitude; sign preserved)
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
static inline int gearSign(uint8_t gear /*GearID*/) {
  // 0=NoInput,1=Coast,2=Forward,3=Reverse
  if (gear == 3) return -1;
  if (gear == 2) return +1;
  return 0; // NoInput or Coast -> zero speed target
}

// percent(0..100) -> signed mm/s using MaxSpeed cap and gear sign
int16_t DriveArbiterNode::manualPercentToMmpsSigned(uint8_t speed_percent, uint8_t gear) const {
  const int sgn = gearSign(gear);
  if (sgn == 0) return 0;
  const double abs_cap = std::max(0.0, top_speed_mps_ * 1000.0 *
                                         (max_speed_percent_ / 100.0));
  const double mmps = (std::clamp<int>(speed_percent, 0, 100) / 100.0) * abs_cap;
  return capSpeedMmpsSigned(sgn * mmps);
}
// percent steer (0..100, 50=center) -> signed mrad
int16_t DriveArbiterNode::percentSteerToMradSigned(uint8_t steer_percent) const {
  const double x = (static_cast<int>(steer_percent) - 50) / 50.0; // -1..+1
  const double max_mrad = steer_max_rad_ * 1000.0;
  return capSteerMradSigned(x * max_mrad);
}

// ---- publish decision ----
void DriveArbiterNode::maybePublish() {
  if (!last_mode_) return;

  const uint8_t mode = last_mode_->mode;
  const bool active = (mode == 1 /*MANUAL*/ || mode == 3 /*AUTO*/);
  if (!active && !publish_when_inactive_) return;

  msg::DriveTarget out{};
  out.brake_percent = 0;
  out.target_speed_mmps = 0;
  out.target_steer_millirad = 0;

  bool use_manual = (mode == 1 /*MANUAL*/);
  if (mode == 3 /*AUTO*/ && last_manual_ && manualIsMeaningful(*last_manual_)) {
    use_manual = true; // immediate feel
  }

  if (use_manual && last_manual_) {
    const auto& m = *last_manual_;
    out.brake_percent = clamp_u8(m.brake);

    if (out.brake_percent > 0) {
      out.target_speed_mmps = 0;
    } else {
      out.target_speed_mmps = manualPercentToMmpsSigned(m.speed, m.gear /*GearID*/);
    }
    out.target_steer_millirad = percentSteerToMradSigned(m.steer);
  }
  else if (!use_manual && last_ap_) {
    const auto& a = *last_ap_;
    out.brake_percent = clamp_u8(a.brake);

    if (out.brake_percent > 0) {
      out.target_speed_mmps = 0;
    } else {
      // speed_mps * 1000 with sign based on AP gear
      const int sgn = gearSign(a.gear);
      const double mmps_signed = (sgn == 0) ? 0.0 : (sgn * (static_cast<double>(a.speed_mps) * 1000.0));
      out.target_speed_mmps = capSpeedMmpsSigned(mmps_signed);
    }

    out.target_steer_millirad = capSteerMradSigned(static_cast<double>(a.steer_rad) * 1000.0);
  }

  pub_target_->publish(out);
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::DriveArbiterNode)