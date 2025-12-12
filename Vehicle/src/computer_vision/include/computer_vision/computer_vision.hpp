#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/string.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <memory>
#include <string>
#include <vector>

namespace vehicle_core {

struct Detection {
  int class_id;
  float score;
  cv::Rect box; // x,y,w,h in pixels
};

class ComputerVisionNode : public rclcpp::Node {
public:
  explicit ComputerVisionNode(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
  ~ComputerVisionNode() override = default;

private:
  void on_image(const sensor_msgs::msg::Image::SharedPtr msg);
  bool load_model();
  void preprocess(const cv::Mat &frame, cv::Mat &blob);
  std::vector<Detection> postprocess(const cv::Mat &frame, const cv::Mat &pred, float conf_thresh, float nms_thresh);
  void draw_detections(cv::Mat &img, const std::vector<Detection> &dets);

  // ROS
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_annotated_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_detections_;

  // Model / infer
  cv::dnn::Net net_;
  int input_width_;
  int input_height_;
  float conf_thresh_;
  float nms_thresh_;
  std::string model_path_;
  std::vector<std::string> class_names_;
  std::string in_topic_;
  std::string annotated_topic_;
  std::string detections_topic_;
  std::string frame_id_;
};

} // namespace vehicle_core