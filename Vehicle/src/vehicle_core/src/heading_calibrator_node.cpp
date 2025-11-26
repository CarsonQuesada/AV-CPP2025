#include "vehicle_core/heading_calibrator_node.hpp"
#include <cmath>
#include <limits>

namespace vehicle_core {

HeadingCalibratorNode::HeadingCalibratorNode(const rclcpp::NodeOptions& opts)
: rclcpp::Node("heading_calibrator_node", opts)
{
  std::string controller_name_ = "heading_calibrator";

  // ---- Parameters ----
  min_dist_m_         = declare_parameter("min_distance_m", 10.0);
  target_speed_mps_   = declare_parameter("target_speed_mps", 2.0);
  stationary_max_mps_ = declare_parameter("stationary_max_mps", 0.05);
  capture_time_s_     = declare_parameter("capture_time_s", 1.0);
  timeout_s_          = declare_parameter("timeout_s", 45.0);

  // ---- Pub/Sub ----
  pub_drive_ = create_publisher<vehicle_core::msg::InternalDriveCommand>(
      "/vehicle/internal_drive_cmd", rclcpp::QoS(10).reliable());

  sub_vel_ = create_subscription<geometry_msgs::msg::TwistWithCovarianceStamped>(
      "/vehicle/velocity", rclcpp::QoS(50).best_effort(),
      std::bind(&HeadingCalibratorNode::onVel, this, std::placeholders::_1));

  sub_fix_ = create_subscription<sensor_msgs::msg::NavSatFix>(
      "/fix", rclcpp::QoS(10).best_effort(),
      std::bind(&HeadingCalibratorNode::onFix, this, std::placeholders::_1));

  sub_manual_ = create_subscription<std_msgs::msg::Empty>(
      "/vehicle/events/manual_override", rclcpp::QoS(5).best_effort(),
      std::bind(&HeadingCalibratorNode::onManual, this, std::placeholders::_1));

  sub_ekf_odom_ = this->create_subscription<nav_msgs::msg::Odometry>(
      "/odometry/filtered", rclcpp::SensorDataQoS(),
      [this](const nav_msgs::msg::Odometry::SharedPtr msg){
        last_odom_ = *msg;
        have_odom_ = true;
      });

  set_pose_client_ = this->create_client<robot_localization::srv::SetPose>("/ekf_localization_node/set_pose");

  // ---- Services ----
  srv_start_ = create_service<std_srvs::srv::Trigger>(
      "/routines/heading/start",
      std::bind(&HeadingCalibratorNode::onStartSvc, this, std::placeholders::_1, std::placeholders::_2));

  srv_cancel_ = create_service<std_srvs::srv::Trigger>(
      "/routines/heading/cancel",
      std::bind(&HeadingCalibratorNode::onCancelSvc, this, std::placeholders::_1, std::placeholders::_2));

  // ---- Arbiter clients ----
  cli_req_ = create_client<vehicle_core::srv::RequestInternalControl>(
    "/drive_arbiter/request_internal_control");
  cli_rel_ = create_client<vehicle_core::srv::ReleaseInternalControl>(
    "/drive_arbiter/release_internal_control");

  // ---- Timer ----
  timer_ = create_wall_timer(std::chrono::milliseconds(50), std::bind(&HeadingCalibratorNode::onTick, this));

  RCLCPP_INFO(get_logger(), "heading_calibrator_node up");
}

// ======== ROS Callbacks ========

void HeadingCalibratorNode::onVel(geometry_msgs::msg::TwistWithCovarianceStamped::SharedPtr m) {
  rclcpp::Time t;
  if (m->header.stamp.sec != 0 || m->header.stamp.nanosec != 0)
    t = rclcpp::Time(m->header.stamp);
  else
    t = now();

  const double vx = m->twist.twist.linear.x;
  if (!vx_buf_.empty()) {
    const double dt = (t - vx_buf_.back().t).seconds();
    if (dt > 0) distance_m_ += 0.5 * (vx_buf_.back().vx + vx) * dt;
  }
  vx_buf_.push_back({t, vx});
  while (!vx_buf_.empty() && (t - vx_buf_.front().t).seconds() > 10.0)
    vx_buf_.pop_front();
}

void HeadingCalibratorNode::onFix(sensor_msgs::msg::NavSatFix::SharedPtr m) {
  if (m->status.status < sensor_msgs::msg::NavSatStatus::STATUS_FIX) return;

  rclcpp::Time t;
  if (m->header.stamp.sec != 0 || m->header.stamp.nanosec != 0)
    t = rclcpp::Time(m->header.stamp);
  else
    t = now();

  if (phase_ == Phase::CaptureA) fix_A_.push_back({t, m->latitude, m->longitude});
  if (phase_ == Phase::CaptureB) fix_B_.push_back({t, m->latitude, m->longitude});
}

void HeadingCalibratorNode::onManual(std_msgs::msg::Empty::SharedPtr) { cancel_ = true; }

void HeadingCalibratorNode::onStartSvc(
    const std::shared_ptr<std_srvs::srv::Trigger::Request>,
    std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  if (phase_ != Phase::Idle) {
    res->success = false;
    res->message = "busy";
    return;
  }
  phase_ = Phase::CaptureA;
  cancel_ = false;
  control_ = false;
  vx_buf_.clear();
  fix_A_.clear();
  fix_B_.clear();
  distance_m_ = 0.0;
  t_start_ = t_phase_ = now();
  RCLCPP_INFO(get_logger(), "[heading] start");
  res->success = true;
  res->message = "started";
}

void HeadingCalibratorNode::onCancelSvc(
    const std::shared_ptr<std_srvs::srv::Trigger::Request>,
    std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  cancel_ = true;
  res->success = true;
  res->message = "cancel requested";
}

// ======== Main Tick ========

void HeadingCalibratorNode::onTick() {
  if (phase_ == Phase::Idle || phase_ == Phase::Done) return;
  if (cancel_ || (now() - t_start_).seconds() > timeout_s_) {
    finish(false);
    return;
  }

  switch (phase_) {
    case Phase::CaptureA:
      if (stationaryFor(capture_time_s_)) {
        if ((now() - t_phase_).seconds() >= capture_time_s_) {
          phase_ = Phase::Drive;
          t_phase_ = now();
          RCLCPP_INFO(get_logger(), "[heading] A captured");
        }
      } else {
        t_phase_ = now();
      }
      break;

    case Phase::Drive:
      if (!control_ && !requestControl()) break;
      if (distance_m_ < min_dist_m_) publishDrive(target_speed_mps_, 0.0);
      else {
        publishZero();
        releaseControl();
        phase_ = Phase::CaptureB;
        t_phase_ = now();
        RCLCPP_INFO(get_logger(), "[heading] baseline reached %.1fm", distance_m_);
      }
      break;

    case Phase::CaptureB:
      publishZero();
      if ((now() - t_phase_).seconds() >= capture_time_s_) {
        const bool ok = computeAndStoreHeading();
        finish(ok);
      }
      break;
    default:
      break;
  }
}

// ======== Helpers ========

bool HeadingCalibratorNode::stationaryFor(double sec) const {
  if (vx_buf_.empty()) return false;
  double acc = 0.0;
  for (auto it = vx_buf_.rbegin(); it != vx_buf_.rend(); ++it) {
    if (std::abs(it->vx) > stationary_max_mps_) return false;
    if (it + 1 != vx_buf_.rend()) acc += (it->t - (it + 1)->t).seconds();
    if (acc >= sec) break;
  }
  return acc >= sec;
}

bool HeadingCalibratorNode::avgFix(const std::deque<Fix>& v, double& lat, double& lon) const {
  if (v.empty()) return false;
  double la = 0, lo = 0;
  for (auto& f : v) {
    la += f.lat;
    lo += f.lon;
  }
  lat = la / v.size();
  lon = lo / v.size();
  return true;
}

void HeadingCalibratorNode::ll_to_enu(double lat0, double lon0, double lat, double lon,
                                      double& ex, double& ey) const {
  constexpr double R = 6378137.0;
  constexpr double D2R = 3.14159265358979323846 / 180.0;
  const double lat0r = lat0 * D2R;
  const double dlon = (lon - lon0) * D2R;
  const double dlat = (lat - lat0) * D2R;
  ex = R * dlon * std::cos(lat0r);
  ey = R * dlat;
}

bool HeadingCalibratorNode::computeAndStoreHeading() {
  double latA, lonA, latB, lonB;
  if (!avgFix(fix_A_, latA, lonA)) return false;
  if (!avgFix(fix_B_, latB, lonB)) return false;

  double ex, ey;                       // ex = East, ey = North
  ll_to_enu(latA, lonA, latB, lonB, ex, ey);

  // Heading from North (clockwise), in radians
  const double yaw_rad = std::atan2(ex, ey);
  const double yaw_deg = yaw_rad * 180.0 / 3.14159265358979323846;

  // --- Uncertainty (yaw_sigma) ---
  // sigma_yaw = atan2(sigma_xy, L), where L = baseline length.
  const double L = std::hypot(ex, ey);
  // Start with a conservative horizontal sigma (meters) if we don't track per-fix covariance:
  double sigma_xy = declare_parameter("heading_init_sigma_xy_m", 3.0);
  // If baseline is long, uncertainty gets smaller; clamp to a minimum
  double yaw_sigma_rad = std::atan2(sigma_xy, std::max(L, 1e-6));
  const double yaw_sigma_min_deg = declare_parameter("heading_init_sigma_min_deg", 5.0);
  yaw_sigma_rad = std::max(yaw_sigma_rad, yaw_sigma_min_deg * 3.14159265358979323846 / 180.0);

  // Store (optional) and log
  set_parameter(rclcpp::Parameter("initial_heading_deg", yaw_deg));
  RCLCPP_INFO(get_logger(), "[heading] baseline=%.2fm  heading=%.1f deg  sigma≈%.1f deg",
              L, yaw_deg, yaw_sigma_rad * 180.0 / 3.14159265358979323846);

  // Apply to EKF
  set_heading(yaw_rad, yaw_sigma_rad);
  return true;
}

bool HeadingCalibratorNode::requestControl() {
  if (control_) return true;
  if (!cli_req_->service_is_ready() && !cli_req_->wait_for_service(std::chrono::seconds(1)))
    return false;

  auto req = std::make_shared<vehicle_core::srv::RequestInternalControl::Request>();
  req->controller = controller_name_;  // <-- IMPORTANT

  cli_req_->async_send_request(req,
    [this](rclcpp::Client<vehicle_core::srv::RequestInternalControl>::SharedFuture f){
      try {
        auto resp = f.get();
        if (resp && resp->success) {
          control_ = true;
          RCLCPP_INFO(get_logger(), "[heading] control granted");
        } else {
          RCLCPP_WARN(get_logger(), "[heading] control denied: %s",
                      resp ? resp->message.c_str() : "no response");
        }
      } catch (const std::exception& e) {
        RCLCPP_ERROR(get_logger(), "control request error: %s", e.what());
      }
    });
  return false; // will flip to true in the callback
}

void HeadingCalibratorNode::releaseControl() {
  if (!control_) return;
  publishZero();

  if (cli_rel_->wait_for_service(std::chrono::seconds(1))) {
    auto req = std::make_shared<vehicle_core::srv::ReleaseInternalControl::Request>();
    req->controller = controller_name_;
    (void)cli_rel_->async_send_request(req);
  } else {
    RCLCPP_WARN(get_logger(), "[heading] release service not available");
  }
  control_ = false;
}

void HeadingCalibratorNode::publishDrive(double v, double steer) {
  vehicle_core::msg::InternalDriveCommand m;
  m.stamp = now();
  m.controller = controller_name_;
  m.brake = 0;
  m.gear = 2; // Forward
  m.speed_mps = v;
  m.steer_rad = steer;
  pub_drive_->publish(m);
}

void HeadingCalibratorNode::publishZero() { publishDrive(0.0, 0.0); }

void HeadingCalibratorNode::finish(bool ok) {
  publishZero();
  releaseControl();
  phase_ = Phase::Idle;
  if (ok) {
    RCLCPP_INFO(get_logger(), "[heading] done");
  } else {
    RCLCPP_WARN(get_logger(), "[heading] failed/canceled");
  }
}

void HeadingCalibratorNode::set_heading(double yaw_rad, double yaw_sigma_rad) {
  if (!have_odom_) {
    RCLCPP_ERROR(this->get_logger(), "No /odometry/filtered yet; cannot set heading.");
    return;
  }
  if (!set_pose_client_->wait_for_service(std::chrono::seconds(2))) {
    RCLCPP_ERROR(this->get_logger(), "EKF set_pose service not available.");
    return;
  }

  auto req = std::make_shared<robot_localization::srv::SetPose::Request>();
  auto& p = req->pose;

  p.header.stamp = this->now();
  p.header.frame_id = "map";                 // use your EKF world frame

  // Keep current EKF position (don’t overwrite x/y/z)
  p.pose.pose.position = last_odom_.pose.pose.position;

  // Replace orientation with your new yaw
  tf2::Quaternion q; q.setRPY(0.0, 0.0, yaw_rad);
  p.pose.pose.orientation.x = q.x();
  p.pose.pose.orientation.y = q.y();
  p.pose.pose.orientation.z = q.z();
  p.pose.pose.orientation.w = q.w();

  // Covariance: set only yaw variance (others zero)
  for (double &c : p.pose.covariance) c = 0.0;
  p.pose.covariance[35] = yaw_sigma_rad * yaw_sigma_rad; // yaw on [5,5]

  (void)set_pose_client_->async_send_request(req); // fire-and-forget
}

rclcpp::Time HeadingCalibratorNode::now() { return get_clock()->now(); }

}  // namespace vehicle_core

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::HeadingCalibratorNode)
