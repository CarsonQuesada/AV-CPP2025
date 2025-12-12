#pragma once

// TcpServerNode.hpp
// This class sends messages over tcp to a connected client
//
// Requirements:
// Shared/Keys.h needs to be configured with the client's port and ip address
//
// Current issues:
// - Does not send the state mode or telemetry data periodically
// 

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>
#include <std_srvs/srv/trigger.hpp>

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>
#include <optional>

// From the sibling shared/ folder (CMake adds the include path via SHARED_ROOT)
#include "Message.h"
#include "Keys.h"

#include "vehicle_core/msg/manual_drive_command.hpp"
#include "vehicle_core/msg/lights_command.hpp"
#include "vehicle_core/msg/max_speed.hpp"
#include "vehicle_core/msg/autopilot_command.hpp"

#include "vehicle_core/msg/lights_status.hpp"
#include "vehicle_core/msg/general_status.hpp"
#include "vehicle_core/msg/drive_status.hpp"
#include "vehicle_core/msg/autopilot_status.hpp"
#include "vehicle_core/msg/telemetry_data.hpp"
#include "vehicle_core/msg/error.hpp"
#include "vehicle_core/msg/server_init.hpp"
#include "vehicle_core/msg/state_mode.hpp"

#include "DebugHelpers.h"

