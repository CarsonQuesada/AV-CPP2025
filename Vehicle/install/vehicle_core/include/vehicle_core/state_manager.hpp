#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/empty.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_srvs/srv/trigger.hpp>

#include "vehicle_core/msg/state_mode.hpp"
#include "vehicle_core/msg/internal_drive_command.hpp"

namespace vehicle_core {

class StateManagerNode final : public rclcpp::Node {
public:
  explicit StateManagerNode(const rclcpp::NodeOptions& opts = rclcpp::NodeOptions());

private:
  // ====== Callbacks ======
  void onAPDriveCmd(const msg::InternalDriveCommand::SharedPtr); // heartbeat only
  void onManualOverride(const std_msgs::msg::Empty::SharedPtr);
  void onStatusTimer();
  // services
  void onReqManual(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                   std::shared_ptr<std_srvs::srv::Trigger::Response>);
  void onReqAuto(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                 std::shared_ptr<std_srvs::srv::Trigger::Response>);
  void onReqEStop(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                  std::shared_ptr<std_srvs::srv::Trigger::Response>);
  void onClearEStop(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                    std::shared_ptr<std_srvs::srv::Trigger::Response>);
  void onMarkAutoReady(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                     std::shared_ptr<std_srvs::srv::Trigger::Response>);

  // ====== Mode machine ======
  enum : uint8_t {
    MODE_INIT   = 0,
    MODE_MANUAL = 1,
    MODE_ARMING = 2,
    MODE_AUTO   = 3,
    MODE_FAULT  = 4,
    MODE_ESTOP  = 5,
  };

  bool transitionTo(uint8_t new_mode, const char* reason);
  void publishState();
  bool requestAutopilotStart();
  bool requestAutopilotStop();

  // ====== Params ======
  int  ap_timeout_ms_;               // time without AP cmds before stale
  int  arming_timeout_ms_;           // how long to sit in ARMING before AUTO (optional path)
  int  status_hz_;                   // publish rate
  bool escalate_ap_stale_to_estop_;  // if true, AP stale in AUTO -> ESTOP; else drop to MANUAL

  // ====== State ======
  vehicle_core::msg::StateMode state_msg_;
  bool estop_latched_{false};

  rclcpp::Time last_ap_rx_{0,0,RCL_ROS_TIME};
  rclcpp::Time arming_enter_time_{0,0,RCL_ROS_TIME};

  // ====== ROS I/O ======
  rclcpp::Subscription<vehicle_core::msg::InternalDriveCommand>::SharedPtr sub_ap_cmd_; // heartbeat only
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr sub_manual_override_;

  rclcpp::Publisher<vehicle_core::msg::StateMode>::SharedPtr pub_state_;

  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_request_manual_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_request_auto_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_request_estop_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_clear_estop_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr srv_mark_auto_ready_;

  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_start_auto_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_stop_auto_;

  rclcpp::TimerBase::SharedPtr status_timer_;
};

} // namespace vehicle_core
