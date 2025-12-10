#include "vehicle_core/rtsp_streamer_node.hpp"

#include <gst/video/video.h>  // for caps/types if needed
#include <gst/gst.h>

namespace vehicle_core {

RtspStreamerNode::RtspStreamerNode(const rclcpp::NodeOptions& options)
: rclcpp::Node("rtsp_streamer", options)
{
  // GStreamer init (safe to call multiple times)
  gst_init(nullptr, nullptr);

  // Parameters — keep consistent with your camera node
  width_  = declare_parameter<int>("width", 2112);
  height_ = declare_parameter<int>("height", 1568);
  fps_    = declare_parameter<int>("fps", 15);

  // --- Create RTSP server ---
  server_ = gst_rtsp_server_new();
  // default port 8554, change with g_object_set(server_, "service", "8554", NULL) if needed

  GstRTSPMountPoints* mounts = gst_rtsp_server_get_mount_points(server_);

  factory_ = gst_rtsp_media_factory_new();
  gst_rtsp_media_factory_set_latency(factory_, 0);

  // Pipeline: appsrc → videoconvert → x264enc → rtph264pay
  // NOTE: appsrc is named "src" so we can find it later.
  const std::string launch_desc =
    "( appsrc name=src is-live=true format=time do-timestamp=true block=false ! "
    "queue max-size-buffers=1 leaky=downstream ! "
    "videoconvert ! videoscale ! "
    "video/x-raw,format=NV12,width=1280,height=720,framerate=15/1 ! "
    "mpph264enc bps=2500000 ! "
    "h264parse config-interval=-1 ! "
    "rtph264pay name=pay0 pt=96 )";

  gst_rtsp_media_factory_set_launch(factory_, launch_desc.c_str());
  gst_rtsp_media_factory_set_shared(factory_, TRUE);

  // Connect media-configure to grab appsrc when the pipeline is built
  g_signal_connect(factory_, "media-configure",
                   G_CALLBACK(&RtspStreamerNode::on_media_configure_static), this);

  // Mount at /stream
  gst_rtsp_mount_points_add_factory(mounts, "/stream", factory_);
  g_object_unref(mounts);

  // Attach server to default main context
  if (gst_rtsp_server_attach(server_, nullptr) == 0) {
    RCLCPP_ERROR(get_logger(), "Failed to attach RTSP server");
    throw std::runtime_error("RTSP server attach failed");
  }

  RCLCPP_INFO(get_logger(),
              "RTSP stream ready at rtsp://<pi-ip>:8554/stream (width=%d height=%d fps=%d)",
              width_, height_, fps_);

  // Start GLib main loop in a separate thread
  loop_ = g_main_loop_new(nullptr, FALSE);
  loop_thread_ = std::thread([this]() {
    g_main_loop_run(loop_);
  });

  // --- ROS subscriber ---
  auto qos = rclcpp::QoS(1);
  qos.best_effort();
  qos.durability_volatile();
  sub_ = create_subscription<sensor_msgs::msg::Image>(
    "/camera/image_raw",
    qos,
    std::bind(&RtspStreamerNode::imageCallback, this, std::placeholders::_1));

  RCLCPP_INFO(get_logger(), "rtsp_streamer node up, subscribing to /camera/image_raw");
}

RtspStreamerNode::~RtspStreamerNode()
{
  RCLCPP_INFO(get_logger(), "Shutting down rtsp_streamer node");

  {
    std::lock_guard<std::mutex> lock(appsrc_mutex_);
    if (appsrc_) {
      // let GStreamer clean it with the pipeline; don't unref directly here
      appsrc_ = nullptr;
    }
  }

  if (loop_) {
    g_main_loop_quit(loop_);
  }
  if (loop_thread_.joinable()) {
    loop_thread_.join();
  }
  if (loop_) {
    g_main_loop_unref(loop_);
    loop_ = nullptr;
  }
  if (server_) {
    g_object_unref(server_);
    server_ = nullptr;
  }
}

// static wrapper
void RtspStreamerNode::on_media_configure_static(GstRTSPMediaFactory* factory,
                                                 GstRTSPMedia* media,
                                                 gpointer user_data)
{
  auto* self = static_cast<RtspStreamerNode*>(user_data);
  self->on_media_configure(media);
}

// called when a client connects and the pipeline is created
void RtspStreamerNode::on_media_configure(GstRTSPMedia* media)
{
  GstElement* pipeline = gst_rtsp_media_get_element(media);
  GstElement* src = gst_bin_get_by_name_recurse_up(GST_BIN(pipeline), "src");
  if (!src) {
    RCLCPP_ERROR(get_logger(), "Failed to find appsrc element 'src' in pipeline");
    return;
  }

  // Caps for the frames we will push (BGR from ROS)
  GstCaps* caps = gst_caps_new_simple(
    "video/x-raw",
    "format", G_TYPE_STRING, "BGR",
    "width", G_TYPE_INT, width_,
    "height", G_TYPE_INT, height_,
    "framerate", GST_TYPE_FRACTION, fps_, 1,
    nullptr);

  g_object_set(src,
               "is-live", TRUE,
               "format", GST_FORMAT_TIME,
               "block", TRUE,
               nullptr);

  gst_app_src_set_caps(GST_APP_SRC(src), caps);
  gst_caps_unref(caps);

  {
    std::lock_guard<std::mutex> lock(appsrc_mutex_);
    appsrc_ = src;
  }

  RCLCPP_INFO(get_logger(), "RTSP media configured, appsrc ready");
}

// ROS image callback: push frames into appsrc
void RtspStreamerNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  GstElement* src = nullptr;
  {
    std::lock_guard<std::mutex> lock(appsrc_mutex_);
    src = appsrc_;
  }

  // No client / pipeline not ready yet
  if (!src) {
    return;
  }

  // Expecting BGR8 to match caps
  if (msg->encoding != "bgr8") {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000,
                         "Image encoding is '%s', expected 'bgr8'",
                         msg->encoding.c_str());
    return;
  }

  const size_t data_size = msg->data.size();
  if (data_size == 0) {
    return;
  }

  // Allocate GstBuffer and copy image data
  GstBuffer* buffer = gst_buffer_new_allocate(nullptr, data_size, nullptr);
  if (!buffer) {
    RCLCPP_WARN(get_logger(), "Failed to allocate GstBuffer");
    return;
  }

  GstMapInfo map;
  if (!gst_buffer_map(buffer, &map, GST_MAP_WRITE)) {
    RCLCPP_WARN(get_logger(), "Failed to map GstBuffer");
    gst_buffer_unref(buffer);
    return;
  }

  std::memcpy(map.data, msg->data.data(), data_size);
  gst_buffer_unmap(buffer, &map);

  // Let GStreamer timestamp if we want to keep it simple; skip PTS for now
  // If needed later, we can set GST_BUFFER_PTS and DURATION.

  GstFlowReturn ret = gst_app_src_push_buffer(GST_APP_SRC(src), buffer);

  if (ret == GST_FLOW_FLUSHING || ret == GST_FLOW_EOS) {
    // Pipeline not ready / shutting down – safe to ignore
    return;
  }

  if (ret != GST_FLOW_OK) {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000,
                         "gst_app_src_push_buffer returned %d", ret);
  }
}

} // namespace vehicle_core

// Optional: register as a component if you use composition
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::RtspStreamerNode)
