#include "vehicle_core/i2c_bridge_node.hpp"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <chrono>

using rclcpp::QoS;
using rclcpp::KeepLast;
using rclcpp::SensorDataQoS;

namespace vehicle_core {

rclcpp::QoS I2cBridgeNode::qos_transient_reliable(size_t depth) const {
  rclcpp::QoS q{rclcpp::KeepLast(depth)};
  q.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  q.durability(RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL);
  return q;
}

I2cBridgeNode::I2cBridgeNode(const rclcpp::NodeOptions& opts)
: rclcpp::Node("i2c_bridge_node", opts)
{
  // Params
  i2c_path_              = this->declare_parameter<std::string>("i2c.path", "/dev/i2c-1");
  addr_lighting_         = static_cast<uint8_t>(this->declare_parameter<int>("i2c.addr_lighting", 0x15));
  addr_drive_            = static_cast<uint8_t>(this->declare_parameter<int>("i2c.addr_drive",    0x20));
  drive_cmd_hz_          = this->declare_parameter<int>("rates.drive_cmd_hz", 50);
  drive_status_hz_       = this->declare_parameter<int>("rates.drive_status_hz", 50);
  brake_light_threshold_ = this->declare_parameter<int>("lighting.brake_threshold_percent", 10);
  default_enable_        = this->declare_parameter<bool>("drive.default_enable", true);

  // Open I2C
  i2c_drv_.path = i2c_lgt_.path = i2c_path_;
  i2c_drv_.addr = addr_drive_;
  i2c_lgt_.addr = addr_lighting_;
  if (!i2c_open(i2c_drv_, "drive") || !i2c_open(i2c_lgt_, "lighting")) {
    throw std::runtime_error("Failed to open one or more I2C devices");
  }

  // Publishers
  pub_drive_status_     = this->create_publisher<vehicle_core::msg::DriveStatus>("/vehicle/drive_status", 10);
  pub_drive_feedback_   = this->create_publisher<vehicle_core::msg::DriveFeedback>("/vehicle/drive_feedback", SensorDataQoS());
  pub_drive_fault_bits_ = this->create_publisher<std_msgs::msg::UInt16>("/vehicle/drive_fault_bits", qos_transient_reliable(1));
  pub_lights_status_    = this->create_publisher<vehicle_core::msg::LightsStatus>("/vehicle/lights_status", 1);

  // Subscriptions
  sub_estop_ = this->create_subscription<std_msgs::msg::Bool>(
      "/vehicle/estop", 10, std::bind(&I2cBridgeNode::on_estop, this, std::placeholders::_1));

  sub_drive_target_ = this->create_subscription<vehicle_core::msg::DriveTarget>(
      "/vehicle/drive_target", 20, std::bind(&I2cBridgeNode::on_drive_target, this, std::placeholders::_1));

  sub_lights_ = this->create_subscription<vehicle_core::msg::LightsCommand>(
      "/vehicle/lights_cmd", 5, std::bind(&I2cBridgeNode::on_lights, this, std::placeholders::_1));

  sub_tcp_state_ = this->create_subscription<std_msgs::msg::UInt8>(
      "/tcp_server/connection_state", qos_transient_reliable(1),
      std::bind(&I2cBridgeNode::on_tcp_state, this, std::placeholders::_1));

  using namespace std::chrono;
  auto ms = [](int hz){ return std::chrono::milliseconds(std::max(1, 1000 / std::max(1, hz))); };

  // Timers
  t_drive_cmd_     = this->create_wall_timer(ms(drive_cmd_hz_),          std::bind(&I2cBridgeNode::tick_drive_cmd, this));
  t_drive_status_  = this->create_wall_timer(ms(drive_status_hz_),       std::bind(&I2cBridgeNode::tick_drive_status, this));

  RCLCPP_INFO(get_logger(), "i2c_bridge_node up on %s  drive=0x%02X lighting=0x%02X",
              i2c_path_.c_str(), addr_drive_, addr_lighting_);

  {
    std::lock_guard<std::mutex> lks(lights_mtx_);
    publish_lights_status_locked();
  }
}

// I2C helpers
bool I2cBridgeNode::i2c_open(I2cDevice& dev, const char* what) {
  dev.fd = ::open(dev.path.c_str(), O_RDWR | O_CLOEXEC);
  if (dev.fd < 0) {
    RCLCPP_ERROR(get_logger(), "I2C open(%s) for %s failed: %s", dev.path.c_str(), what, std::strerror(errno));
    return false;
  }
  if (!i2c_select(dev.fd, dev.addr)) return false;
  return true;
}

bool I2cBridgeNode::i2c_select(int fd, uint8_t addr) {
  if (ioctl(fd, I2C_SLAVE, addr) < 0) {
    RCLCPP_ERROR(get_logger(), "I2C ioctl(I2C_SLAVE,0x%02X) failed: %s", addr, std::strerror(errno));
    return false;
  }
  return true;
}

bool I2cBridgeNode::i2c_write(int fd, const void* buf, size_t n) {
  ssize_t w = ::write(fd, buf, n);
  return (w == static_cast<ssize_t>(n));
}

bool I2cBridgeNode::i2c_read(int fd, void* buf, size_t n) {
  ssize_t r = ::read(fd, buf, n);
  return (r == static_cast<ssize_t>(n));
}

// Callbacks
void I2cBridgeNode::on_estop(const std_msgs::msg::Bool::SharedPtr m) { estop_.store(m->data); }

void I2cBridgeNode::on_drive_target(const vehicle_core::msg::DriveTarget::SharedPtr m) {
  last_target_ = m;
  maybe_auto_brake_lights(m->brake_percent);
}

void I2cBridgeNode::on_lights(const vehicle_core::msg::LightsCommand::SharedPtr m) {
  // Interpret incoming as LightID toggle intent
  const uint8_t id = m->light_id;
  last_light_cmd_ = id; // keep for visibility/diagnostics

  bool changed = false;
  uint8_t cmd_to_send = 0;

  {
    std::lock_guard<std::mutex> lks(lights_mtx_);

    switch (id) {
      case 0x01: { // LeftTurnSig toggle
        // If hazards are on, turning one side typically cancels hazards first.
        if (lights_.hazards) {
          lights_.hazards = false;
          // No need to send HazardsOff if your MCU derives hazards from both signals on.
          // If it needs explicit HazardsOff, uncomment next line:
          // send_light_cmd(static_cast<uint8_t>(LightingCommand::HazardsOff));
        }
        lights_.left_sig = !lights_.left_sig;
        cmd_to_send = static_cast<uint8_t>(
            lights_.left_sig ? 3 /*LeftSigOn*/ : 4 /*LeftSigOff*/);
        changed = true;
        break;
      }
      case 0x02: { // RightTurnSig toggle
        if (lights_.hazards) {
          lights_.hazards = false;
          // Optionally: send HazardsOff explicitly
          // send_light_cmd(static_cast<uint8_t>(LightingCommand::HazardsOff));
        }
        lights_.right_sig = !lights_.right_sig;
        cmd_to_send = static_cast<uint8_t>(
            lights_.right_sig ? 5 /*RightSigOn*/ : 6 /*RightSigOff*/);
        changed = true;
        break;
      }
      case 0x03: { // Headlights toggle
        lights_.headlights = !lights_.headlights;
        cmd_to_send = static_cast<uint8_t>(
            lights_.headlights ? 1 /*HeadlightsOn*/ : 2 /*HeadlightsOff*/);
        changed = true;
        break;
      }
      case 0x04: { // Hazards toggle (example ID)
        lights_.hazards = !lights_.hazards;
        // When hazards on, most cars cancel individual signals
        lights_.left_sig  = lights_.hazards;
        lights_.right_sig = lights_.hazards;
        cmd_to_send = static_cast<uint8_t>(
            lights_.hazards ? 7 /*HazardsOn*/ : 8 /*HazardsOff*/);
        changed = true;
        break;
      }
      case 0x00: // NoInput
      default:
        // ignore
        break;
    }

    if (changed) {
      // Send the single-byte command; if it fails, revert the state change so status stays truthful
      if (!send_light_cmd(cmd_to_send)) {
        // revert toggle if write failed
        switch (id) {
          case 0x01: lights_.left_sig = !lights_.left_sig; break;
          case 0x02: lights_.right_sig = !lights_.right_sig; break;
          case 0x03: lights_.headlights = !lights_.headlights; break;
          default: break;
        }
        RCLCPP_WARN(get_logger(), "Lighting I2C write failed; state reverted (errno=%d: %s)", errno, std::strerror(errno));
      } else {
        // on success, publish new status
        publish_lights_status_locked();
      }
    }
  }
}

void I2cBridgeNode::on_tcp_state(const std_msgs::msg::UInt8::SharedPtr m) {
  tcp_state_.store(m->data);
  // Optional link-state animation (raw one-byte command), if your lighting Arduino supports it.
  uint8_t light_cmd = 0;
  switch (m->data) {
    case 0: light_cmd = 12; break; // Disconnected -> StopConnecting
    case 1: light_cmd = 14; break; // Listening    -> Reconnecting
    case 2: light_cmd = 13; break; // Connected
  }
  if (light_cmd) {
    last_light_cmd_ = light_cmd;
    std::lock_guard<std::mutex> lk(i2c_mtx_);
    (void)i2c_select(i2c_lgt_.fd, addr_lighting_);
    (void)i2c_write(i2c_lgt_.fd, &light_cmd, 1);
  }
}

// Command builder (unchanged)
DriveCommandWire I2cBridgeNode::build_drive_command() {
  DriveCommandWire dc{};
  const bool estop  = estop_.load();
  const bool tcp_ok = (tcp_state_.load() == 2);

  bool enable = (!estop) && (tcp_ok || default_enable_);
  dc.flags = 0;
  if (enable) dc.flags |= 0x01;
  if (estop)  dc.flags |= 0x02;

  int16_t speed = 0;
  int16_t steer = 0;
  uint8_t brake = 0;

  if (last_target_) {
    brake = std::min<uint8_t>(last_target_->brake_percent, 100);
    speed = last_target_->target_speed_mmps;
    steer = last_target_->target_steer_millirad;
    if (speed < 0) dc.flags |= 0x04; // Reverse flag for your MCU (optional)
  }

  dc.brake_percent         = brake;
  dc.target_speed_mmps     = speed;
  dc.target_steer_millirad = steer;

  maybe_auto_brake_lights(brake);
  return dc;
}

// Periodic
void I2cBridgeNode::tick_drive_cmd() {
  using clock = std::chrono::steady_clock;
  static auto prev = clock::now();
  auto start = clock::now();

  DriveCommandWire dc = build_drive_command();

  bool ok = false;
  auto w0 = clock::now();
  {
    std::lock_guard<std::mutex> lk(i2c_mtx_);
    (void)i2c_select(i2c_drv_.fd, addr_drive_);
    // Raw struct write -> Arduino Wire.onReceive() handler
    ok = i2c_write(i2c_drv_.fd, reinterpret_cast<const uint8_t*>(&dc), sizeof(dc));
  }
  auto w1 = clock::now();

  auto period_gap = std::chrono::duration_cast<std::chrono::milliseconds>(start - prev).count();
  auto write_ms   = std::chrono::duration_cast<std::chrono::milliseconds>(w1 - w0).count();
  prev = start;

  if (period_gap > 100 || write_ms > 50 || !ok) {
    RCLCPP_WARN(get_logger(), "TX gap=%ld ms write=%ld ms ok=%d errno=%d (%s)",
                (long)period_gap, (long)write_ms, (int)ok, errno, std::strerror(errno));
  }
}

void I2cBridgeNode::tick_drive_status() {
  DriveStatusWire st{};
  {
    std::lock_guard<std::mutex> lk(i2c_mtx_);
    (void)i2c_select(i2c_drv_.fd, addr_drive_);
    // Plain read -> Arduino Wire.onRequest() should provide sizeof(DriveStatusWire) bytes
    if (!i2c_read(i2c_drv_.fd, &st, sizeof(st))) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000, "Drive status read failed (errno=%d: %s)", errno, std::strerror(errno));
      return;
    }
  }

  vehicle_core::msg::DriveFeedback fb;
  fb.speed_mmps     = st.measured_speed_mmps;
  fb.steer_millirad = st.measured_steer_millirad;
  pub_drive_feedback_->publish(fb);

  vehicle_core::msg::DriveStatus ds;
  ds.gear       = current_gear();
  ds.braking    = current_braking(last_target_ ? last_target_->brake_percent : 0);
  ds.fault_bits = st.fault_bits;
  pub_drive_status_->publish(ds);

  if (st.fault_bits != last_fault_bits_) {
    last_fault_bits_ = st.fault_bits;
    std_msgs::msg::UInt16 f; f.data = st.fault_bits;
    pub_drive_fault_bits_->publish(f);
  }
}

