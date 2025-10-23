#include "vehicle_core/gst_camera_node.hpp"

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <gst/video/video.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

namespace vehicle_core {

GstCameraNode::GstCameraNode(const rclcpp::NodeOptions& opts)
: rclcpp::Node("gst_camera", opts)
{
  // init GStreamer once (safe to call multiple times)
  gst_init(nullptr, nullptr);

  device_   = declare_parameter<std::string>("device", "/dev/video11");
  width_    = declare_parameter<int>("width", 2112);
  height_   = declare_parameter<int>("height", 1568);
  fps_      = declare_parameter<int>("fps", 15);
  topic_    = declare_parameter<std::string>("topic", "/camera/image_raw");
  frame_id_ = declare_parameter<std::string>("frame_id", "camera_link");
  int qdepth= declare_parameter<int>("queue_depth", 5);

  auto qos = rclcpp::QoS(rclcpp::KeepLast(qdepth));
  qos.reliable();                // make it compatible with web_video_server defaults
  qos.durability_volatile();
  pub_ = create_publisher<sensor_msgs::msg::Image>(topic_, qos);

  std::string pipe =
    "v4l2src device=" + device_ + " io-mode=2 do-timestamp=true ! "
    "video/x-raw,format=NV12,width=" + std::to_string(width_) +
    ",height=" + std::to_string(height_) + ",framerate=" + std::to_string(fps_) + "/1 ! "
    "videoconvert ! video/x-raw,format=BGR ! "
    "queue leaky=downstream max-size-buffers=1 ! "
    "appsink name=appsink emit-signals=true sync=false max-buffers=1 drop=true "
    "caps=video/x-raw,format=BGR";

  RCLCPP_INFO(get_logger(), "GStreamer pipeline:\n%s", pipe.c_str());

  pipeline_ = gst_parse_launch(pipe.c_str(), nullptr);
  if (!pipeline_) {
    throw std::runtime_error("gst_parse_launch failed");
  }

  auto* appsink = gst_bin_get_by_name(GST_BIN(pipeline_), "appsink");
  if (!appsink) {
    throw std::runtime_error("appsink not found");
  }
  g_signal_connect(appsink, "new-sample", G_CALLBACK(&GstCameraNode::on_new_sample_static), this);
  gst_object_unref(appsink);

  if (gst_element_set_state(pipeline_, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
    throw std::runtime_error("pipeline PLAYING failed");
  }

  // run a GLib loop so GStreamer can dispatch signals
  loop_thread_ = std::thread([this]{
    GMainContext* ctx = g_main_context_new();
    g_main_context_push_thread_default(ctx);
    loop_ = g_main_loop_new(ctx, FALSE);
    g_main_loop_run(loop_);
    g_main_loop_unref(loop_);
    g_main_context_pop_thread_default(ctx);
    g_main_context_unref(ctx);
  });

  RCLCPP_INFO(get_logger(), "gst_camera component up, publishing %s", topic_.c_str());
}

GstCameraNode::~GstCameraNode() {
  if (pipeline_) {
    gst_element_set_state(pipeline_, GST_STATE_NULL);
    gst_object_unref(pipeline_);
    pipeline_ = nullptr;
  }
  if (loop_) g_main_loop_quit(loop_);
  if (loop_thread_.joinable()) loop_thread_.join();
}

GstFlowReturn GstCameraNode::on_new_sample_static(GstAppSink* sink, gpointer ud) {
  return static_cast<GstCameraNode*>(ud)->on_new_sample(sink);
}

GstFlowReturn GstCameraNode::on_new_sample(GstAppSink* sink) {
  GstSample* sample = gst_app_sink_pull_sample(sink);
  if (!sample) return GST_FLOW_ERROR;

  // Read width/height from caps (no gstvideo dependency)
  int w = 0, h = 0;
  {
    GstCaps* caps = gst_sample_get_caps(sample);
    if (!caps) { gst_sample_unref(sample); return GST_FLOW_ERROR; }
    const GstStructure* s = gst_caps_get_structure(caps, 0);
    gst_structure_get_int(s, "width",  &w);
    gst_structure_get_int(s, "height", &h);
    if (w <= 0 || h <= 0) { gst_sample_unref(sample); return GST_FLOW_ERROR; }
  }

  // Map buffer and compute a safe row step for single-plane BGR
  GstBuffer* buffer = gst_sample_get_buffer(sample);
  GstMapInfo map;
  if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
    gst_sample_unref(sample);
    return GST_FLOW_ERROR;
  }

  // BGR is one plane; stride may be >= w*3. Derive from total size.
  // (map.size should be at least h * (w*3); if larger, it's padded.)
  size_t step = map.size / static_cast<size_t>(h);
  if (step < static_cast<size_t>(w) * 3) step = static_cast<size_t>(w) * 3;

  // Build a view with the correct step, then clone so it's valid after unmap
  cv::Mat bgr_view(h, w, CV_8UC3, const_cast<guint8*>(map.data), step);
  cv::Mat bgr = bgr_view.clone();

  gst_buffer_unmap(buffer, &map);
  gst_sample_unref(sample);

  auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", bgr).toImageMsg();
  msg->header.stamp = now();
  msg->header.frame_id = frame_id_;
  pub_->publish(*msg);
  return GST_FLOW_OK;
}

} // namespace vehicle_core

// Register as a component
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::GstCameraNode)
