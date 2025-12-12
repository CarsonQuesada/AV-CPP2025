#include "vehicle_core/tcp_server_node.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <functional>

using namespace std::chrono_literals;
using vehicle_core::TcpServerNode;
using vehicle_core::ConnState;

namespace rosm = vehicle_core::msg;  // ROS messages
namespace wire {
  using ::LightsStatus;
  using ::GeneralStatus;
  using ::DriveStatus;
  using ::StateMode;
  using ::TelemetryData;
  using ::ErrorMessage;
  using ::ServerInit;
}

TcpServerNode::TcpServerNode(const rclcpp::NodeOptions& options)
: rclcpp::Node("tcp_server_node", options)
{
  // Declare parameters (defaults come from members, port_ uses LOCAL_TCP_PORT macro)
  port_              = this->declare_parameter<int>("port", LOCAL_TCP_PORT);
  bind_addr_         = this->declare_parameter<std::string>("bind_address", "0.0.0.0");
  enforce_handshake_ = this->declare_parameter<bool>("enforce_handshake", true);
  recv_timeout_sec_  = this->declare_parameter<int>("recv_timeout_sec", 5);

  // Rates
  hz_general_   = this->declare_parameter<double>("general_status_hz",   2.0);
  hz_lights_    = this->declare_parameter<double>("lights_status_hz",   10.0);
  hz_drive_     = this->declare_parameter<double>("drive_status_hz",    40.0);
  hz_autopilot_ = this->declare_parameter<double>("autopilot_status_hz", 2.0);

  // Publishers (decoded inbound control)
  pub_state_         = this->create_publisher<std_msgs::msg::UInt8>("/tcp_server/connection_state", rclcpp::QoS(1).reliable().transient_local());
  pub_drive_cmd_     = this->create_publisher<vehicle_core::msg::ManualDriveCommand>("vehicle/manual_drive_cmd", 10);
  pub_lights_cmd_    = this->create_publisher<vehicle_core::msg::LightsCommand>("vehicle/lights_cmd", 10);
  pub_max_speed_cmd_ = this->create_publisher<vehicle_core::msg::MaxSpeed>("vehicle/max_speed_cmd", 10);
  pub_autopilot_cmd_ = this->create_publisher<vehicle_core::msg::AutopilotCommand>("autopilot/active_cmd", 10);

  sub_lights_status_ = this->create_subscription<vehicle_core::msg::LightsStatus>(
    "vehicle/lights_status", rclcpp::QoS(10),
    std::bind(&TcpServerNode::onLightsStatus, this, std::placeholders::_1));

  sub_general_status_ = this->create_subscription<vehicle_core::msg::GeneralStatus>(
    "vehicle/general_status", rclcpp::QoS(10),
    std::bind(&TcpServerNode::onGeneralStatus, this, std::placeholders::_1));

  sub_drive_status_ = this->create_subscription<vehicle_core::msg::DriveStatus>(
    "vehicle/drive_status", rclcpp::QoS(20),
    std::bind(&TcpServerNode::onDriveStatus, this, std::placeholders::_1));

  sub_state_mode_ = this->create_subscription<vehicle_core::msg::StateMode>(
    "/vehicle/state_mode", rclcpp::QoS(10),
    std::bind(&TcpServerNode::onStateMode, this, std::placeholders::_1));

  sub_telemetry_ = this->create_subscription<vehicle_core::msg::TelemetryData>(
    "vehicle/telemetry", rclcpp::QoS(20),
    std::bind(&TcpServerNode::onTelemetry, this, std::placeholders::_1));

  sub_error_ = this->create_subscription<vehicle_core::msg::Error>(
    "vehicle/error", rclcpp::QoS(5),
    std::bind(&TcpServerNode::onError, this, std::placeholders::_1));

    // Clients
    cli_req_estop_ = this->create_client<std_srvs::srv::Trigger>("/state_manager/request_estop");
    cli_clear_estop_ = this->create_client<std_srvs::srv::Trigger>("/state_manager/clear_estop");
    cli_req_manual_ = this->create_client<std_srvs::srv::Trigger>("/state_manager/request_manual");
    cli_req_auto_ = this->create_client<std_srvs::srv::Trigger>("/state_manager/request_auto");
    cli_heading_start_  = this->create_client<std_srvs::srv::Trigger>("/routines/heading/start");
    cli_heading_stop_ = this->create_client<std_srvs::srv::Trigger>("/routines/heading/cancel");

    // Timers for periodic sends
    if (hz_general_ > 0.0)   timer_general_   = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0/hz_general_)),   [this]{ if (state_.load()==ConnState::Connected) { std::lock_guard<std::mutex> lk(cache_m_); if (cache_general_)   enqueue_message(*cache_general_,   MessageID::GeneralStatus); }});
    if (hz_lights_  > 0.0)   timer_lights_    = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0/hz_lights_)),    [this]{ if (state_.load()==ConnState::Connected) { std::lock_guard<std::mutex> lk(cache_m_); if (cache_lights_)    enqueue_message(*cache_lights_,    MessageID::LightsStatus);  dirty_lights_ = false; }});
    if (hz_drive_   > 0.0)   timer_drive_     = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0/hz_drive_)),     [this]{ if (state_.load()==ConnState::Connected) { std::lock_guard<std::mutex> lk(cache_m_); if (cache_drive_)     enqueue_message(*cache_drive_,     MessageID::DriveStatus); }});
    if (hz_autopilot_>0.0)   timer_autopilot_ = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0/hz_autopilot_)), [this]{ if (state_.load()==ConnState::Connected) { std::lock_guard<std::mutex> lk(cache_m_); if (cache_mode_)      enqueue_message(*cache_mode_,      MessageID::StateMode); }});

    // Start supervisor thread
    supervisor_thread_ = std::thread([this]{ supervisorLoop(); });
  }

