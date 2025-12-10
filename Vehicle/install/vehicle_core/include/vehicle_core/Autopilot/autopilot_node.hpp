#pragma once

// autopilot_node.hpp
// This class implements the autopilot functionality, generating internal drive commands
// based on odometry data and a predefined path.
//
// Requirements:
// - Path file in KML format specifying waypoints for the vehicle to follow.
// - Path should be in data folder and specified as a paramter in the launch file.
//
// Current issues:
// - No obstacle detection yet
// - This node is untested
//
// Notes:
// - Relies on the ekf node for odometry data. Though the ekf publishes pose, and 
//   heading it has not been tested to see if it is accurate.

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <std_srvs/srv/trigger.hpp>
#include "vehicle_core/msg/internal_drive_command.hpp"
#include "vehicle_core/srv/request_internal_control.hpp"
#include "vehicle_core/srv/release_internal_control.hpp"

#include <vector>

#include "PurePursuit.hpp"
#include "KmlPathLoader.hpp"

namespace vehicle_core {

class AutopilotNode : public rclcpp::Node {
public:
  explicit AutopilotNode(const rclcpp::NodeOptions& opts = rclcpp::NodeOptions());

  private:
  // Publishers
  rclcpp::Publisher<vehicle_core::msg::InternalDriveCommand>::SharedPtr pub_drive_;

  // Subscribers
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr sub_odom_;

  // Services
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_start_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_cancel_;

  // Clients
  rclcpp::Client<vehicle_core::srv::RequestInternalControl>::SharedPtr cli_req_;
  rclcpp::Client<vehicle_core::srv::ReleaseInternalControl>::SharedPtr cli_rel_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_notify_ready_;

  // Subscription handlers
  void onOdom(const nav_msgs::msg::Odometry::SharedPtr msg);

  // Service handlers
  void handleStart(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
    std::shared_ptr<std_srvs::srv::Trigger::Response> res);
  void handleCancel(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> req,
    std::shared_ptr<std_srvs::srv::Trigger::Response> res);

  // Core functionality
  void generateDriveCommand();
  bool startAutopilot();
  void stopAutopilot();
  bool requestControl();
  void releaseControl();
  void notifyReady();

  // Helpers
  void publishDrive(double speed, double steer);
  void publishZero();

  // Params
  double control_rate_hz_;
  double wheelbase_m_{1.0};

  // For generating drive commands
  PurePursuit pure_pursuit_;
  nav_msgs::msg::Odometry::SharedPtr last_odom_;

  // Other
  rclcpp::TimerBase::SharedPtr control_timer_;
  const std::string controller_name_{"autopilot"};
  bool cancel_{false}, control_{false}, autopilot_active_{false};
  KmlPathLoader loader_;
  std::string kml_path_;
  bool ready_notified_{false};
  rclcpp::CallbackGroup::SharedPtr control_cb_group_;
};

}  // namespace vehicle_core