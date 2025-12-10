#include "computer_vision/computer_vision.hpp"
#include <rclcpp_components/register_node_macro.hpp>

namespace vehicle_core {

using std::placeholders::_1;

ComputerVisionNode::ComputerVisionNode(const rclcpp::NodeOptions& options)
: Node("computer_vision", options)
{
  // Parameters with sensible defaults
  model_path_      = declare_parameter<std::string>("model_path", "yolov8n.onnx");
  input_width_     = declare_parameter<int>("input_width", 640);
  input_height_    = declare_parameter<int>("input_height", 640);
  conf_thresh_     = declare_parameter<double>("conf_threshold", 0.25);
  nms_thresh_      = declare_parameter<double>("nms_threshold", 0.45);
  in_topic_        = declare_parameter<std::string>("image_topic", "/camera/image_raw");
  annotated_topic_ = declare_parameter<std::string>("annotated_topic", "/camera/image_annotated");
  detections_topic_= declare_parameter<std::string>("detections_topic", "/camera/detections");
  frame_id_        = declare_parameter<std::string>("frame_id", "camera_link");

  // Optional: small set of COCO class names; modify or load from file if you want full list.
  class_names_ = {
    "person","bicycle","car","motorcycle","airplane","bus","train","truck","boat","traffic light",
    "fire hydrant","stop sign","parking meter","bench","bird","cat","dog","horse","sheep","cow",
    "elephant","bear","zebra","giraffe","backpack","umbrella","handbag","tie","suitcase","frisbee",
    "skis","snowboard","sports ball","kite","baseball bat","baseball glove","skateboard","surfboard","tennis racket","bottle",
    "wine glass","cup","fork","knife","spoon","bowl","banana","apple","sandwich","orange",
    "broccoli","carrot","hot dog","pizza","donut","cake","chair","couch","potted plant","bed",
    "dining table","toilet","tv","laptop","mouse","remote","keyboard","cell phone","microwave","oven",
    "toaster","sink","refrigerator","book","clock","vase","scissors","teddy bear","hair drier","toothbrush"
  };

  RCLCPP_INFO(get_logger(), "Computer vision node: model=%s input=%dx%d conf=%.2f nms=%.2f",
              model_path_.c_str(), input_width_, input_height_, conf_thresh_, nms_thresh_);

  // Load model
  if (!load_model()) {
    RCLCPP_ERROR(get_logger(), "Failed to load model '%s'", model_path_.c_str());
    throw std::runtime_error("failed to load model");
  }

  // Publishers & subscriber
  // Match QoS from publisher (keep it simple: default QoS)
  pub_annotated_ = create_publisher<sensor_msgs::msg::Image>(annotated_topic_, rclcpp::QoS(5));
  pub_detections_ = create_publisher<std_msgs::msg::String>(detections_topic_, rclcpp::QoS(5));

  // Subscribe to image topic (shared with gst_camera)
  sub_ = create_subscription<sensor_msgs::msg::Image>(
    in_topic_, rclcpp::SensorDataQoS(),
    std::bind(&ComputerVisionNode::on_image, this, _1)
  );

  RCLCPP_INFO(get_logger(), "computer_vision component ready, subscribing to %s", in_topic_.c_str());
}

bool ComputerVisionNode::load_model() {
  try {
    net_ = cv::dnn::readNet(model_path_);
    // Preferable to use CPU by default; you can change to CUDA if supported:
    net_.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
    net_.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
  } catch (const cv::Exception &e) {
    RCLCPP_ERROR(get_logger(), "OpenCV exception while loading model: %s", e.what());
    return false;
  }
  return true;
}

void ComputerVisionNode::preprocess(const cv::Mat &frame, cv::Mat &blob) {
  // Resize with letterbox (preserve aspect ratio) to input size expected by model
  int w = frame.cols;
  int h = frame.rows;
  float r = std::min(input_width_ / (float)w, input_height_ / (float)h);
  int new_w = static_cast<int>(round(w * r));
  int new_h = static_cast<int>(round(h * r));

  cv::Mat resized;
  cv::resize(frame, resized, cv::Size(new_w, new_h));

  // create a padded image (letterbox) with black borders
  cv::Mat canvas(cv::Size(input_width_, input_height_), frame.type(), cv::Scalar(114,114,114));
  int x_offset = (input_width_ - new_w) / 2;
  int y_offset = (input_height_ - new_h) / 2;
  resized.copyTo(canvas(cv::Rect(x_offset, y_offset, resized.cols, resized.rows)));

  // convert BGR->RGB and scale to [0,1]
  cv::Mat rgb;
  cv::cvtColor(canvas, rgb, cv::COLOR_BGR2RGB);
  rgb.convertTo(rgb, CV_32F, 1.0/255.0);

  // Create blob: shape [1,3,input_h,input_w]
  blob = cv::dnn::blobFromImage(rgb); // default orders channels correctly
  // We'll need offsets and scale to convert outputs back to original image
  // We'll store offsets via a thread-local/global capture in inference step below
}

std::vector<Detection> ComputerVisionNode::postprocess(const cv::Mat &frame, const cv::Mat &pred, float conf_thresh, float nms_thresh) {
  // pred: Nx(5+num_classes) OR 1xM where M is flattened; we handle row-wise matrix
  // We'll parse rows: [xc, yc, w, h, obj_conf, class_scores...]
  std::vector<int> class_ids;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;

  int rows = pred.rows;
  int cols = pred.cols; // 5 + num_classes

  // Determine padding/scale used in preprocess to map back to original
  float r = std::min(input_width_ / (float)frame.cols, input_height_ / (float)frame.rows);
  int new_w = static_cast<int>(round(frame.cols * r));
  int new_h = static_cast<int>(round(frame.rows * r));
  int x_offset = (input_width_ - new_w) / 2;
  int y_offset = (input_height_ - new_h) / 2;

  for (int i = 0; i < rows; ++i) {
    const float* row = pred.ptr<float>(i);
    float xc = row[0];
    float yc = row[1];
    float w = row[2];
    float h = row[3];
    float obj_conf = row[4];

    // find best class
    int num_classes = cols - 5;
    float best_score = 0.0f;
    int best_class = -1;
    for (int c = 0; c < num_classes; ++c) {
      float cls_score = row[5 + c];
      if (cls_score > best_score) {
        best_score = cls_score;
        best_class = c;
      }
    }
    float score = obj_conf * best_score;
    if (score < conf_thresh) continue;

    // Convert xywh (relative to network input) to box in original image pixels
    // If model outputs normalized coords [0..1], multiply by input size. Many ONNX models output absolute coords relative to input size -- we assume they are normalized in [0..input_size]
    // We'll treat them as absolute in pixels of input size.
    float x = xc;
    float y = yc;
    float bw = w;
    float bh = h;

    // if the model outputs normalized [0..1], uncomment the following block:
    // x *= input_width_; y *= input_height_; bw *= input_width_; bh *= input_height_;

    // Now shift by letterbox offset and scale back to original frame
    float x1 = (x - bw/2.0f - x_offset) / r;
    float y1 = (y - bh/2.0f - y_offset) / r;
    float x2 = (x + bw/2.0f - x_offset) / r;
    float y2 = (y + bh/2.0f - y_offset) / r;

    int ix1 = std::max(0, (int)std::floor(x1));
    int iy1 = std::max(0, (int)std::floor(y1));
    int ix2 = std::min(frame.cols - 1, (int)std::ceil(x2));
    int iy2 = std::min(frame.rows - 1, (int)std::ceil(y2));
    int bw_int = std::max(0, ix2 - ix1);
    int bh_int = std::max(0, iy2 - iy1);

    boxes.emplace_back(ix1, iy1, bw_int, bh_int);
    confidences.push_back(score);
    class_ids.push_back(best_class);
  }

  // NMS
  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, conf_thresh, nms_thresh, indices);

