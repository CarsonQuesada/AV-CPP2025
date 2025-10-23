#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/empty.hpp>
#include <std_srvs/srv/trigger.hpp>

#include "vehicle_core/msg/autopilot_drive_command.hpp"
#include "vehicle_core/msg/manual_drive_command.hpp"
#include "vehicle_core/msg/drive_target.hpp"
#include "vehicle_core/msg/max_speed.hpp"
#include "vehicle_core/msg/state_mode.hpp"

#include <cstdint>

namespace vehicle_core {

class DriveArbiterNode final : public rclcpp::Node {
public:
  explicit DriveArbiterNode(const rclcpp::NodeOptions& opts = rclcpp::NodeOptions());

private:
  // Callbacks
  void onStateMode(const msg::StateMode::SharedPtr m);
  void onAP(const msg::AutopilotDriveCommand::SharedPtr m);
  void onManual(const msg::ManualDriveCommand::SharedPtr m);
  void onMaxSpeed(const msg::MaxSpeed::SharedPtr m);

  // Core
  void maybePublish();                 // decide source & emit DriveTarget
  bool manualIsMeaningful(const msg::ManualDriveCommand& m) const;

  // Mapping & clamp helpers
  uint16_t clampSpeedToCap_mmps(float speed_mmps) const;
  int32_t  clampSteer_mrad(int32_t steer_mrad) const;

  int32_t percentSteerToMrad(uint8_t steer_percent) const;
  uint16_t manualSpeedPercentToMmps(uint8_t speed_percent) const;

  // Params/state
  double top_speed_mps_;        // YAML param
  double steer_max_rad_;        // YAML param
  uint8_t override_deadband_;   // YAML param [percent]
  bool publish_when_inactive_;  // YAML param

  uint8_t max_speed_percent_{100}; // runtime cap from MaxSpeed topic
  msg::StateMode::SharedPtr last_mode_;

  msg::AutopilotDriveCommand::SharedPtr last_ap_;
  msg::ManualDriveCommand::SharedPtr    last_manual_;

  // ROS I/O
  rclcpp::Subscription<msg::StateMode>::SharedPtr sub_mode_;
  rclcpp::Subscription<msg::AutopilotDriveCommand>::SharedPtr sub_ap_;
  rclcpp::Subscription<msg::ManualDriveCommand>::SharedPtr sub_manual_;
  rclcpp::Subscription<msg::MaxSpeed>::SharedPtr sub_max_;

  rclcpp::Publisher<msg::DriveTarget>::SharedPtr pub_target_;
  rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr pub_override_evt_;

  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr req_mode_client_;

  // QoS
  rclcpp::QoS qos_best_effort_{rclcpp::QoS(10).best_effort().durability_volatile()};

  // Helpers
  int16_t capSpeedMmpsSigned(double mmps_signed) const;
  int16_t capSteerMradSigned(double mrad_signed) const;
  int16_t manualPercentToMmpsSigned(uint8_t speed_percent, uint8_t gear) const;
  int16_t percentSteerToMradSigned(uint8_t steer_percent) const;
};

} // namespace vehicle_core