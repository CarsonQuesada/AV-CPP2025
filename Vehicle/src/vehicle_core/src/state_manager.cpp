#include "vehicle_core/state_manager.hpp"
#include <chrono>

using namespace std::chrono_literals;
using vehicle_core::msg::StateMode;

namespace vehicle_core {

StateManagerNode::StateManagerNode(const rclcpp::NodeOptions& opts)
: rclcpp::Node("state_manager_node", opts)
{
  // ---- parameters ----
  ap_timeout_ms_              = this->declare_parameter<int>("timeouts.autopilot_ms", 200);
  arming_timeout_ms_          = this->declare_parameter<int>("timeouts.arming_ms", 5000);
  status_hz_                  = this->declare_parameter<int>("status_hz", 5);
  escalate_ap_stale_to_estop_ = this->declare_parameter<bool>("escalate_ap_stale_to_estop", false);

  // ---- pubs/subs ----
  // We subscribe to AP drive commands ONLY to treat them as a heartbeat for AUTO freshness.
  sub_ap_cmd_ = this->create_subscription<msg::InternalDriveCommand>(
      "/vehicle/internal_drive_cmd", rclcpp::QoS(10).best_effort(),
      std::bind(&StateManagerNode::onAPDriveCmd, this, std::placeholders::_1));

  // The DriveArbiter publishes this event when manual input occurs while in AUTO.
  sub_manual_override_ = this->create_subscription<std_msgs::msg::Empty>(
      "/vehicle/events/manual_override", rclcpp::QoS(5).best_effort(),
      std::bind(&StateManagerNode::onManualOverride, this, std::placeholders::_1));

  pub_state_ = this->create_publisher<StateMode>(
      "/vehicle/state_mode", rclcpp::QoS(10).reliable().transient_local()); // make latest latched

  // ---- services ----
  srv_request_manual_ = this->create_service<std_srvs::srv::Trigger>(
      "/state_manager/request_manual",
      std::bind(&StateManagerNode::onReqManual, this, std::placeholders::_1, std::placeholders::_2));

  srv_request_auto_ = this->create_service<std_srvs::srv::Trigger>(
      "/state_manager/request_auto",
      std::bind(&StateManagerNode::onReqAuto, this, std::placeholders::_1, std::placeholders::_2));

  srv_request_estop_ = this->create_service<std_srvs::srv::Trigger>(
      "/state_manager/request_estop",
      std::bind(&StateManagerNode::onReqEStop, this, std::placeholders::_1, std::placeholders::_2));

  srv_clear_estop_ = this->create_service<std_srvs::srv::Trigger>(
      "/state_manager/clear_estop",
      std::bind(&StateManagerNode::onClearEStop, this, std::placeholders::_1, std::placeholders::_2));

  srv_mark_auto_ready_ = this->create_service<std_srvs::srv::Trigger>(
      "/state_manager/mark_auto_ready",
      std::bind(&StateManagerNode::onMarkAutoReady, this, std::placeholders::_1, std::placeholders::_2));

  cli_start_auto_ = this->create_client<std_srvs::srv::Trigger>("/autopilot/start");
  cli_stop_auto_ = this->create_client<std_srvs::srv::Trigger>("/autopilot/cancel");

  // ---- init state ----
  state_msg_.mode = MODE_INIT;
  publishState();

  // ---- status/housekeeping ----
  const double period = std::max(1, status_hz_);
  status_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(static_cast<int>(1000.0 / period)),
      std::bind(&StateManagerNode::onStatusTimer, this));

  RCLCPP_INFO(get_logger(),
              "state_manager_node up: ap_timeout=%d ms, arming_timeout=%d ms, status_hz=%d, escalate_ap_stale_to_estop=%s",
              ap_timeout_ms_, arming_timeout_ms_, status_hz_, escalate_ap_stale_to_estop_ ? "true" : "false");
}

// ============= Callbacks =============

void StateManagerNode::onAPDriveCmd(const msg::InternalDriveCommand::SharedPtr) {
  last_ap_rx_ = this->now();
}

void StateManagerNode::onManualOverride(const std_msgs::msg::Empty::SharedPtr) {
  // Only respond if currently AUTO (immediate, authoritative handoff to manual)
  if (state_msg_.mode == MODE_AUTO) {
    transitionTo(MODE_MANUAL, "manual_override_event");
  }
}

void StateManagerNode::onStatusTimer() {
  const rclcpp::Time now = this->now();

  switch (state_msg_.mode) {
    case MODE_INIT:
      // Simple policy: go straight to MANUAL on bringup.
      transitionTo(MODE_MANUAL, "init_complete");
      break;

    case MODE_ARMING:
      if ((now - arming_enter_time_).seconds() * 1000.0 > arming_timeout_ms_) {
        transitionTo(MODE_MANUAL, "Arming timed out, moving back to manual");
      }
      break;

    case MODE_AUTO: {
      // AP freshness check
      const double ms_since_ap = (now - last_ap_rx_).nanoseconds() / 1e6;
      if (ms_since_ap > ap_timeout_ms_) {
        if (escalate_ap_stale_to_estop_) {
          transitionTo(MODE_ESTOP, "autopilot stale escalate estop");
        } else {
          transitionTo(MODE_MANUAL, "autopilot stale fallback manual");
        }
      }
    } break;

    case MODE_ESTOP:
      // latched; wait for clear_estop service
      break;

    case MODE_MANUAL:
    case MODE_FAULT:
    default:
      // nothing periodic
      break;
  }

  publishState();
}