TcpServerNode::~TcpServerNode() {
  shutting_down_.store(true);

  // Stop workers and wake TX queue
  {
    std::lock_guard<std::mutex> lk(tx_m_);
    tx_stop_ = true;
  }
  tx_cv_.notify_all();

  if (supervisor_thread_.joinable()) supervisor_thread_.join();
  if (rx_thread_.joinable()) rx_thread_.join();
  if (tx_thread_.joinable()) tx_thread_.join();

  closeClient();
  closeListen();
}

// ---------- socket helpers ----------

int TcpServerNode::setNonBlocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags < 0) return -1;
  return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int TcpServerNode::openListenSocket() {
  int s = ::socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) return -1;

  int opt = 1;
  ::setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port   = htons(port_);
  if (bind_addr_ == "0.0.0.0") {
    addr.sin_addr.s_addr = INADDR_ANY;
  } else {
    if (::inet_pton(AF_INET, bind_addr_.c_str(), &addr.sin_addr) <= 0) {
      ::close(s);
      return -2;
    }
  }

  if (::bind(s, (sockaddr*)&addr, sizeof(addr)) < 0) { ::close(s); return -3; }
  if (::listen(s, 1) < 0)                           { ::close(s); return -4; }
  return s;
}

void TcpServerNode::closeListen() {
  std::unique_lock<std::shared_mutex> lk(sock_mut_);
  if (listen_fd_ >= 0) { ::close(listen_fd_); listen_fd_ = -1; }
}

void TcpServerNode::closeClient() {
  std::unique_lock<std::shared_mutex> lk(sock_mut_);
  if (client_fd_ >= 0) {
    ::shutdown(client_fd_, SHUT_RDWR);
    ::close(client_fd_);
    client_fd_ = -1;
  }
}

void TcpServerNode::publishState(ConnState st) {
  auto m = std_msgs::msg::UInt8();
  m.data = static_cast<uint8_t>(st);
  pub_state_->publish(m);
}

