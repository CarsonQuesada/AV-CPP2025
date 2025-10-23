#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>

namespace vehicle_core {

class GstCameraNode : public rclcpp::Node {
public:
  explicit GstCameraNode(const rclcpp::NodeOptions& opts = rclcpp::NodeOptions());
  ~GstCameraNode() override;

private:
  static GstFlowReturn on_new_sample_static(GstAppSink* sink, gpointer user_data);
  GstFlowReturn on_new_sample(GstAppSink* sink);

  std::string device_, topic_, frame_id_;
  int width_{0}, height_{0}, fps_{0};

  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
  GstElement* pipeline_{nullptr};
  GMainLoop* loop_{nullptr};
  std::thread loop_thread_;
};

} // namespace vehicle_core
