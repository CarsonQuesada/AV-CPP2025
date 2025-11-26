#include "vehicle_core/gt_u7_gps_node.hpp"

#include <algorithm>
#include <chrono>
#include <limits>
#include <stdexcept>
#include <string>

namespace vehicle_core {

GtU7GpsNode::GtU7GpsNode(const rclcpp::NodeOptions& opts)
: rclcpp::Node("gt_u7_gps_node", opts) {
  // ---- Parameters (declare + get) ----
  port_          = this->declare_parameter<std::string>("port", "/dev/ttyS0");
  baud_rate_     = this->declare_parameter<int>("baud_rate", 115200);
  nmea_rate_     = this->declare_parameter<int>("nmea_rates", 5);
  frame_id_      = this->declare_parameter<std::string>("frame_id", "gps");
  publish_hz_    = this->declare_parameter<double>("publish_hz", 10.0);
  uere_m_         = this->declare_parameter<double>("uere_m", 5.0);
  min_sigma_xy_m_ = this->declare_parameter<double>("min_sigma_xy", 1.0);
  min_sigma_z_m_  = this->declare_parameter<double>("min_sigma_z", 2.0);
  vertical_scale_ = this->declare_parameter<double>("vertical_scale", 2.0);
  std::string mode_str = this->declare_parameter<std::string>("mode", "GPS_10HZ"); // or "GPS_GLO_5HZ"

  // ---- Open + configure device ----
  int tries = 3;
  bool failedConfig = true;
  for (int i = 0; i < tries; i++) {
    if (!gps_.open(port_, baud_rate_)) {
      RCLCPP_ERROR(get_logger(), "Failed to open %s @ %d", port_.c_str(), baud_rate_);
      continue;
    }
    if (!gps_.cfgBaudRate(baud_rate_)) {
      RCLCPP_ERROR(get_logger(), "Failed to set baud rate");
      continue;
    }
    if (!gps_.cfgNmeaRates(nmea_rate_)) {
      RCLCPP_ERROR(get_logger(), "Failed to set NMEA rates");
      continue;
    }
    if (!gps_.cfgRateHz(nmea_rate_)) {
      RCLCPP_ERROR(get_logger(), "Failed to set navigation rate");
      continue;
    }
    if (!gps_.cfgNmeaRatesPubx40(nmea_rate_)) {
      RCLCPP_ERROR(get_logger(), "Failed to set NMEA rates PUBX40");
      continue;
    }
    if (!gps_.cfgNmeaNoFilter()) {
      RCLCPP_ERROR(get_logger(), "Failed to set NMEA no filter");
      continue;
    }
    if (!gps_.cfgNavModel(GtU7Gps::DynModel::AUTOMOTIVE)) {
      RCLCPP_ERROR(get_logger(), "Failed to set navigation model");
      continue;
    }
    if (!gps_.cfgSBAS()) {
      RCLCPP_ERROR(get_logger(), "Failed to enable SBAS");
      continue;
    }
    failedConfig = false;
    break;
  }

  if (failedConfig)
    throw std::runtime_error("Failed to Configure GPS module. Tried " + std::to_string(tries) + " times.");
  else {
    int hz_now = gps_.pollEffectiveRateHz();
    RCLCPP_INFO(get_logger(), "CFG-RATE reports %d Hz", hz_now);
    gps_.saveToBBR();
  }

  RCLCPP_INFO(get_logger(), "GT-U7 configured on %s", port_.c_str());

  // ---- Publisher ----
  pub_fix_ = this->create_publisher<sensor_msgs::msg::NavSatFix>(
      "fix", rclcpp::SensorDataQoS());

  // ---- Timer ----
  using namespace std::chrono;
  auto period = duration<double>(1.0 / std::max(1.0, publish_hz_));
  timer_ = this->create_wall_timer(
      duration_cast<std::chrono::milliseconds>(period),
      std::bind(&GtU7GpsNode::onTimer, this));
}

void GtU7GpsNode::onTimer() {
  // Read one snapshot; short timeout keeps the node responsive even with sparse data
  const int live_hz = std::max(1, gps_.pollEffectiveRateHz());
  const int window_ms = std::clamp(static_cast<int>(600.0 / live_hz), 60, 180);
  auto fx = gps_.readFix(window_ms);
  if (!fx) {
    // no fresh data right now; skip publish
    return;
  }

  // Compose NavSatFix
  sensor_msgs::msg::NavSatFix msg;
  msg.header.stamp = this->now();
  msg.header.frame_id = frame_id_;

  // Status: FIX vs NO_FIX.
  // (GGA fix_quality: 0=no, 1=GPS, 2=DGPS/SBAS)
  sensor_msgs::msg::NavSatStatus status;
  if (fx->fix_quality && *fx->fix_quality > 0 && fx->valid) {
    status.status = sensor_msgs::msg::NavSatStatus::STATUS_FIX;
  } else {
    status.status = sensor_msgs::msg::NavSatStatus::STATUS_NO_FIX;
  }
  status.service = sensor_msgs::msg::NavSatStatus::SERVICE_GPS; // primary
  msg.status = status;

  // Coordinates (if missing, leave NaNs to signal “unknown”)
  msg.latitude  = fx->lat_deg.value_or(std::numeric_limits<double>::quiet_NaN());
  msg.longitude = fx->lon_deg.value_or(std::numeric_limits<double>::quiet_NaN());
  msg.altitude  = fx->alt_m.value_or(std::numeric_limits<double>::quiet_NaN());

  double sigma_e_m, sigma_n_m, sigma_u_m;

  // Prefer GST per-axis std devs
  if (fx->sdev_lat_m && fx->sdev_lon_m) {
    sigma_n_m = std::max(min_sigma_xy_m_, *fx->sdev_lat_m);
    sigma_e_m = std::max(min_sigma_xy_m_, *fx->sdev_lon_m);
    sigma_u_m = std::max(min_sigma_z_m_,  fx->sdev_alt_m.value_or(*fx->sdev_lat_m * vertical_scale_));
  } else {
    // Fallback: HDOP/UERE for horizontal, VDOP/UERE (or scale) for vertical
    const double hdop = fx->hdop.value_or(std::numeric_limits<double>::quiet_NaN());
    const double vdop = fx->vdop.value_or(std::numeric_limits<double>::quiet_NaN());
    const double sigma_xy = (std::isfinite(hdop) && hdop>0) ? std::max(min_sigma_xy_m_, hdop*uere_m_)
                                                            : std::max(min_sigma_xy_m_, 3.0);
    const double sigma_z  = (std::isfinite(vdop) && vdop>0) ? std::max(min_sigma_z_m_, vdop*uere_m_*1.5)
                                                            : std::max(min_sigma_z_m_, sigma_xy*vertical_scale_);
    sigma_e_m = sigma_xy;
    sigma_n_m = sigma_xy;
    sigma_u_m = sigma_z;
  }

  msg.position_covariance_type = sensor_msgs::msg::NavSatFix::COVARIANCE_TYPE_DIAGONAL_KNOWN;
  msg.position_covariance[0] = sigma_e_m * sigma_e_m;
  msg.position_covariance[4] = sigma_n_m * sigma_n_m;
  msg.position_covariance[8] = sigma_u_m * sigma_u_m;

  pub_fix_->publish(msg);
}

} // namespace vehicle_core

// Register as a component
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::GtU7GpsNode)