// ============= Services =============

void StateManagerNode::onReqManual(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                                   std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  bool ok = transitionTo(MODE_MANUAL, "svc_request_manual");
  res->success = ok;
  res->message = ok ? "Switched to MANUAL" : "No change";
}

void StateManagerNode::onReqAuto(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                                 std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  if (estop_latched_) {
    res->success = false;
    res->message = "Cannot enter AUTO: ESTOP latched";
    return;
  }
  // Require a brief ARMING phase before AUTO
  bool ok = transitionTo(MODE_ARMING, "svc_request_auto");
  res->success = ok;
  res->message = ok ? "Entering ARMING" : "No change";
}

void StateManagerNode::onReqEStop(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                                  std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  bool ok = transitionTo(MODE_ESTOP, "svc_request_estop");
  res->success = ok;
  res->message = "ESTOP engaged";
}

void StateManagerNode::onClearEStop(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                                    std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  estop_latched_ = false;
  // Do not auto-enter AUTO; drop to MANUAL for safety.
  bool ok = transitionTo(MODE_MANUAL, "svc_clear_estop");
  res->success = ok;
  res->message = "ESTOP cleared; MANUAL";
}

void StateManagerNode::onMarkAutoReady(const std::shared_ptr<std_srvs::srv::Trigger::Request>,
                                       std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
  if (estop_latched_) {
    res->success = false;
    res->message = "Cannot enter AUTO: ESTOP latched";
    return;
  }
  if (state_msg_.mode != MODE_ARMING) {
    res->success = false;
    res->message = "Not in ARMING";
    return;
  }
  const bool ok = transitionTo(MODE_AUTO, "autopilot marked ready");
  res->success = ok;
  res->message = ok ? "Switched to AUTO" : "No change";
}

// ============= Internals =============

bool StateManagerNode::transitionTo(uint8_t new_mode, const char* reason) {
  if (state_msg_.mode == new_mode) return false;

  if (new_mode == MODE_ESTOP) {
    estop_latched_ = true;
  }
  if (estop_latched_ && new_mode != MODE_ESTOP && new_mode != MODE_MANUAL) {
    RCLCPP_WARN(get_logger(), "rejecting transition to %u while ESTOP latched", new_mode);
    return false;
  }

  // Start arming timer when we actually enter ARMING
  if (new_mode == MODE_ARMING) {
    arming_enter_time_ = this->now();
    requestAutopilotStart();
    RCLCPP_INFO(get_logger(), "Requested autopilot start");
  }

  if (new_mode == MODE_AUTO) {
    // Give the AP up to ap_timeout_ms_ to publish a first heartbeat
    last_ap_rx_ = this->now();
  } else if (state_msg_.mode == MODE_AUTO) {
    // leaving AUTO: clear AP freshness
    last_ap_rx_ = rclcpp::Time(0, 0, RCL_ROS_TIME);
    requestAutopilotStop();
  }

  uint8_t old = state_msg_.mode;
  state_msg_.mode = new_mode;

  RCLCPP_INFO(get_logger(), "MODE %u -> %u (%s)", old, new_mode, reason ? reason : "");
  publishState();
  return true;
}

void StateManagerNode::publishState() {
  //state_msg_.header.stamp = this->now();
  pub_state_->publish(state_msg_);
}

bool StateManagerNode::requestAutopilotStart()
{
  if (!cli_start_auto_->wait_for_service(1s)) {
    RCLCPP_WARN(get_logger(), "Autopilot start service not available");
    return false;
  }

  auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
  auto future = cli_start_auto_->async_send_request(
      req,
      [this](rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture f) {
        auto res = f.get();
        if (!res->success) {
          RCLCPP_ERROR(get_logger(), "Autopilot failed to start: %s", res->message.c_str());
        } else {
          RCLCPP_INFO(get_logger(), "Autopilot start: %s", res->message.c_str());
        }
      });

  (void)future; // we don't need it right now
  return true;
}

bool StateManagerNode::requestAutopilotStop()
{
  if (!cli_stop_auto_->wait_for_service(1s)) {
    RCLCPP_WARN(get_logger(), "Autopilot stop service not available");
    return false;
  }

  auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
  auto future = cli_stop_auto_->async_send_request(
      req,
      [this](rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture f) {
        auto res = f.get();
        if (!res->success) {
          RCLCPP_ERROR(get_logger(), "Autopilot failed to stop: %s", res->message.c_str());
        } else {
          RCLCPP_INFO(get_logger(), "Autopilot stop: %s", res->message.c_str());
        }
      });

  (void)future;
  return true;
}


} // namespace vehicle_core

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::StateManagerNode)
