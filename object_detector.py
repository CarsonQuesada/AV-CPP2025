#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from std_msgs.msg import Bool
import numpy as np
import math

class LidarObjectDetector(Node):
    def __init__(self):
        super().__init__('lidar_object_detector')
        
        # Subscribe to LiDAR data
        self.subscription = self.create_subscription(
            LaserScan,
            '/scan',
            self.scan_callback,
            10
        )
        
        # Publishers for visualization
        self.marker_pub = self.create_publisher(MarkerArray, '/detected_objects', 10)
        self.bbox_pub = self.create_publisher(MarkerArray, '/object_bboxes', 10)
        
        # Obstacle warning publisher
        self.obstacle_pub = self.create_publisher(Bool, '/sensors/obstacle_detected', 10)
        
        # Parameters
        self.cluster_threshold = 0.3  # meters between points to form clusters
        self.min_cluster_points = 5   # minimum points to be considered an object
        self.max_object_distance = 8.0  # meters
        
        # Emergency braking parameters
        self.emergency_braking_zone = 2.5  # meters - stop if object in this range
        self.warning_zone = 4.0  # meters - warn but don't stop
        
        self.get_logger().info("LiDAR Object Detector Started")
        
    def scan_callback(self, msg):
        # Convert polar to Cartesian coordinates
        points = []
        valid_indices = []
        
        for i, range_val in enumerate(msg.ranges):
            if (not math.isinf(range_val) and 
                range_val >= msg.range_min and 
                range_val <= min(msg.range_max, self.max_object_distance)):
                
                angle = msg.angle_min + i * msg.angle_increment
                x = range_val * math.cos(angle)
                y = range_val * math.sin(angle)
                points.append([x, y])
                valid_indices.append(i)
        
        # Emergency braking check (even without clusters)
        emergency_stop = self.check_emergency_braking(points, msg)
        
        if len(points) < self.min_cluster_points:
            # Still publish obstacle status
            obstacle_msg = Bool()
            obstacle_msg.data = emergency_stop
            self.obstacle_pub.publish(obstacle_msg)
            return
            
        # Cluster points
        clusters = self.euclidean_cluster(points, valid_indices)
        
        # Detect objects from clusters
        objects = self.detect_objects(clusters)
        
        # Update emergency check with object data
        emergency_stop = self.check_emergency_braking_with_objects(objects, points, msg)
        
        # Publish visualization markers
        self.publish_markers(objects, msg.header)
        
        # Publish obstacle status
        obstacle_msg = Bool()
        obstacle_msg.data = emergency_stop
        self.obstacle_pub.publish(obstacle_msg)
        
        # Log detected objects
        if objects or emergency_stop:
            status = "EMERGENCY STOP! " if emergency_stop else ""
            self.get_logger().info(f"{status}Detected {len(objects)} objects")
            for obj in objects:
                dist = math.sqrt(obj['centroid'][0]**2 + obj['centroid'][1]**2)
                self.get_logger().info(f"  - {obj['type']} at {dist:.2f}m ({obj['centroid'][0]:.2f}, {obj['centroid'][1]:.2f})")
    
    def check_emergency_braking(self, points, scan_msg):
        """Check if immediate emergency braking is needed"""
        if not points:
            return False
            
        # Check points in front of vehicle (narrow field of view)
        for i, range_val in enumerate(scan_msg.ranges):
            if (not math.isinf(range_val) and 
                range_val >= scan_msg.range_min and 
                range_val <= self.emergency_braking_zone):
                
                angle = scan_msg.angle_min + i * scan_msg.angle_increment
                # Only consider points directly in front (±30 degrees)
                if abs(angle) < math.radians(30):
                    return True
        return False
    
    def check_emergency_braking_with_objects(self, objects, points, scan_msg):
        """Enhanced emergency check using object detection"""
        # First check raw points for immediate danger
        if self.check_emergency_braking(points, scan_msg):
            return True
            
        # Then check detected objects
        for obj in objects:
            dist = math.sqrt(obj['centroid'][0]**2 + obj['centroid'][1]**2)
            angle = math.atan2(obj['centroid'][1], obj['centroid'][0])
            
            # Stop for any object in front that's too close
            if (abs(angle) < math.radians(45) and 
                dist < self.emergency_braking_zone and
                obj['type'] not in ["wall"]):  # Don't stop for distant walls
                self.get_logger().warning(f"EMERGENCY: {obj['type']} at {dist:.1f}m")
                return True
                
        return False
    
    def euclidean_cluster(self, points, indices):
        """Simple Euclidean clustering algorithm"""
        clusters = []
        visited = set()
        
        for i in range(len(points)):
            if i in visited:
                continue
                
            cluster = []
            queue = [i]
            visited.add(i)
            
            while queue:
                current_idx = queue.pop(0)
                cluster.append({
                    'point': points[current_idx],
                    'original_idx': indices[current_idx]
                })
                
                # Check neighbors
                for j in range(len(points)):
                    if j in visited:
                        continue
                    
                    distance = math.sqrt(
                        (points[current_idx][0] - points[j][0])**2 +
                        (points[current_idx][1] - points[j][1])**2
                    )
                    
                    if distance < self.cluster_threshold:
                        queue.append(j)
                        visited.add(j)
            
            if len(cluster) >= self.min_cluster_points:
                clusters.append(cluster)
        
        return clusters
    
    def detect_objects(self, clusters):
        """Classify clusters as obstacle types (no person classification)"""
        objects = []
        
        for i, cluster in enumerate(clusters):
            # Extract points
            points = [c['point'] for c in cluster]
            points_array = np.array(points)
            
            # Calculate cluster properties
            centroid = np.mean(points_array, axis=0)
            bbox_min = np.min(points_array, axis=0)
            bbox_max = np.max(points_array, axis=0)
            bbox_size = bbox_max - bbox_min
            
            # Calculate approximate area
            area = bbox_size[0] * bbox_size[1]
            
            # Calculate distance to vehicle
            distance = math.sqrt(centroid[0]**2 + centroid[1]**2)
            
            # Classify object based on size - SIMPLIFIED (no person)
            obj_type = self.classify_object(area, bbox_size, len(cluster), distance)
            
            objects.append({
                'id': i,
                'centroid': centroid.tolist(),
                'bbox': {
                    'min': bbox_min.tolist(),
                    'max': bbox_max.tolist(),
                    'size': bbox_size.tolist()
                },
                'point_count': len(cluster),
                'area': area,
                'distance': distance,
                'type': obj_type
            })
        
        return objects
    
    def classify_object(self, area, bbox_size, point_count, distance):
        """Simple obstacle classification - no person category"""
        width, height = bbox_size
        
        # Calculate aspect ratio
        if height > 0:
            aspect_ratio = width / height
        else:
            aspect_ratio = 1.0
        
        # Wall or barrier (long and thin, or very large)
        if (width > 2.0 or height > 2.0) or (width > 1.5 and aspect_ratio > 3.0):
            return "wall"
        
        # Vehicle or large obstacle
        elif (area > 1.0 or width > 1.2 or height > 1.2):
            return "large_obstacle"
        
        # Small obstacle (most things will fall here)
        elif area < 0.5:
            return "small_obstacle"
        
        # Medium obstacle
        elif area < 2.0:
            return "medium_obstacle"
        
        # Everything else is large obstacle
        else:
            return "large_obstacle"
    
    def publish_markers(self, objects, header):
        """Publish visualization markers for detected objects"""
        marker_array = MarkerArray()
        bbox_array = MarkerArray()
        
        # Clear previous markers
        clear_marker = Marker()
        clear_marker.action = Marker.DELETEALL
        marker_array.markers.append(clear_marker)
        bbox_array.markers.append(clear_marker)
        
        for obj in objects:
            # Object centroid marker (sphere)
            centroid_marker = Marker()
            centroid_marker.header = header
            centroid_marker.ns = "object_centroids"
            centroid_marker.id = obj['id']
            centroid_marker.type = Marker.SPHERE
            centroid_marker.action = Marker.ADD
            
            centroid_marker.pose.position.x = obj['centroid'][0]
            centroid_marker.pose.position.y = obj['centroid'][1]
            centroid_marker.pose.position.z = 0.0
            centroid_marker.pose.orientation.w = 1.0
            
            # Color based on object type and emergency status
            emergency = self.is_emergency_object(obj)
            color = self.get_color_for_type(obj['type'], emergency)
            centroid_marker.color.r = color[0]
            centroid_marker.color.g = color[1]
            centroid_marker.color.b = color[2]
            centroid_marker.color.a = 0.8
            
            centroid_marker.scale.x = 0.2
            centroid_marker.scale.y = 0.2
            centroid_marker.scale.z = 0.2
            
            marker_array.markers.append(centroid_marker)
            
            # Bounding box marker
            bbox_marker = Marker()
            bbox_marker.header = header
            bbox_marker.ns = "object_bboxes"
            bbox_marker.id = obj['id']
            bbox_marker.type = Marker.CUBE
            bbox_marker.action = Marker.ADD
            
            bbox_marker.pose.position.x = obj['centroid'][0]
            bbox_marker.pose.position.y = obj['centroid'][1]
            bbox_marker.pose.position.z = 0.0
            bbox_marker.pose.orientation.w = 1.0
            
            bbox_marker.color.r = color[0]
            bbox_marker.color.g = color[1]
            bbox_marker.color.b = color[2]
            bbox_marker.color.a = 0.3  # Transparent
            
            bbox_size = obj['bbox']['size']
            bbox_marker.scale.x = max(bbox_size[0], 0.1)
            bbox_marker.scale.y = max(bbox_size[1], 0.1)
            bbox_marker.scale.z = 0.5
            
            bbox_array.markers.append(bbox_marker)
            
            # Text label
            text_marker = Marker()
            text_marker.header = header
            text_marker.ns = "object_labels"
            text_marker.id = obj['id']
            text_marker.type = Marker.TEXT_VIEW_FACING
            text_marker.action = Marker.ADD
            
            text_marker.pose.position.x = obj['centroid'][0]
            text_marker.pose.position.y = obj['centroid'][1]
            text_marker.pose.position.z = 1.0
            text_marker.pose.orientation.w = 1.0
            
            # Red text for emergency objects
            if emergency:
                text_marker.color.r = 1.0
                text_marker.color.g = 0.0
                text_marker.color.b = 0.0
            else:
                text_marker.color.r = 1.0
                text_marker.color.g = 1.0
                text_marker.color.b = 1.0
            text_marker.color.a = 1.0
            
            text_marker.scale.z = 0.15
            status = "EMERGENCY! " if emergency else ""
            text_marker.text = f"{status}{obj['type']}\n{obj['distance']:.1f}m"
            
            marker_array.markers.append(text_marker)
        
        self.marker_pub.publish(marker_array)
        self.bbox_pub.publish(bbox_array)
    
    def is_emergency_object(self, obj):
        """Check if this object should trigger emergency braking"""
        dist = obj['distance']
        angle = math.atan2(obj['centroid'][1], obj['centroid'][0])
        
        return (abs(angle) < math.radians(45) and 
                dist < self.emergency_braking_zone and
                obj['type'] not in ["wall"])
    
    def get_color_for_type(self, obj_type, emergency=False):
        """Get RGB color for object type"""
        if emergency:
            return (1.0, 0.0, 0.0)  # Bright red for emergency
            
        colors = {
            "small_obstacle": (1.0, 0.5, 0.0),  # Orange
            "medium_obstacle": (1.0, 1.0, 0.0), # Yellow
            "large_obstacle": (0.5, 0.0, 0.5),  # Purple
            "wall": (0.0, 0.0, 1.0),          # Blue
        }
        return colors.get(obj_type, (0.5, 0.5, 0.5))  # Gray for unknown

def main():
    rclpy.init()
    node = LidarObjectDetector()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("Shutting down object detector")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()