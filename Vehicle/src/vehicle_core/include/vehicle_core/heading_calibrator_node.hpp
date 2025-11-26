#pragma once

// heading_calibrator_node.hpp
// This class implements a heading calibration routine for the vehicle.
// It captures GPS fixes at two points separated by a drive segment,
// computes the heading based on the displacement, and sets the EKF's
// heading accordingly.
// 
// Requirements:
// - Access to GPS fixes and velocity data.
// 
// Current issues:
// - Untested
// - does not allow cancellation with the UI button. Cancellation should
//   be possible with manual override or client disconnection.
// 

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <std_msgs/msg/empty.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <geometry_msgs/msg/twist_with_covariance_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <robot_localization/srv/set_pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include "vehicle_core/msg/internal_drive_command.hpp"
#include "vehicle_core/srv/request_internal_control.hpp"
#include "vehicle_core/srv/release_internal_control.hpp"

#include <deque>

namespace vehicle_core {

class HeadingCalibratorNode : public rclcpp::Node {
public:
  explicit HeadingCalibratorNode(const rclcpp::NodeOptions& opts = rclcpp::NodeOptions());

private:
  // ===== Data types =====
  struct Vel { rclcpp::Time t; double vx; };
  struct Fix { rclcpp::Time t; double lat; double lon; };

  enum class Phase { Idle, CaptureA, Drive, CaptureB, Done };

  // ===== Callbacks =====
  void onVel(geometry_msgs::msg::TwistWithCovarianceStamped::SharedPtr m);
  void onFix(sensor_msgs::msg::NavSatFix::SharedPtr m);
  void onManual(std_msgs::msg::Empty::SharedPtr);
  void onTick();
  void onStartSvc(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                  std::shared_ptr<std_srvs::srv::Trigger::Response> res);
  void onCancelSvc(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                   std::shared_ptr<std_srvs::srv::Trigger::Response> res);

  // ===== Helpers =====
  bool stationaryFor(double sec) const;
  bool avgFix(const std::deque<Fix>& v, double& lat, double& lon) const;
  void ll_to_enu(double lat0, double lon0, double lat, double lon, double& ex, double& ey) const;
  bool computeAndStoreHeading();
  bool requestControl();
  void releaseControl();
  void publishDrive(double v, double steer);
  void publishZero();
  void finish(bool ok);
  void set_heading(double yaw_rad, double yaw_sigma_rad);
  rclcpp::Time now();

  // ===== ROS =====
  rclcpp::Publisher<vehicle_core::msg::InternalDriveCommand>::SharedPtr pub_drive_;
  rclcpp::Subscription<geometry_msgs::msg::TwistWithCovarianceStamped>::SharedPtr sub_vel_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_ekf_odom_;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr sub_fix_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr sub_manual_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_start_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_cancel_;
  rclcpp::Client<vehicle_core::srv::RequestInternalControl>::SharedPtr cli_req_;
  rclcpp::Client<vehicle_core::srv::ReleaseInternalControl>::SharedPtr cli_rel_;
  rclcpp::Client<robot_localization::srv::SetPose>::SharedPtr set_pose_client_;
  rclcpp::TimerBase::SharedPtr timer_;

  // ===== Params =====
  double min_dist_m_, target_speed_mps_, stationary_max_mps_, capture_time_s_, timeout_s_;

  // ===== Buffers & State =====
  std::deque<Vel> vx_buf_;
  std::deque<Fix> fix_A_, fix_B_;
  double distance_m_{0.0};
  bool cancel_{false}, control_{false};
  Phase phase_{Phase::Idle};
  rclcpp::Time t_start_, t_phase_;
  nav_msgs::msg::Odometry last_odom_;
  bool have_odom_ = false;
  std::string controller_name_ {"heading_calibrator"};
};

} // namespace vehicle_core
