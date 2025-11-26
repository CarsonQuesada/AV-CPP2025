#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
import numpy as np

class LidarTest(Node):
    def __init__(self):
        super().__init__('lidar_test')
        self.subscription = self.create_subscription(
            LaserScan,
            '/scan',
            self.scan_callback,
            10
        )
        self.scan_count = 0
        self.get_logger().info("LiDAR Test Node Started - Waiting for data...")
        
    def scan_callback(self, msg):
        self.scan_count += 1
        ranges = np.array(msg.ranges)
        
        # Filter out invalid measurements
        valid_ranges = ranges[(ranges >= msg.range_min) & 
                             (ranges <= msg.range_max) & 
                             (~np.isinf(ranges))]
        
        if len(valid_ranges) > 0:
            min_dist = np.min(valid_ranges)
            max_dist = np.max(valid_ranges)
            avg_dist = np.mean(valid_ranges)
            
            self.get_logger().info(
                f"Scan #{self.scan_count}: {len(valid_ranges)}/{len(ranges)} points | "
                f"Range: {min_dist:.2f}-{max_dist:.2f}m | "
                f"Avg: {avg_dist:.2f}m | "
                f"Angle: {np.rad2deg(msg.angle_min):.1f}° to {np.rad2deg(msg.angle_max):.1f}°"
            )
            
            # Detect close objects (within 1 meter)
            close_objects = valid_ranges[valid_ranges < 1.0]
            if len(close_objects) > 0:
                self.get_logger().warning(f"⚠️  {len(close_objects)} objects within 1m!")
                
        else:
            self.get_logger().warning("No valid LiDAR data in scan!")

def main():
    rclpy.init()
    node = LidarTest()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("LiDAR Test Node Shutting Down")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
