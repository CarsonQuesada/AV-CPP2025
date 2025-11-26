#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
import numpy as np
import math

class LidarObjectDetector(Node):
    def __init__(self):
        super().__init__('lidar_object_detector')
        
        # LiDAR subscription
        self.subscription = self.create_subscription(
            LaserScan,
            '/scan',
            self.scan_callback,
            10
        )
        
        # Object markers publisher
        self.marker_pub = self.create_publisher(MarkerArray, '/lidar_objects', 10)
        
        # Parameters
        self.cluster_eps = 0.2  # Clustering distance threshold
        self.cluster_min_points = 3  # Minimum points per cluster
        self.max_detection_range = 8.0  # meters
        
        self.get_logger().info("LiDAR Object Detector Started")
        
    def scan_callback(self, msg):
        # Convert polar to Cartesian coordinates
        points = []
        
        for i, range_val in enumerate(msg.ranges):
            if (not math.isinf(range_val) and 
                range_val >= msg.range_min and 
                range_val <= min(msg.range_max, self.max_detection_range)):
                
                angle = msg.angle_min + i * msg.angle_increment
                x = range_val * math.cos(angle)
                y = range_val * math.sin(angle)
                points.append([x, y])
        
        if len(points) < 3:
            return
            
        points = np.array(points)
        
        # Simple Euclidean clustering (since we might not have sklearn on Orange Pi)
        clusters = self.simple_euclidean_cluster(points)
        
        # Create markers for detected objects
        marker_array = MarkerArray()
        
        # Clear previous markers
        clear_marker = Marker()
        clear_marker.action = Marker.DELETEALL
        marker_array.markers.append(clear_marker)
        
        for cluster_id, cluster_points in enumerate(clusters):
            if len(cluster_points) < self.cluster_min_points:
                continue
                
            # Calculate cluster properties
            cluster_points = np.array(cluster_points)
            centroid = np.mean(cluster_points, axis=0)
            bbox_size = np.max(cluster_points, axis=0) - np.min(cluster_points, axis=0)
            
            # Create marker
            marker = Marker()
            marker.header.frame_id = msg.header.frame_id
            marker.header.stamp = self.get_clock().now().to_msg()
            marker.ns = "lidar_objects"
            marker.id = cluster_id
            marker.type = Marker.CUBE
            marker.action = Marker.ADD
            
            marker.pose.position.x = float(centroid[0])
            marker.pose.position.y = float(centroid[1])
            marker.pose.position.z = 0.0
            marker.pose.orientation.w = 1.0
            
            marker.scale.x = max(float(bbox_size[0]), 0.1)
            marker.scale.y = max(float(bbox_size[1]), 0.1)
            marker.scale.z = 0.5
            
            marker.color.r = 0.0
            marker.color.g = 1.0
            marker.color.b = 0.0
            marker.color.a = 0.7
            
            marker_array.markers.append(marker)
            
            # Add text label
            text_marker = Marker()
            text_marker.header.frame_id = msg.header.frame_id
            text_marker.header.stamp = self.get_clock().now().to_msg()
            text_marker.ns = "object_labels"
            text_marker.id = cluster_id
            text_marker.type = Marker.TEXT_VIEW_FACING
            text_marker.action = Marker.ADD
            
            text_marker.pose.position.x = float(centroid[0])
            text_marker.pose.position.y = float(centroid[1])
            text_marker.pose.position.z = 1.0
            text_marker.pose.orientation.w = 1.0
            
            text_marker.scale.z = 0.2
            text_marker.color.r = 1.0
            text_marker.color.g = 1.0
            text_marker.color.b = 1.0
            text_marker.color.a = 1.0
            
            text_marker.text = f"Obj_{cluster_id}\n{len(cluster_points)}pts"
            
            marker_array.markers.append(text_marker)
        
        self.marker_pub.publish(marker_array)
        
        if len(clusters) > 0:
            self.get_logger().info(f"Detected {len(clusters)} objects with {len(points)} total points")

    def simple_euclidean_cluster(self, points):
        """Simple Euclidean clustering without sklearn dependency"""
        clusters = []
        visited = set()
        
        for i, point in enumerate(points):
            if i in visited:
                continue
                
            cluster = []
            queue = [i]
            visited.add(i)
            
            while queue:
                current_idx = queue.pop(0)
                cluster.append(points[current_idx])
                
                # Check neighbors
                for j, other_point in enumerate(points):
                    if j in visited:
                        continue
                    
                    distance = np.linalg.norm(points[current_idx] - other_point)
                    if distance < self.cluster_eps:
                        queue.append(j)
                        visited.add(j)
            
            clusters.append(cluster)
        
        return clusters

def main():
    rclpy.init()
    node = LidarObjectDetector()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("Shutting down LiDAR Object Detector")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
