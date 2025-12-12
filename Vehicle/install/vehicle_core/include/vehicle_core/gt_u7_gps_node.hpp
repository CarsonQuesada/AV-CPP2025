#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/nav_sat_status.hpp>
#include <string>

#include "Devices/GtU7Gps.hpp"

namespace vehicle_core {

class GtU7GpsNode : public rclcpp::Node {
public:
  // Defaulted options so you can use as component or standalone
  explicit GtU7GpsNode(const rclcpp::NodeOptions& opts = rclcpp::NodeOptions());

private:
  void onTimer();

  // ---- members ----
  GtU7Gps gps_;
  GtU7Gps::Mode mode_{GtU7Gps::Mode::GPS_10HZ};
  std::optional<GtU7Gps::Fix> last_gga_;
  std::optional<GtU7Gps::Fix> last_rmc_;
  std::string port_, frame_id_;
  int baud_rate_{115200};
  int nmea_rate_{5};
  double publish_hz_{10.0};
  double uere_m_{5.0};   // typical standalone GPS
  double min_sigma_xy_m_{1.0};
  double min_sigma_z_m_{2.0};
  double vertical_scale_{2.0};
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr pub_fix_;
  rclcpp::TimerBase::SharedPtr timer_;
};

} // namespace vehicle_core