// ---------- supervisor / accept / lifecycle ----------

void TcpServerNode::supervisorLoop() {
  rclcpp::Rate r(10.0);

  while (rclcpp::ok() && !shutting_down_.load()) {
    if (state_.load() == ConnState::Disconnected) {
      int fd = openListenSocket();
      if (fd < 0) {
        RCLCPP_ERROR(get_logger(), "Listen failed (code %d); retry in 2s", fd);
        changeState(ConnState::Disconnected);
        std::this_thread::sleep_for(2s);
        continue;
      }
      { std::unique_lock<std::shared_mutex> lk(sock_mut_); listen_fd_ = fd; }
      changeState(ConnState::Listening);
      RCLCPP_INFO(get_logger(), "Listening on %s:%d", bind_addr_.c_str(), port_);
    }

    if (state_.load() == ConnState::Listening) {
      int fd_copy;
      { std::shared_lock<std::shared_mutex> lk(sock_mut_); fd_copy = listen_fd_; }
      if (fd_copy < 0) { changeState(ConnState::Disconnected);; continue; }

      fd_set rfds; FD_ZERO(&rfds); FD_SET(fd_copy, &rfds);
      timeval tv{1,0};
      int sel = ::select(fd_copy+1, &rfds, nullptr, nullptr, &tv);
      if (sel > 0 && FD_ISSET(fd_copy, &rfds)) {
        int cfd = ::accept(fd_copy, nullptr, nullptr);
        if (cfd >= 0) {
          setNonBlocking(cfd);
          { std::unique_lock<std::shared_mutex> lk(sock_mut_); client_fd_ = cfd; }

          // Handshake BEFORE starting worker threads
          if (enforce_handshake_ && !performHandshake()) {
            RCLCPP_WARN(get_logger(), "Handshake failed; closing client");
            closeClient();
            // remain in Listening
            continue;
          }

          // Clean up any previous worker threads (finished threads are still joinable!)
          if (rx_thread_.joinable()) rx_thread_.join();
          if (tx_thread_.joinable()) tx_thread_.join();

          // Start fresh workers AFTER handshake succeeds
          stop_workers_.store(false);
          { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = false; }
          rx_thread_ = std::thread([this]{ rxLoop(); });
          tx_thread_ = std::thread([this]{ txLoop(); });

          changeState(ConnState::Connected);
          RCLCPP_INFO(get_logger(), "Accepted client");
        }
      }
    }

    if (state_.load() == ConnState::Connected) {
      // Cleanup triggered by worker request to stop (rxLoop sets stop_workers_=true)
      if (stop_workers_.load()) {
        { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = true; }
        tx_cv_.notify_all();

        // Unblock any I/O and close socket
        closeClient();

        // Reap worker threads (they may already have exited; still joinable)
        if (rx_thread_.joinable()) rx_thread_.join();
        if (tx_thread_.joinable()) tx_thread_.join();

        // Back to listening
        changeState(ConnState::Listening);
        RCLCPP_INFO(get_logger(), "Cleaned up; back to Listening");
      }
    }

    r.sleep();
  }

  // Shutdown path
  stop_workers_.store(true);
  { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = true; }
  tx_cv_.notify_all();
  if (rx_thread_.joinable()) rx_thread_.join();
  if (tx_thread_.joinable()) tx_thread_.join();
}

// ---------- I/O helpers ----------

