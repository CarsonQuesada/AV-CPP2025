#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
import time
import numpy as np

class StandaloneD300Driver(Node):
    def __init__(self):
        super().__init__('standalone_d300_driver')
        
        # Publisher
        self.scan_pub = self.create_publisher(LaserScan, '/scan', 10)
        
        # Create timer to publish scans
        self.timer = self.create_timer(0.1, self.publish_scan)  # 10Hz
        
        self.get_logger().info("Standalone D300 Driver Started - Publishing to /scan")
    
    def publish_scan(self):
        scan_msg = LaserScan()
        scan_msg.header.stamp = self.get_clock().now().to_msg()
        scan_msg.header.frame_id = 'laser_frame'
        
        # D300 specifications
        scan_msg.angle_min = -3.14159
        scan_msg.angle_max = 3.14159
        scan_msg.angle_increment = 0.0174533
        scan_msg.time_increment = 0.0001
        scan_msg.scan_time = 0.1
        scan_msg.range_min = 0.1
        scan_msg.range_max = 16.0
        
        # Generate realistic scan data (360 points)
        num_points = 360
        ranges = []
        intensities = []
        
        time_factor = time.time()
        
        for i in range(num_points):
            # Create walls and open space
            if 170 <= i <= 190:  # Front
                dist = 2.0 + 0.1 * np.sin(time_factor)
            elif 80 <= i <= 100:  # Right
                dist = 1.5 + 0.1 * np.sin(time_factor + 1)
            elif 260 <= i <= 280:  # Left
                dist = 1.8 + 0.1 * np.sin(time_factor + 2)
            else:  # Open space
                dist = 4.0 + 0.3 * np.sin(time_factor + i * 0.05)
            
            # Add noise
            dist += np.random.normal(0, 0.02)
            dist = max(0.1, min(16.0, dist))
            
            # Intensity based on distance
            intensity = 100 + (100 * (1.0 - dist/16.0)) + np.random.randint(0, 30)
            
            ranges.append(float(dist))
            intensities.append(float(intensity))
        
        scan_msg.ranges = ranges
        scan_msg.intensities = intensities
        
        self.scan_pub.publish(scan_msg)
        
        # Log occasionally
        if int(time.time()) % 5 == 0:
            valid_ranges = [r for r in ranges if 0.1 <= r <= 16.0]
            if valid_ranges:
                self.get_logger().info(f"Published scan: {len(valid_ranges)} points")

def main():
    rclpy.init()
    node = StandaloneD300Driver()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        print("\nShutting down...")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
