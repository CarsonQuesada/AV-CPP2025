// #pragma once
#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_msgs/msg/u_int16.hpp>

#include "vehicle_core/msg/drive_target.hpp"
#include "vehicle_core/msg/lights_command.hpp"
#include "vehicle_core/msg/lights_status.hpp"
#include "vehicle_core/msg/drive_status.hpp"
#include "vehicle_core/msg/drive_feedback.hpp"

#include <mutex>
#include <atomic>
#include <string>
#include <cstdint>

struct I2cDevice {
  int fd{-1};
  std::string path{"/dev/i2c-1"};
  uint8_t addr{0x00};
};

#pragma pack(push,1)
struct DriveCommandWire {
  uint8_t  flags;                  // bit0: enable, bit1: estop, bit2: reverse_ok
  uint8_t  brake_percent;          // 0..100
  int16_t  target_speed_mmps;      // signed mm/s
  int16_t  target_steer_millirad;  // signed mrad
};

struct DriveStatusWire {
  int16_t  measured_speed_mmps;     // signed mm/s
  int16_t  measured_steer_millirad; // signed mrad
  uint16_t fault_bits;              // 1=WATCHDOG,2=ESTOP,4=OVERCURR(placeholder)
};
#pragma pack(pop)

namespace vehicle_core {

class I2cBridgeNode : public rclcpp::Node {
public:
  explicit I2cBridgeNode(const rclcpp::NodeOptions& opts);

private:
  // Params
  std::string i2c_path_;
  uint8_t addr_lighting_{0x15}, addr_drive_{0x20};
  int drive_cmd_hz_{50};
  int drive_status_hz_{50};
  int brake_light_threshold_{10};
  bool default_enable_{true};

  // I2C
  I2cDevice i2c_drv_, i2c_lgt_;
  std::mutex i2c_mtx_;

  // State
  std::atomic_bool estop_{false};
  std::atomic<uint8_t> tcp_state_{0}; // 0=Disc,1=Listen,2=Connected
  vehicle_core::msg::DriveTarget::SharedPtr last_target_;
  uint8_t last_light_cmd_{0};
  uint16_t last_fault_bits_{0};

  // Lighting state the node maintains & publishes
  struct LightsState {
    bool brake{false};
    bool reverse{false};
    bool right_sig{false};
    bool left_sig{false};
    bool headlights{false};
    bool hazards{false};
  };
  LightsState lights_;
  std::mutex lights_mtx_;

  // ROS IO
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_estop_;
  rclcpp::Subscription<vehicle_core::msg::DriveTarget>::SharedPtr sub_drive_target_;
  rclcpp::Subscription<vehicle_core::msg::LightsCommand>::SharedPtr sub_lights_;
  rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr sub_tcp_state_;

  rclcpp::Publisher<vehicle_core::msg::DriveStatus>::SharedPtr   pub_drive_status_;
  rclcpp::Publisher<vehicle_core::msg::DriveFeedback>::SharedPtr pub_drive_feedback_;
  rclcpp::Publisher<std_msgs::msg::UInt16>::SharedPtr            pub_drive_fault_bits_;
  rclcpp::Publisher<vehicle_core::msg::LightsStatus>::SharedPtr  pub_lights_status_;

  // Timers
  rclcpp::TimerBase::SharedPtr t_drive_cmd_;
  rclcpp::TimerBase::SharedPtr t_drive_status_;

  // I2C low-level
  bool i2c_open(I2cDevice& dev, const char* what);
  bool i2c_select(int fd, uint8_t addr);
  bool i2c_write(int fd, const void* buf, size_t n);
  bool i2c_read(int fd, void* buf, size_t n); // <-- plain read, no register

  static inline int16_t clamp_i16(int64_t v) {
    return static_cast<int16_t>(std::clamp<int64_t>(v, -32768, 32767));
  }

  // Builders
  DriveCommandWire build_drive_command();

  // Callbacks
  void on_estop(const std_msgs::msg::Bool::SharedPtr);
  void on_drive_target(const vehicle_core::msg::DriveTarget::SharedPtr);
  void on_lights(const vehicle_core::msg::LightsCommand::SharedPtr);
  void on_tcp_state(const std_msgs::msg::UInt8::SharedPtr);

  // Periodic jobs
  void tick_drive_cmd();
  void tick_drive_status();

  // Utilities
  void maybe_auto_brake_lights(uint8_t brake_percent);
  void publish_lights_status_locked(); // assumes lights_mtx_ held
  bool send_light_cmd(uint8_t cmd_byte); // returns I2C ok
  uint8_t current_gear() const;
  bool current_braking(uint8_t brake_percent) const;
  rclcpp::QoS qos_transient_reliable(size_t depth=1) const;
};

} // namespace vehicle_core
