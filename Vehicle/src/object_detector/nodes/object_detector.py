#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point
from std_msgs.msg import Bool, Float32, String  # ADDED String here
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
        
        # Obstacle detection publishers
        self.obstacle_pub = self.create_publisher(Bool, '/sensors/obstacle_detected', 10)
        self.closest_object_pub = self.create_publisher(Float32, '/sensors/closest_object_distance', 10)
        self.emergency_zone_pub = self.create_publisher(Float32, '/sensors/emergency_zone_distance', 10)
        self.angle_zone_pub = self.create_publisher(String, '/sensors/closest_object_angle_zone', 10)

        # Parameters
        self.cluster_threshold = 0.3  # meters between points to form clusters
        self.min_cluster_points = 5   # minimum points to be considered an object
        self.max_object_distance = 8.0  # meters
        
        # Zones for graduated response - NOW CONFIGURABLE
        self.emergency_braking_zone = self.declare_parameter('emergency_braking_zone', 2.0).value  # meters - full stop
        self.slow_down_zone = self.declare_parameter('slow_down_zone', 2.5).value  # meters - reduce speed
        self.warning_zone = self.declare_parameter('warning_zone', 6.0).value  # meters - warn but maintain speed
        
        # Field of view with priority zones - ALSO CONFIGURABLE
        self.fov_degrees = self.declare_parameter('fov_degrees', 80.0).value  # Total FOV: ±40 degrees
        self.emergency_fov_degrees = self.declare_parameter('emergency_fov_degrees', 40.0).value  # Emergency zone: ±20 degrees (center)
        self.caution_fov_degrees = self.declare_parameter('caution_fov_degrees', 80.0).value  # Caution zone: ±40 degrees (edges)
        
        # Convert to radians
        self.fov_radians = math.radians(self.fov_degrees / 2)
        self.emergency_fov_radians = math.radians(self.emergency_fov_degrees / 2)
        self.caution_fov_radians = math.radians(self.caution_fov_degrees / 2)
        
        # Dynamic emergency zone adjustment
        self.dynamic_emergency_zone = self.emergency_braking_zone
        self.min_emergency_zone = 0.5  # Minimum emergency distance
        self.max_emergency_zone = 3.0  # Maximum emergency distance
        
        # Publish initial emergency zone
        self.publish_emergency_zone()
        
        self.get_logger().info(f"LiDAR Object Detector Started")
        self.get_logger().info(f"FOV: {self.fov_degrees}° total, Emergency: {self.emergency_fov_degrees}°, Caution: {self.caution_fov_degrees}°")
        self.get_logger().info(f"Distance Zones: Emergency={self.emergency_braking_zone}m, Slow={self.slow_down_zone}m, Warning={self.warning_zone}m")
        self.get_logger().info(f"Dynamic emergency zone: {self.dynamic_emergency_zone}m (adjustable)")
        
    def publish_emergency_zone(self):
        """Publish the current emergency zone distance"""
        zone_msg = Float32()
        zone_msg.data = self.dynamic_emergency_zone
        self.emergency_zone_pub.publish(zone_msg)
    
    def adjust_emergency_zone(self, adjustment):
        """Adjust emergency zone distance dynamically"""
        self.dynamic_emergency_zone += adjustment
        self.dynamic_emergency_zone = max(self.min_emergency_zone, 
                                         min(self.max_emergency_zone, self.dynamic_emergency_zone))
        self.get_logger().info(f"Emergency zone adjusted to: {self.dynamic_emergency_zone:.2f}m")
        self.publish_emergency_zone()
    
    def get_angle_zone(self, angle_normalized):
        """Determine which angle zone the object is in"""
        # Normalize to 0-360 degrees for easier understanding
        angle_deg = math.degrees(angle_normalized)
        
        # Center is at 0°, so we need to handle wrap-around
        if angle_deg > 180:
            angle_deg = angle_deg - 360  # Convert to -180 to 180 range
        
        abs_angle = abs(angle_deg)
        
        # Determine zone based on absolute angle from center
        if abs_angle <= self.emergency_fov_degrees / 2:
            return "emergency_angle"  # Directly in front (±20°)
        elif abs_angle <= self.caution_fov_degrees / 2:
            return "caution_angle"    # Sides (±20-40°)
        else:
            return "ignore_angle"     # Outside our concern (> ±40°)
    
    def scan_callback(self, msg):
        # Convert polar to Cartesian coordinates
        points = []
        valid_indices = []
        closest_distance = float('inf')
        closest_angle_zone = ""
        
        for i, range_val in enumerate(msg.ranges):
            if (not math.isinf(range_val) and 
                range_val >= msg.range_min and 
                range_val <= min(msg.range_max, self.max_object_distance)):
                
                angle = msg.angle_min + i * msg.angle_increment
                
                # Normalize angle to 0-2π range
                angle_normalized = angle % (2 * math.pi)
                
                # Check if angle is within TOTAL FOV
                angle_zone = self.get_angle_zone(angle_normalized)
                
                if angle_zone != "ignore_angle":  # Only track if in emergency or caution zones
                    x = range_val * math.cos(angle)
                    y = range_val * math.sin(angle)
                    points.append([x, y])
                    valid_indices.append(i)
                    
                    # Track closest distance and its zone
                    if range_val < closest_distance:
                        closest_distance = range_val
                        closest_angle_zone = angle_zone
        
        # Emergency braking check (even without clusters)
        emergency_stop = self.check_emergency_braking(points, msg)
        
        # Publish closest distance
        distance_msg = Float32()
        if closest_distance != float('inf'):
            distance_msg.data = closest_distance
        else:
            distance_msg.data = self.max_object_distance  # No obstacles detected
        self.closest_object_pub.publish(distance_msg)
        
        # ADDED: Publish angle zone
        zone_msg = String()
        if closest_angle_zone:
            zone_msg.data = closest_angle_zone
            self.get_logger().debug(f"Closest object: {closest_distance:.2f}m in {closest_angle_zone}")
        else:
            zone_msg.data = "ignore_angle"
        self.angle_zone_pub.publish(zone_msg)
        
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
        self.publish_markers(objects, msg.header, closest_distance)
        
        # Publish obstacle status (only stop for emergency angle zone objects)
        obstacle_msg = Bool()
        # Only trigger emergency stop if object is in emergency angle zone AND emergency distance zone
        obstacle_msg.data = emergency_stop
        self.obstacle_pub.publish(obstacle_msg)
        
        # Log detected objects
        if objects or emergency_stop:
            status = "EMERGENCY STOP! " if emergency_stop else ""
            zone_status = self.get_zone_status(closest_distance)
            self.get_logger().info(f"{status}{zone_status}Detected {len(objects)} objects, closest: {closest_distance:.2f}m")
            for obj in objects:
                dist = math.sqrt(obj['centroid'][0]**2 + obj['centroid'][1]**2)
                angle = math.atan2(obj['centroid'][1], obj['centroid'][0])
                angle_normalized = angle % (2 * math.pi)
                angle_zone = self.get_angle_zone(angle_normalized)
                self.get_logger().info(f"  - {obj['type']} at {dist:.2f}m ({obj['centroid'][0]:.2f}, {obj['centroid'][1]:.2f}) in {angle_zone}")
    
    def get_zone_status(self, distance):
        """Return which distance zone the closest object is in"""
        if distance <= self.dynamic_emergency_zone:
            return "EMERGENCY DISTANCE ZONE! "
        elif distance <= self.slow_down_zone:
            return "SLOW DOWN DISTANCE ZONE "
        elif distance <= self.warning_zone:
            return "WARNING DISTANCE ZONE "
        else:
            return ""
    
    def check_emergency_braking(self, points, scan_msg):
        """Check if immediate emergency braking is needed"""
        if not points:
            return False
            
        # Check points in front of vehicle
        for i, range_val in enumerate(scan_msg.ranges):
            if (not math.isinf(range_val) and 
                range_val >= scan_msg.range_min and 
                range_val <= self.dynamic_emergency_zone):
                
                angle = scan_msg.angle_min + i * scan_msg.angle_increment
                angle_normalized = angle % (2 * math.pi)
                
                # Only emergency stop if object is in EMERGENCY ANGLE zone
                angle_zone = self.get_angle_zone(angle_normalized)
                if angle_zone == "emergency_angle":
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
            angle_normalized = angle % (2 * math.pi)
            
            # Determine angle zone
            angle_zone = self.get_angle_zone(angle_normalized)
            
            # Only emergency stop if:
            # 1. Object is in emergency angle zone (±20°)
            # 2. Object is within emergency distance zone
            # 3. Not a wall
            if (angle_zone == "emergency_angle" and 
                dist < self.dynamic_emergency_zone and
                obj['type'] not in ["wall"]):
                
                self.get_logger().warning(f"EMERGENCY: {obj['type']} at {dist:.1f}m in emergency angle zone")
                return True
                
            # Objects in caution angle zone (20-40°) don't trigger emergency stop
            # They only trigger speed reduction (handled by drive arbiter)
                
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
            
            # Calculate angle to object
            angle = math.atan2(centroid[1], centroid[0])
            angle_normalized = angle % (2 * math.pi)
            angle_zone = self.get_angle_zone(angle_normalized)
            
            # Classify object based on size
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
                'angle': angle,
                'angle_zone': angle_zone,
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
    
    def publish_markers(self, objects, header, closest_distance):
        """Publish visualization markers for detected objects"""
        marker_array = MarkerArray()
        bbox_array = MarkerArray()
        
        # Clear previous markers
        clear_marker = Marker()
        clear_marker.action = Marker.DELETEALL
        marker_array.markers.append(clear_marker)
        bbox_array.markers.append(clear_marker)
        
        # Add zone visualization markers (semi-transparent rings)
        self.add_zone_markers(marker_array, header)
        
        for obj in objects:
            # Determine color based on BOTH distance AND angle zone
            dist = obj['distance']
            angle_zone = obj['angle_zone']
            
            if angle_zone == "emergency_angle":
                if dist <= self.dynamic_emergency_zone:
                    color = (1.0, 0.0, 0.0)  # Red for emergency angle + emergency distance
                    emergency = True
                elif dist <= self.slow_down_zone:
                    color = (1.0, 0.5, 0.0)  # Orange for emergency angle + slow distance
                    emergency = False
                elif dist <= self.warning_zone:
                    color = (1.0, 1.0, 0.0)  # Yellow for emergency angle + warning distance
                    emergency = False
                else:
                    color = (0.5, 0.0, 0.0)  # Dark red for emergency angle but far
                    emergency = False
            elif angle_zone == "caution_angle":
                if dist <= self.dynamic_emergency_zone:
                    color = (1.0, 0.5, 0.5)  # Pink for caution angle + emergency distance
                    emergency = False
                elif dist <= self.slow_down_zone:
                    color = (1.0, 0.8, 0.5)  # Light orange for caution angle + slow distance
                    emergency = False
                elif dist <= self.warning_zone:
                    color = (1.0, 1.0, 0.5)  # Light yellow for caution angle + warning distance
                    emergency = False
                else:
                    color = (0.8, 0.8, 0.8)  # Light gray for caution angle but far
                    emergency = False
            else:
                color = self.get_color_for_type(obj['type'], False)
                emergency = False
            
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
            bbox_marker.scale.x = max(float(bbox_size[0]), 0.1)
            bbox_marker.scale.y = max(float(bbox_size[1]), 0.1)
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
            
            # Color text based on zone
            if emergency:
                text_marker.color.r = 1.0
                text_marker.color.g = 0.0
                text_marker.color.b = 0.0
            elif angle_zone == "emergency_angle":
                if dist <= self.dynamic_emergency_zone:
                    text_marker.color.r = 1.0
                    text_marker.color.g = 0.5
                    text_marker.color.b = 0.5
                else:
                    text_marker.color.r = 1.0
                    text_marker.color.g = 1.0
                    text_marker.color.b = 1.0
            else:
                text_marker.color.r = 1.0
                text_marker.color.g = 1.0
                text_marker.color.b = 1.0
                
            text_marker.color.a = 1.0
            
            text_marker.scale.z = 0.15
            zone_text = ""
            if emergency:
                zone_text = "EMERGENCY! "
            elif dist <= self.dynamic_emergency_zone:
                zone_text = "CLOSE! "
            elif dist <= self.slow_down_zone:
                zone_text = "SLOW! "
            elif dist <= self.warning_zone:
                zone_text = "WARN! "
                
            text_marker.text = f"{zone_text}{obj['type']}\n{dist:.1f}m ({angle_zone})"
            
            marker_array.markers.append(text_marker)
        
        self.marker_pub.publish(marker_array)
        self.bbox_pub.publish(bbox_array)
    
    def add_zone_markers(self, marker_array, header):
        """Add visualization rings for each zone"""
        # Warning zone (yellow)
        warning_marker = Marker()
        warning_marker.header = header
        warning_marker.ns = "zones"
        warning_marker.id = 1000
        warning_marker.type = Marker.CYLINDER
        warning_marker.action = Marker.ADD
        warning_marker.pose.position.x = 0.0
        warning_marker.pose.position.y = 0.0
        warning_marker.pose.position.z = -0.5  # Below ground slightly
        warning_marker.pose.orientation.w = 1.0
        warning_marker.color.r = 1.0
        warning_marker.color.g = 1.0
        warning_marker.color.b = 0.0
        warning_marker.color.a = 0.1  # Very transparent
        warning_marker.scale.x = float(self.warning_zone * 2)  # Diameter
        warning_marker.scale.y = float(self.warning_zone * 2)
        warning_marker.scale.z = 0.01  # Very thin
        marker_array.markers.append(warning_marker)
        
        # Slow down zone (orange)
        slow_marker = Marker()
        slow_marker.header = header
        slow_marker.ns = "zones"
        slow_marker.id = 1001
        slow_marker.type = Marker.CYLINDER
        slow_marker.action = Marker.ADD
        slow_marker.pose.position.x = 0.0
        slow_marker.pose.position.y = 0.0
        slow_marker.pose.position.z = -0.49  # Slightly above warning zone
        slow_marker.pose.orientation.w = 1.0
        slow_marker.color.r = 1.0
        slow_marker.color.g = 0.5
        slow_marker.color.b = 0.0
        slow_marker.color.a = 0.15
        slow_marker.scale.x = float(self.slow_down_zone * 2)
        slow_marker.scale.y = float(self.slow_down_zone * 2)
        slow_marker.scale.z = 0.01
        marker_array.markers.append(slow_marker)
        
        # Emergency zone (red) - DYNAMIC
        emergency_marker = Marker()
        emergency_marker.header = header
        emergency_marker.ns = "zones"
        emergency_marker.id = 1002
        emergency_marker.type = Marker.CYLINDER
        emergency_marker.action = Marker.ADD
        emergency_marker.pose.position.x = 0.0
        emergency_marker.pose.position.y = 0.0
        emergency_marker.pose.position.z = -0.48  # Slightly above slow zone
        emergency_marker.pose.orientation.w = 1.0
        emergency_marker.color.r = 1.0
        emergency_marker.color.g = 0.0
        emergency_marker.color.b = 0.0
        emergency_marker.color.a = 0.2
        emergency_marker.scale.x = float(self.dynamic_emergency_zone * 2)
        emergency_marker.scale.y = float(self.dynamic_emergency_zone * 2)
        emergency_marker.scale.z = 0.01
        marker_array.markers.append(emergency_marker)
        
        # FOV visualization (green wedges for different zones)
        # Emergency angle zone wedge (bright green)
        emergency_fov_marker = Marker()
        emergency_fov_marker.header = header
        emergency_fov_marker.ns = "zones"
        emergency_fov_marker.id = 1003
        emergency_fov_marker.type = Marker.TRIANGLE_LIST
        emergency_fov_marker.action = Marker.ADD
        emergency_fov_marker.pose.position.x = 0.0
        emergency_fov_marker.pose.position.y = 0.0
        emergency_fov_marker.pose.position.z = -0.47  # Above other zones
        emergency_fov_marker.pose.orientation.w = 1.0
        emergency_fov_marker.color.r = 0.0
        emergency_fov_marker.color.g = 1.0
        emergency_fov_marker.color.b = 0.0
        emergency_fov_marker.color.a = 0.3
        
        # Create triangles for emergency FOV wedge
        num_triangles = 10
        max_range = self.warning_zone
        fov_half_rad = self.emergency_fov_radians
        
        for i in range(num_triangles):
            angle1 = -fov_half_rad + (2 * fov_half_rad / num_triangles) * i
            angle2 = -fov_half_rad + (2 * fov_half_rad / num_triangles) * (i + 1)
            
            p0 = Point(x=0.0, y=0.0, z=0.0)
            p1 = Point(x=max_range * math.cos(angle1), y=max_range * math.sin(angle1), z=0.0)
            p2 = Point(x=max_range * math.cos(angle2), y=max_range * math.sin(angle2), z=0.0)
            
            emergency_fov_marker.points.append(p0)
            emergency_fov_marker.points.append(p1)
            emergency_fov_marker.points.append(p2)
        
        emergency_fov_marker.scale.x = 1.0
        emergency_fov_marker.scale.y = 1.0
        emergency_fov_marker.scale.z = 1.0
        marker_array.markers.append(emergency_fov_marker)
        
        # Caution angle zone wedge (yellow-green)
        caution_fov_marker = Marker()
        caution_fov_marker.header = header
        caution_fov_marker.ns = "zones"
        caution_fov_marker.id = 1004
        caution_fov_marker.type = Marker.TRIANGLE_LIST
        caution_fov_marker.action = Marker.ADD
        caution_fov_marker.pose.position.x = 0.0
        caution_fov_marker.pose.position.y = 0.0
        caution_fov_marker.pose.position.z = -0.46  # Above emergency zone
        caution_fov_marker.pose.orientation.w = 1.0
        caution_fov_marker.color.r = 0.5
        caution_fov_marker.color.g = 1.0
        caution_fov_marker.color.b = 0.0
        caution_fov_marker.color.a = 0.2
        
        # Create triangles for caution FOV wedge (the outer ring)
        for i in range(num_triangles):
            # Outer wedge from emergency_fov_radians to caution_fov_radians
            angle1_outer = -self.caution_fov_radians + (2 * self.caution_fov_radians / num_triangles) * i
            angle2_outer = -self.caution_fov_radians + (2 * self.caution_fov_radians / num_triangles) * (i + 1)
            
            # Only draw the part outside emergency zone
            angle1 = max(abs(angle1_outer), self.emergency_fov_radians) * (1 if angle1_outer >= 0 else -1)
            angle2 = max(abs(angle2_outer), self.emergency_fov_radians) * (1 if angle2_outer >= 0 else -1)
            
            if abs(angle1) > self.emergency_fov_radians or abs(angle2) > self.emergency_fov_radians:
                p0 = Point(x=0.0, y=0.0, z=0.0)
                p1 = Point(x=max_range * math.cos(angle1), y=max_range * math.sin(angle1), z=0.0)
                p2 = Point(x=max_range * math.cos(angle2), y=max_range * math.sin(angle2), z=0.0)
                
                caution_fov_marker.points.append(p0)
                caution_fov_marker.points.append(p1)
                caution_fov_marker.points.append(p2)
        
        caution_fov_marker.scale.x = 1.0
        caution_fov_marker.scale.y = 1.0
        caution_fov_marker.scale.z = 1.0
        marker_array.markers.append(caution_fov_marker)
    
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
    
    # Example: You could add a service or topic to adjust emergency zone dynamically
    # For now, you can adjust it via ROS parameters when launching:
    # ros2 run object_detector object_detector.py --ros-args -p emergency_braking_zone:=1.5
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("Shutting down object detector")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()