bool TcpServerNode::recvAll(void* buf, int len, int timeout_sec) {
  int got = 0;

  while (got < len) {
    int fd_copy; { std::shared_lock<std::shared_mutex> lk(sock_mut_); fd_copy = client_fd_; }
    if (fd_copy < 0) return false;

    fd_set rfds; FD_ZERO(&rfds); FD_SET(fd_copy, &rfds);

    // If timeout_sec <= 0, block forever (nullptr timeout)
    timeval tv{timeout_sec, 0};
    timeval* tvp = (timeout_sec <= 0) ? nullptr : &tv;

    int rr = ::select(fd_copy + 1, &rfds, nullptr, nullptr, tvp);
    if (rr < 0) {
      RCLCPP_ERROR(get_logger(), "select(recv): %s", strerror(errno));
      return false;
    }
    if (rr == 0) {
      // Only warn/drop if a real timeout was requested
      if (timeout_sec > 0) {
        RCLCPP_WARN(get_logger(), "recv timeout");
        return false;
      }
      continue;
    }

    int n = ::recv(fd_copy, (char*)buf + got, len - got, 0);
    if (n > 0) { got += n; continue; }
    if (n == 0) { RCLCPP_INFO(get_logger(), "peer closed"); return false; }
    if (errno == EAGAIN || errno == EWOULDBLOCK) continue;

    RCLCPP_ERROR(get_logger(), "recv: %s", strerror(errno));
    return false;
  }
  return true;
}

bool TcpServerNode::sendAll(const void* buf, int len) {
  int sent = 0;
  int fd_copy; { std::shared_lock<std::shared_mutex> lk(sock_mut_); fd_copy = client_fd_; }
  if (fd_copy < 0) return false;

  while (sent < len) {
    fd_set wfds; FD_ZERO(&wfds); FD_SET(fd_copy, &wfds);
    timeval tv{1, 0};
    int rr = ::select(fd_copy+1, nullptr, &wfds, nullptr, &tv);
    if (rr < 0) { RCLCPP_ERROR(get_logger(), "select(send): %s", strerror(errno)); return false; }
    if (rr == 0) { RCLCPP_WARN(get_logger(), "send timeout"); return false; }
    int n = ::send(fd_copy, (const char*)buf + sent, len - sent, 0);
    if (n > 0) { sent += n; continue; }
    if (n == 0) { RCLCPP_INFO(get_logger(), "peer closed"); return false; }
    if (errno == EAGAIN || errno == EWOULDBLOCK) continue;
    RCLCPP_ERROR(get_logger(), "send: %s", strerror(errno));
    return false;
  }
  return true;
}

// ---------- workers ----------

