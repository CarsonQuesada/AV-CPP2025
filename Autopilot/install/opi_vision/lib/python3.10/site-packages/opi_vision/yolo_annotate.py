#!/usr/bin/env python3
import rclpy, cv2
from rclpy.node import Node
from sensor_msgs.msg import Image, CompressedImage
from cv_bridge import CvBridge
from ultralytics import YOLO

class YoloAnnotate(Node):
    def __init__(self):
        super().__init__('yolo_annotate')
        self.declare_parameter('image_topic', '/camera/image_raw')
        self.declare_parameter('model_path', 'yolov8n.pt')
        self.declare_parameter('imgsz', 640)
        self.declare_parameter('conf', 0.25)

        self.bridge = CvBridge()
        self.model = YOLO(self.get_parameter('model_path').get_parameter_value().string_value)
        self.imgsz = int(self.get_parameter('imgsz').value)
        self.conf = float(self.get_parameter('conf').value)

        topic = self.get_parameter('image_topic').get_parameter_value().string_value
        self.sub = self.create_subscription(Image, topic, self.cb, 10)
        self.pub_raw = self.create_publisher(Image, '/camera/image_annotated', 10)
        self.pub_jpg = self.create_publisher(CompressedImage, '/camera/image_annotated/compressed', 10)
        self.get_logger().info(f'YOLO ready on {topic}')

    def cb(self, msg: Image):
        # gscam publishes rgb8; cv2 prefers BGR
        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        results = self.model.predict(frame, imgsz=self.imgsz, conf=self.conf, verbose=False)
        annotated = results[0].plot()

        # raw
        self.pub_raw.publish(self.bridge.cv2_to_imgmsg(annotated, encoding='bgr8'))
        # compressed (lighter for network)
        ok, enc = cv2.imencode('.jpg', annotated, [int(cv2.IMWRITE_JPEG_QUALITY), 80])
        if ok:
            out = CompressedImage()
            out.format = 'jpeg'
            out.data = enc.tobytes()
            self.pub_jpg.publish(out)

def main():
    rclpy.init(); rclpy.spin(YoloAnnotate()); rclpy.shutdown()

if __name__ == "__main__":
    main()
