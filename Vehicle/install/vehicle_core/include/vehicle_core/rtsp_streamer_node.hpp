#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <gst/app/gstappsrc.h>

#include <thread>
#include <mutex>

namespace vehicle_core {

class RtspStreamerNode : public rclcpp::Node
{
public:
  explicit RtspStreamerNode(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
  ~RtspStreamerNode() override;

private:
  // ROS callback
  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);

  // RTSP media configure callbacks
  static void on_media_configure_static(GstRTSPMediaFactory* factory,
                                        GstRTSPMedia* media,
                                        gpointer user_data);
  void on_media_configure(GstRTSPMedia* media);

  // GStreamer / RTSP
  GstRTSPServer* server_ = nullptr;
  GstRTSPMediaFactory* factory_ = nullptr;
  GMainLoop* loop_ = nullptr;
  std::thread loop_thread_;

  // appsrc we push frames into
  GstElement* appsrc_ = nullptr;
  std::mutex appsrc_mutex_;

  // ROS
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;

  // parameters (should match camera node)
  int width_;
  int height_;
  int fps_;
  std::string image_topic_;
  std::string service_;         // RTSP port as string, e.g., "8554"
  std::string mount_point_;  // RTSP path, e.g., "/stream"
};

} // namespace vehicle_core
