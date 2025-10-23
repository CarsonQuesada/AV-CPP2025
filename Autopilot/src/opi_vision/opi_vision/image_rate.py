#!/usr/bin/env python3
import rclpy, time
from rclpy.node import Node
from sensor_msgs.msg import Image

class ImageRate(Node):
    def __init__(self):
        super().__init__('image_rate')
        self.sub = self.create_subscription(Image, '/camera/image_raw', self.cb, 10)
        self.t0 = time.time(); self.n = 0

    def cb(self, _):
        self.n += 1
        now = time.time()
        if now - self.t0 >= 2:
            fps = self.n / (now - self.t0)
            self.get_logger().info(f'~{fps:.1f} fps')
            self.t0, self.n = now, 0

def main():
    rclpy.init()
    rclpy.spin(ImageRate())
    rclpy.shutdown()

if __name__ == "__main__":
    main()
