#pragma once

// DriveArbiterNode.hpp
// This class arbitrates between internal autopilot commands and manual driver commands
// to produce a final DriveTarget command for the vehicle to follow.

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/empty.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_srvs/srv/trigger.hpp>

#include "vehicle_core/msg/internal_drive_command.hpp"
#include "vehicle_core/msg/manual_drive_command.hpp"
#include "vehicle_core/msg/drive_target.hpp"
#include "vehicle_core/msg/max_speed.hpp"
#include "vehicle_core/msg/state_mode.hpp"
#include "vehicle_core/srv/request_internal_control.hpp"
#include "vehicle_core/srv/release_internal_control.hpp"

namespace vehicle_core {

class DriveArbiterNode final : public rclcpp::Node {
public:
  explicit DriveArbiterNode(const rclcpp::NodeOptions& opts = rclcpp::NodeOptions());

private:
  // ---- Callbacks ----
  void onStateMode(const msg::StateMode::SharedPtr m);
  void onInternal(const msg::InternalDriveCommand::SharedPtr m);
  void onManual(const msg::ManualDriveCommand::SharedPtr m);
  void onMaxSpeed(const msg::MaxSpeed::SharedPtr m);
  void onObstacleDetected(const std_msgs::msg::Bool::SharedPtr msg);
  void onObstacleDistance(const std_msgs::msg::Float32::SharedPtr msg);
  void onObstacleAngleZone(const std_msgs::msg::String::SharedPtr msg);  
  // ---- Core ----
  void maybePublish();                           // decide source & emit DriveTarget
  bool manualIsMeaningful(const msg::ManualDriveCommand& m) const;
  void triggerEmergencyStop();
  float calculateSpeedReductionFactor(float distance) const;
  void applySpeedReduction(msg::DriveTarget& out, float distance);

  // ---- Mapping & clamp helpers ----
  int16_t capSpeedMmpsSigned(double mmps_signed) const;
  int16_t capSteerMradSigned(double mrad_signed) const;
  int16_t manualPercentToMmpsSigned(uint8_t speed_percent, uint8_t gear) const;
  int16_t percentSteerToMradSigned(uint8_t steer_percent) const;

  // ---- Params ----
  double top_speed_mps_;        // YAML param
  double steer_max_rad_;        // YAML param
  uint8_t override_deadband_;   // YAML param [percent]
  bool publish_when_inactive_;  // YAML param
  
  // Obstacle detection parameters - HARDCODED
  float emergency_zone_;      // meters - full stop
  float slow_down_zone_;      // meters - reduce speed
  float warning_zone_;        // meters - warn but maintain speed
  float speed_reduction_factor_; // Reduce speed to 50% in slow zone
  float warning_speed_factor_;   // Reduce speed to 80% in warning zone
  
  uint8_t max_speed_percent_{100}; // runtime cap from MaxSpeed topic
  std::string grant_owner_;
  std::string closest_angle_zone_;
  // ---- State ----
  msg::StateMode::SharedPtr last_mode_;
  msg::InternalDriveCommand::SharedPtr last_internal_;
  msg::ManualDriveCommand::SharedPtr   last_manual_;

  bool internal_control_{true};   // always allowed by default
  bool manual_active_{false};
  bool obstacle_detected_{false};
  float closest_object_distance_{0.0f};  // Distance to closest object

  // ---- ROS I/O ----
  rclcpp::Subscription<msg::StateMode>::SharedPtr sub_mode_;
  rclcpp::Subscription<msg::InternalDriveCommand>::SharedPtr sub_internal_;
  rclcpp::Subscription<msg::ManualDriveCommand>::SharedPtr sub_manual_;
  rclcpp::Subscription<msg::MaxSpeed>::SharedPtr sub_max_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_obstacle_;
  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr sub_obstacle_distance_;
   rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_obstacle_angle_;

  rclcpp::Publisher<msg::DriveTarget>::SharedPtr pub_target_;
  rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr pub_override_evt_;
  rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr pub_emergency_stop_evt_;

  rclcpp::Service<vehicle_core::srv::RequestInternalControl>::SharedPtr srv_req_internal_ctrl_;
  rclcpp::Service<vehicle_core::srv::ReleaseInternalControl>::SharedPtr srv_rel_internal_ctrl_;
  
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr req_mode_client_;
};

} // namespace vehicle_core