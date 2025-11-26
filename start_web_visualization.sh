#!/bin/bash
echo "Starting D300 LiDAR Web Visualization System..."
echo "=============================================="

# Check if ROS 2 is sourced
if [ -z "$ROS_DISTRO" ]; then
    echo "Sourcing ROS 2..."
    source /opt/ros/humble/setup.bash
fi

# Start the web services
echo "1. Starting ROS 2 web services..."
ros2 launch av_cpp2025 web_lidar_visualization.launch.py &

# Wait for services to start
sleep 3

# Start the web server
echo "2. Starting web visualizer server..."
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
echo "Press Ctrl+C to stop all services"
echo "=============================================="

# Wait for user to press Ctrl+C
wait