void TcpServerNode::rxLoop() {
  RCLCPP_INFO(get_logger(), "rxLoop started");
  while (rclcpp::ok() && !stop_workers_.load()) {
    // Read header
    MessageHeader h{};
    if (!recvAll(&h, sizeof(h), recv_timeout_sec_)) break;

    // Run checks to see if valid message
    if (h.payloadLength > MAX_PAYLOAD) {
        RCLCPP_WARN(get_logger(), "BAD header: id=%u len=%u (cap=%u) — resetting link",
                    (unsigned)h.messageID, (unsigned)h.payloadLength, (unsigned)MAX_PAYLOAD);
        stop_workers_.store(true);
        { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = true; }
        tx_cv_.notify_all();
        return; // supervisor will close and go back to Listening
    }
    auto expect = expectedPayloadSize(h.messageID);
    if (!expect.has_value()) {
        RCLCPP_WARN(get_logger(), "BAD header: id=%u (%s) not allowed — resetting link",
                    (unsigned)h.messageID, msgName(h.messageID));
        stop_workers_.store(true);
        { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = true; }
        tx_cv_.notify_all();
        return;
    }
    if (h.payloadLength != expect.value()) {
        RCLCPP_WARN(get_logger(), "BAD length for id=%u (%s): len=%u expected=%zu — resetting link",
                    (unsigned)h.messageID, msgName(h.messageID),
                    (unsigned)h.payloadLength, expect.value());
        stop_workers_.store(true);
        { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = true; }
        tx_cv_.notify_all();
        return;
    }

    // Read payload
    Message m;
    m.messageID = h.messageID;
    m.payload.resize(h.payloadLength);
    if (h.payloadLength > 0) {
      if (!recvAll(m.payload.data(), h.payloadLength, recv_timeout_sec_)) break;
    }

    // RCLCPP_DEBUG(get_logger(), "RX id=%u (%s) len=%zu payload=%s",
    //          (unsigned)m.messageID, msgName(m.messageID),
    //          m.payload.size(),
    //          m.payload.empty() ? "" : hexDump(m.payload.data(), m.payload.size()).c_str());

    // Decode and publish other messages
    switch (m.messageID) {
      case MessageID::Ping: {
        MessageHeader rh{ (uint32_t)m.payload.size(), MessageID::Ping };
        std::vector<uint8_t> flat(sizeof(MessageHeader) + m.payload.size());
        std::memcpy(flat.data(), &rh, sizeof(rh));
        if (!m.payload.empty())
          std::memcpy(flat.data() + sizeof(rh), m.payload.data(), m.payload.size());
        { std::lock_guard<std::mutex> lk(tx_m_); tx_queue_.emplace_back(std::move(flat)); }
        tx_cv_.notify_one();
        continue;
      }
      case MessageID::Drive: {
        if (m.payload.size()==sizeof(DriveCommand)) {
          auto d = extractPayload<DriveCommand>(m);
          vehicle_core::msg::ManualDriveCommand out;
          out.brake = d.brake;
          out.gear  = static_cast<uint8_t>(d.gear);
          out.speed = d.speed;
          out.steer = d.steer;
          pub_drive_cmd_->publish(out);
        }
        break;
      }
      case MessageID::ToggleLights: {
        if (m.payload.size()==sizeof(LightsCommand)) {
          auto lc = extractPayload<LightsCommand>(m);
          vehicle_core::msg::LightsCommand out;
          out.light_id = static_cast<uint8_t>(lc.lightID);
          pub_lights_cmd_->publish(out);
        }
        break;
      }
      case MessageID::SetMaxSpeed: {
        if (m.payload.size()==sizeof(SetMaxSpeedCommand)) {
          auto ms = extractPayload<SetMaxSpeedCommand>(m);
          vehicle_core::msg::MaxSpeed out;
          out.percent = ms.maxSpeed;
          pub_max_speed_cmd_->publish(out);
        }
        break;
      }
      case MessageID::StartAutopilot: {
        vehicle_core::msg::AutopilotCommand out;
        out.action = 1; // START
        pub_autopilot_cmd_->publish(out);
        callTriggerAsync(cli_req_auto_, "Autopilot Mode", "Client started autopilot");
        RCLCPP_INFO(get_logger(), "Turning ON autopilot");
        break;
      }
      case MessageID::StopAutopilot: {
        vehicle_core::msg::AutopilotCommand out;
        out.action = 0; // STOP
        pub_autopilot_cmd_->publish(out);
        callTriggerAsync(cli_req_manual_, "Manual Mode", "Client stopped autopilot");
        RCLCPP_INFO(get_logger(), "Turning OFF autopilot");
        break;
      }
      case MessageID::StartHeadingCalib: {
        callTriggerAsync(cli_heading_start_, "Heading Start", "Starting heading calibration");
        RCLCPP_INFO(get_logger(), "Starting heading calibration");
        break;
      }
      case MessageID::StopHeadingCalib: {
        callTriggerAsync(cli_heading_stop_, "Heading Stop", "Stopping heading calibration");
        RCLCPP_INFO(get_logger(), "Stopping heading calibration");
        break;
      }
      case MessageID::ClientInit:
        // handshake already consumed in performHandshake()
        break;

      default:
        break;
    }

  }

  RCLCPP_INFO(get_logger(), "rxLoop exiting (disconnect)");
  // Signal supervisor to clean up; don't touch sockets or state here
  stop_workers_.store(true);
  { std::lock_guard<std::mutex> lk(tx_m_); tx_stop_ = true; }
  tx_cv_.notify_all();
}