// Utilities
void I2cBridgeNode::maybe_auto_brake_lights(uint8_t brake_percent) {
  const bool on = (brake_percent >= brake_light_threshold_);
  const uint8_t cmd_on  = 9;   // BrakeLightsOn (per your enum)
  const uint8_t cmd_off = 10;  // BrakeLightsOff
  const uint8_t want = on ? cmd_on : cmd_off;

  std::lock_guard<std::mutex> lks(lights_mtx_);
  if (lights_.brake == on) return; // no change
  if (send_light_cmd(want)) {
    lights_.brake = on;
    publish_lights_status_locked();
    last_light_cmd_ = want;
  } else {
    RCLCPP_WARN(get_logger(), "Brake light I2C write failed (errno=%d: %s)", errno, std::strerror(errno));
  }
}

bool I2cBridgeNode::send_light_cmd(uint8_t cmd_byte) {
  std::lock_guard<std::mutex> lk(i2c_mtx_);
  (void)i2c_select(i2c_lgt_.fd, addr_lighting_);
  return i2c_write(i2c_lgt_.fd, &cmd_byte, 1);
}

void I2cBridgeNode::publish_lights_status_locked() {
  vehicle_core::msg::LightsStatus msg;
  msg.brake_lights  = lights_.brake     ? 1 : 0;
  msg.reverse_lights= lights_.reverse   ? 1 : 0;
  msg.right_sig     = lights_.right_sig ? 1 : 0;
  msg.left_sig      = lights_.left_sig  ? 1 : 0;
  msg.headlights    = lights_.headlights? 1 : 0;
  msg.hazards       = lights_.hazards   ? 1 : 0;
  pub_lights_status_->publish(msg);
}

uint8_t I2cBridgeNode::current_gear() const {
  if (!last_target_) return 0; // Neutral/Coast
  const auto s = last_target_->target_speed_mmps;
  if (s > 0) return 2; // Forward
  if (s < 0) return 3; // Reverse
  return 1;            // Coast
}

bool I2cBridgeNode::current_braking(uint8_t brake_percent) const {
  return brake_percent >= static_cast<uint8_t>(std::clamp(brake_light_threshold_, 0, 100));
}

} // namespace vehicle_core

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::I2cBridgeNode)
