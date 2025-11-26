#!/bin/bash
echo "Starting D300 LiDAR Web Visualization System..."
echo "=============================================="

# Check if ROS 2 is sourced
if [ -z "$ROS_DISTRO" ]; then
    echo "Sourcing ROS 2..."
    source /opt/ros/humble/setup.bash
fi

# Start the LiDAR driver (standalone version)
echo "1. Starting LiDAR driver..."
python3 ~/AV-CPP2025/run_standalone_driver.py &

# Wait a moment for the driver to start
sleep 2

# Start ROS web services
echo "2. Starting ROS web services..."

# Start web video server
ros2 run web_video_server web_video_server --ros-args -p port:=8080 -p address:="0.0.0.0" &

# Start ROS bridge
ros2 run rosbridge_server rosbridge_websocket --ros-args -p port:=9090 -p address:="0.0.0.0" &

# Start TF2 web republisher
ros2 run tf2_web_republisher tf2_web_republisher &

# Start ROS API
ros2 run rosapi rosapi_node &

# Wait for services to start
sleep 3

# Start the web server
echo "3. Starting web visualizer server..."
cd ~/AV-CPP2025/web_visualizer
python3 start_web_server.py &

echo ""
echo "=============================================="
echo "Web Visualization System Started!"
echo ""
echo "Access your LiDAR data at:"
echo "  http://$(hostname -I | awk '{print $1}'):8000/lidar_viewer.html"
echo "  or"
echo "  http://localhost:8000/lidar_viewer.html"
echo ""
echo "To check if LiDAR data is publishing:"
echo "  ros2 topic echo /scan --once"
echo ""
echo "Press Ctrl+C to stop all services"
echo "=============================================="

# Wait for user to press Ctrl+C
wait