void TcpServerNode::txLoop() {
  RCLCPP_INFO(get_logger(), "txLoop started");
  while (rclcpp::ok() && !stop_workers_.load()) {
    std::vector<uint8_t> flat;
    {
      std::unique_lock<std::mutex> lk(tx_m_);
      tx_cv_.wait_for(lk, 50ms, [this]{ return !tx_queue_.empty() || tx_stop_; });
      if (tx_stop_) break;
      if (tx_queue_.empty()) continue;
      flat = std::move(tx_queue_.front());
      tx_queue_.pop_front();
    }

    if (flat.size() < sizeof(MessageHeader)) {
      RCLCPP_WARN(get_logger(), "Outgoing frame too small: %zu bytes", flat.size());
      continue;
    }

    if (!sendAll(flat.data(), static_cast<int>(flat.size()))) {
      RCLCPP_WARN(get_logger(), "tx send failed; signaling cleanup");
      requestCleanup();               
      break;
    }
  }
  RCLCPP_INFO(get_logger(), "txLoop exiting");
}

// ---------- handshake ----------

bool TcpServerNode::performHandshake() {
  RCLCPP_INFO(get_logger(), "HS: waiting for ClientInit header...");
  MessageHeader h{};
  if (!recvAll(&h, sizeof(h), /*timeout_sec=*/0)) {
    RCLCPP_WARN(get_logger(), "HS: failed to read ClientInit header");
    return false;
  }
  RCLCPP_INFO(get_logger(), "HS: got header id=%u len=%u",
              (unsigned)h.messageID, (unsigned)h.payloadLength);

  if (h.messageID != MessageID::ClientInit || h.payloadLength != sizeof(ClientInit)) {
    RCLCPP_WARN(get_logger(), "HS: unexpected id/len (id=%u len=%u expected id=%u len=%zu)",
                (unsigned)h.messageID, (unsigned)h.payloadLength,
                (unsigned)MessageID::ClientInit, sizeof(ClientInit));
    if (h.payloadLength) {
      std::vector<uint8_t> dummy(h.payloadLength);
      (void)recvAll(dummy.data(), h.payloadLength, 0);
    }
    return false;
  }

  // read ClientInit payload
  if (h.payloadLength) {
    std::vector<uint8_t> pl(h.payloadLength);
    if (!recvAll(pl.data(), h.payloadLength, 0)) { RCLCPP_WARN(get_logger(), "HS: payload read failed"); return false; }
  }

  // Build and send ServerInit
  ServerInit s{};
  {
    std::lock_guard<std::mutex> lk(cache_m_);
    if (cache_general_)   s.generalStatus   = *cache_general_;
    if (cache_lights_)    s.lightsStatus    = *cache_lights_;
    if (cache_drive_)     s.driveStatus     = *cache_drive_;
    if (cache_mode_)      s.stateMode = *cache_mode_;
  }
  Message reply = makeMessageFrom(s);
  MessageHeader rh{ (uint32_t)reply.payload.size(), MessageID::ServerInit };

  RCLCPP_INFO(get_logger(), "HS: sending ServerInit header len=%u, payload=%zu",
              rh.payloadLength, reply.payload.size());

  if (!sendAll(&rh, sizeof(rh)))                { RCLCPP_WARN(get_logger(), "HS: send header failed");   return false; }
  if (!reply.payload.empty() && !sendAll(reply.payload.data(), (int)reply.payload.size())) {
    RCLCPP_WARN(get_logger(), "HS: send payload failed"); return false;
  }

  RCLCPP_INFO(get_logger(), "HS: complete");
  return true;
}

void TcpServerNode::onLightsStatus(const vehicle_core::msg::LightsStatus::SharedPtr m) {
  wire::LightsStatus local{};
  {
    std::lock_guard<std::mutex> lk(cache_m_);
    cache_lights_ = wire::LightsStatus{
      m->brake_lights, m->reverse_lights, m->right_sig,
      m->left_sig, m->headlights, m->hazards
    };
    local = *cache_lights_;
    dirty_lights_ = true;
  }
  if (state_.load() == ConnState::Connected) {
    enqueue_message(local, MessageID::LightsStatus);  // reactive send
  }
}