namespace vehicle_core {

enum class ConnState : uint8_t { Disconnected = 0, Listening = 1, Connected = 2 };

class TcpServerNode : public rclcpp::Node {
public:
  explicit TcpServerNode(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
  ~TcpServerNode() override;

private:
  // Lifecycle / threads
  void supervisorLoop();
  void rxLoop();
  void txLoop();

  // Handshake and socket I/O
  bool performHandshake();
  bool recvAll(void* buf, int len, int timeout_sec);
  bool sendAll(const void* buf, int len);

  // Socket helpers
  static int setNonBlocking(int fd);
  int openListenSocket();
  void closeListen();
  void closeClient();

  // ROS helpers
  void publishState(ConnState st);

  // Handlers for outbound messages
  void onLightsStatus(const vehicle_core::msg::LightsStatus::SharedPtr m);
  void onGeneralStatus(const vehicle_core::msg::GeneralStatus::SharedPtr m);
  void onDriveStatus(const vehicle_core::msg::DriveStatus::SharedPtr m);
  void onStateMode(const vehicle_core::msg::StateMode::SharedPtr m);
  void onTelemetry(const vehicle_core::msg::TelemetryData::SharedPtr m);
  void onError(const vehicle_core::msg::Error::SharedPtr m);

  // Client helpers
  void callTriggerAsync(
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr& client,
    const char* action,                      // e.g. "ESTOP", "Manual", "Heading Start"
    const char* reason = nullptr,            // optional
    std::chrono::milliseconds wait = std::chrono::milliseconds(100),
    std::chrono::milliseconds timeout = std::chrono::milliseconds(800));

  // Other helpers
  void changeState(ConnState st);

  // Parameters
  int         port_               { LOCAL_TCP_PORT };        // from Keys.h
  std::string bind_addr_          { "0.0.0.0" };
  bool        enforce_handshake_  { true };
  int         recv_timeout_sec_   { 5 };

  // ROS interfaces
  rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr            pub_state_;
  // === Publishers (decoded inbound commands) ===
  rclcpp::Publisher<vehicle_core::msg::ManualDriveCommand>::SharedPtr pub_drive_cmd_;
  rclcpp::Publisher<vehicle_core::msg::LightsCommand>::SharedPtr      pub_lights_cmd_;
  rclcpp::Publisher<vehicle_core::msg::MaxSpeed>::SharedPtr           pub_max_speed_cmd_;
  rclcpp::Publisher<vehicle_core::msg::AutopilotCommand>::SharedPtr   pub_autopilot_cmd_;

  // === Subscribers (status to send to client) ===
  rclcpp::Subscription<vehicle_core::msg::LightsStatus>::SharedPtr     sub_lights_status_;
  rclcpp::Subscription<vehicle_core::msg::GeneralStatus>::SharedPtr    sub_general_status_;
  rclcpp::Subscription<vehicle_core::msg::DriveStatus>::SharedPtr      sub_drive_status_;
  rclcpp::Subscription<vehicle_core::msg::StateMode>::SharedPtr        sub_state_mode_;
  rclcpp::Subscription<vehicle_core::msg::TelemetryData>::SharedPtr    sub_telemetry_;
  rclcpp::Subscription<vehicle_core::msg::Error>::SharedPtr            sub_error_;

  // === Client ===
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_req_estop_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_clear_estop_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_req_manual_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_req_auto_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_heading_start_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr cli_heading_stop_;

  // === Timers for periodic sends ===
  rclcpp::TimerBase::SharedPtr timer_general_, timer_lights_, timer_drive_, timer_autopilot_, timer_telemetry_;

  // === Cached latest values + dirty flags ===
  std::mutex cache_m_;
  std::optional<::LightsStatus>      cache_lights_;
  std::optional<::GeneralStatus>     cache_general_;
  std::optional<::DriveStatus>       cache_drive_;
  std::optional<::StateMode>         cache_mode_;
  std::optional<::TelemetryData>     cache_telem_;
  std::optional<::ErrorMessage>      cache_error_;

  bool dirty_lights_{false};   // send reactive
  bool dirty_error_{false};    // send reactive

  // === Periods (params) ===
  double hz_general_{2.0}, hz_lights_{10.0}, hz_drive_{40.0}, hz_autopilot_{2.0}, hz_telem_{10.0};

  // === helpers ===
  template<typename T>
  void enqueue_message(const T& obj, MessageID id);

  // Worker threads and state
  std::thread supervisor_thread_;
  std::thread rx_thread_;
  std::thread tx_thread_;
  std::atomic<bool>      shutting_down_{false};
  std::atomic<bool>      stop_workers_{true};
  std::atomic<ConnState> state_{ConnState::Disconnected};

  // Outgoing queue (raw frames: header || payload)
  std::deque<std::vector<uint8_t>> tx_queue_;
  std::mutex tx_m_;
  std::condition_variable tx_cv_;
  bool tx_stop_{false};

  // Sockets
  std::shared_mutex sock_mut_;
  int listen_fd_{-1};
  int client_fd_{-1};

  inline void requestCleanup() {
    stop_workers_.store(true);
    { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = true; }
    tx_cv_.notify_all();
  }
  
};

template<typename T>
inline void TcpServerNode::enqueue_message(const T& obj, MessageID id) {
  // Build wire message + header from Message.h
  Message m = makeMessageFrom(obj);
  m.messageID = id;  // ok to force

  MessageHeader h{
    static_cast<uint32_t>(m.payload.size()),
    m.messageID
  };

  // Before queing do checks to see if valid message
  auto expect = expectedPayloadSize(id);
  if (!expect.has_value()) {
      RCLCPP_WARN(get_logger(), "[SRV] REFUSE to send id=%u (%s): not allowed on wire",
                  (unsigned)id, msgName(id));
      return; // drop
  }
  if (m.payload.size() != expect.value()) {
      RCLCPP_WARN(get_logger(), "[SRV] BAD PAYLOAD for id=%u (%s): len=%zu expected=%zu — dropping",
                  (unsigned)id, msgName(id),
                  m.payload.size(), expect.value());
      return;
  }

  std::vector<uint8_t> flat(sizeof(MessageHeader) + m.payload.size());
  std::memcpy(flat.data(), &h, sizeof(h));
  if (!m.payload.empty()) {
    std::memcpy(flat.data() + sizeof(h), m.payload.data(), m.payload.size());
  }

  {
    std::lock_guard<std::mutex> lk(tx_m_);
    tx_queue_.emplace_back(std::move(flat));
  }
  tx_cv_.notify_one();
}

} // namespace vehicle_core