  std::vector<Detection> dets;
  dets.reserve(indices.size());
  for (int idx : indices) {
    Detection d;
    d.class_id = class_ids[idx];
    d.score = confidences[idx];
    d.box = boxes[idx];
    dets.push_back(d);
  }
  return dets;
}

void ComputerVisionNode::draw_detections(cv::Mat &img, const std::vector<Detection> &dets) {
  for (const auto &d : dets) {
    cv::rectangle(img, d.box, cv::Scalar(0, 255, 0), 2);
    std::string label = (d.class_id >= 0 && d.class_id < (int)class_names_.size())
                        ? class_names_[d.class_id]
                        : std::to_string(d.class_id);
    char buf[64];
    snprintf(buf, sizeof(buf), "%s: %.2f", label.c_str(), d.score);
    int baseLine = 0;
    cv::Size label_size = cv::getTextSize(buf, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    int top = std::max(d.box.y, label_size.height);
    cv::rectangle(img, cv::Point(d.box.x, top - label_size.height - 4),
                  cv::Point(d.box.x + label_size.width, top + baseLine - 4),
                  cv::Scalar(0, 255, 0), cv::FILLED);
    cv::putText(img, buf, cv::Point(d.box.x, top - 4),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1);
  }
}

void ComputerVisionNode::on_image(const sensor_msgs::msg::Image::SharedPtr msg) {
  // Convert ROS image to OpenCV
  cv_bridge::CvImagePtr cv_ptr;
  try {
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
  } catch (cv_bridge::Exception &e) {
    RCLCPP_ERROR(get_logger(), "cv_bridge exception: %s", e.what());
    return;
  }
  cv::Mat frame = cv_ptr->image;
  if (frame.empty()) return;

  // Preprocess
  cv::Mat blob;
  preprocess(frame, blob);

  // Set input and run
  net_.setInput(blob);
  std::vector<cv::Mat> outputs;
  // Many YOLOv8 ONNX exports have a single output. We'll handle both single and multiple outputs.
  try {
    net_.forward(outputs, net_.getUnconnectedOutLayersNames());
  } catch (const cv::Exception &e) {
    RCLCPP_ERROR(get_logger(), "DNN forward error: %s", e.what());
    return;
  }

  // Combine outputs into NxC matrix if multiple
  cv::Mat pred;
  if (outputs.size() == 1) {
    pred = outputs[0].reshape(1, outputs[0].total() / outputs[0].cols); // try to get rows correct
    // If output shape is 1xNxC, reshape to NxC
    if (pred.rows == 1 && outputs[0].dims >= 2) {
      // handle case where output is 1xNxC flattened
      pred = outputs[0].reshape(1, outputs[0].size[1]);
    }
  } else {
    // concat vertically
    std::vector<cv::Mat> reshaped;
    for (auto &o : outputs) {
      cv::Mat r = o.reshape(1, o.total() / o.cols);
      reshaped.push_back(r);
    }
    cv::vconcat(reshaped, pred);
  }

  // Ensure float type
  if (pred.type() != CV_32F) pred.convertTo(pred, CV_32F);

  // Postprocess
  auto detections = postprocess(frame, pred, conf_thresh_, nms_thresh_);

  // Draw boxes on copy for publishing
  cv::Mat annotated = frame.clone();
  draw_detections(annotated, detections);

  // Publish annotated image
  auto out_msg = cv_bridge::CvImage(msg->header, "bgr8", annotated).toImageMsg();
  out_msg->header.stamp = now();
  out_msg->header.frame_id = frame_id_;
  pub_annotated_->publish(*out_msg);

  // Publish detections as simple JSON string
  std::string json = "[";
  for (size_t i = 0; i < detections.size(); ++i) {
    const auto &d = detections[i];
    std::string cls = (d.class_id >= 0 && d.class_id < (int)class_names_.size())
                      ? class_names_[d.class_id] : std::to_string(d.class_id);
    char buf[256];
    snprintf(buf, sizeof(buf),
             "{\"class\":\"%s\",\"score\":%.3f,\"x\":%d,\"y\":%d,\"w\":%d,\"h\":%d}",
             cls.c_str(), d.score, d.box.x, d.box.y, d.box.width, d.box.height);
    json += buf;
    if (i + 1 < detections.size()) json += ",";
  }
  json += "]";

  std_msgs::msg::String det_msg;
  det_msg.data = json;
  pub_detections_->publish(det_msg);
}

} // namespace vehicle_core

// Register as component so it can be loaded as a component
RCLCPP_COMPONENTS_REGISTER_NODE(vehicle_core::ComputerVisionNode)