void TcpServerNode::onGeneralStatus(const vehicle_core::msg::GeneralStatus::SharedPtr m) {
  std::lock_guard<std::mutex> lk(cache_m_);
  cache_general_ = wire::GeneralStatus{ m->speed, m->battery_percent,
                                        static_cast<uint8_t>(m->gps_online) };
}

void TcpServerNode::onDriveStatus(const vehicle_core::msg::DriveStatus::SharedPtr m) {
  std::lock_guard<std::mutex> lk(cache_m_);
  cache_drive_ = wire::DriveStatus{
    static_cast<GearID>(m->gear), static_cast<uint8_t>(m->braking)
  };
}

void TcpServerNode::onStateMode(const vehicle_core::msg::StateMode::SharedPtr m) {
  std::lock_guard<std::mutex> lk(cache_m_);
  cache_mode_ = wire::StateMode{static_cast<uint8_t>(m->mode)};
}

void TcpServerNode::onTelemetry(const vehicle_core::msg::TelemetryData::SharedPtr m) {
  std::lock_guard<std::mutex> lk(cache_m_);
  cache_telem_ = wire::TelemetryData{ static_cast<uint8_t>(m->gps_online),
                                      m->lat, m->lon, m->heading, m->speed, m->distance_delta };
}

void TcpServerNode::onError(const vehicle_core::msg::Error::SharedPtr m) {
  wire::ErrorMessage local{};
  {
    std::lock_guard<std::mutex> lk(cache_m_);
    cache_error_ = wire::ErrorMessage{ static_cast<ErrorCode>(m->code) };
    local = *cache_error_;
    dirty_error_ = true;
  }
  if (state_.load() == ConnState::Connected) {
    enqueue_message(local, MessageID::Error);        // reactive send
  }
}

void TcpServerNode::callTriggerAsync(
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr& client,
  const char* action,
  const char* reason,
  std::chrono::milliseconds wait,
  std::chrono::milliseconds timeout)
{
  if (!client) {
    RCLCPP_ERROR(get_logger(), "%s: client is null", action);
    return;
  }
  if (!client->service_is_ready()) {
    client->wait_for_service(wait);
  }

  auto req = std::make_shared<std_srvs::srv::Trigger::Request>();
  (void)client->async_send_request(req,
    [this, action, reason, timeout](rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture f) {
      try {
        if (f.wait_for(timeout) != std::future_status::ready) {
          RCLCPP_ERROR(get_logger(), "%s timed out (%s)", action, reason ? reason : "n/a");
          return;
        }
        auto res = f.get();
        RCLCPP_INFO(get_logger(), "%s: success=%s msg=\"%s\" (%s)",
                    action, res->success ? "true" : "false",
                    res->message.c_str(), reason ? reason : "n/a");
      } catch (const std::exception& e) {
        RCLCPP_ERROR(get_logger(), "%s failed (%s): %s", action, reason ? reason : "n/a", e.what());
      }
    });
}

void TcpServerNode::changeState(ConnState st) {
  if ((state_ != ConnState::Disconnected) && (st == ConnState::Disconnected)) {
    callTriggerAsync(cli_req_estop_, "ESTOP", "TCP disconnected from client");
  } else if ((state_ != ConnState::Listening) && (st == ConnState::Listening)) {
    callTriggerAsync(cli_req_estop_, "ESTOP", "TCP not connected to client");
  } else if (st == ConnState::Connected) {
    callTriggerAsync(cli_clear_estop_, "Clear ESTOP", "TCP connected to client");
  }
  state_.store(st);
  publishState(st);
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::TcpServerNode)