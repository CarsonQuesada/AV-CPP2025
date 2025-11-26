#!/bin/bash
echo "Starting Clean D300 LiDAR Web Visualization System..."
echo "===================================================="

# Kill any existing processes
echo "1. Cleaning up existing processes..."
sudo pkill -f web_video_server 2>/dev/null || true
sudo pkill -f rosbridge_websocket 2>/dev/null || true
sudo pkill -f tf2_web_republisher 2>/dev/null || true
sudo pkill -f rosapi_node 2>/dev/null || true
sudo pkill -f standalone_d300_driver 2>/dev/null || true

# Wait for ports to be freed
sleep 2

# Check if ROS 2 is sourced
if [ -z "$ROS_DISTRO" ]; then
    echo "Sourcing ROS 2..."
    source /opt/ros/humble/setup.bash
fi

# Start the LiDAR driver (standalone version)
echo "2. Starting LiDAR driver..."
python3 ~/AV-CPP2025/run_standalone_driver.py &
LIDAR_PID=$!
echo "LiDAR driver PID: $LIDAR_PID"

# Wait a moment for the driver to start
sleep 3

# Start ROS web services with error handling
echo "3. Starting ROS web services..."

# Start web video server on different port if 8080 is busy
if ! lsof -i :8080 > /dev/null; then
    ros2 run web_video_server web_video_server --ros-args -p port:=8080 -p address:="0.0.0.0" &
    WEB_VIDEO_PID=$!
    echo "Web video server PID: $WEB_VIDEO_PID"
else
    echo "Port 8080 busy, using 8081 for web video server"
    ros2 run web_video_server web_video_server --ros-args -p port:=8081 -p address:="0.0.0.0" &
    WEB_VIDEO_PID=$!
fi

# Start ROS bridge on different port if 9090 is busy
if ! lsof -i :9090 > /dev/null; then
    ros2 run rosbridge_server rosbridge_websocket --ros-args -p port:=9090 -p address:="0.0.0.0" &
    ROSBRIDGE_PID=$!
    echo "ROS Bridge PID: $ROSBRIDGE_PID"
else
    echo "Port 9090 busy, using 9091 for ROS bridge"
    ros2 run rosbridge_server rosbridge_websocket --ros-args -p port:=9091 -p address:="0.0.0.0" &
    ROSBRIDGE_PID=$!
fi

# Start other services
ros2 run tf2_web_republisher tf2_web_republisher &
TF2_PID=$!

ros2 run rosapi rosapi_node &
ROSAPI_PID=$!

# Wait for services to start
sleep 5

# Verify services are running
echo "4. Verifying services..."
ros2 topic list | grep scan && echo "✓ LiDAR topic found" || echo "✗ LiDAR topic missing"

# Start the web server
echo "5. Starting web visualizer server..."
cd ~/AV-CPP2025/web_visualizer

# Update the HTML file to use correct ports if needed
if [ -n "$ROSBRIDGE_PID" ]; then
    sed -i 's/9090/9091/g' lidar_viewer.html 2>/dev/null || echo "Using default port 9090"
fi

python3 start_web_server.py &
WEB_SERVER_PID=$!

echo ""
echo "=============================================="
echo "Web Visualization System Started!"
echo ""
echo "PIDs:"
echo "  LiDAR Driver: $LIDAR_PID"
echo "  Web Video: $WEB_VIDEO_PID" 
echo "  ROS Bridge: $ROSBRIDGE_PID"
echo "  TF2 Repub: $TF2_PID"
echo "  ROS API: $ROSAPI_PID"
echo "  Web Server: $WEB_SERVER_PID"
echo ""
echo "Access your LiDAR data at:"
echo "  http://$(hostname -I | awk '{print $1}'):8000/lidar_viewer.html"
echo ""
echo "To check LiDAR data:"
echo "  ros2 topic echo /scan --once"
echo ""
echo "To stop: ./stop_web_services.sh or Ctrl+C"
echo "=============================================="

# Create a stop script
cat > ~/AV-CPP2025/stop_web_services.sh << STOPEOF
#!/bin/bash
echo "Stopping all web visualization services..."
sudo pkill -f web_video_server 2>/dev/null || true
sudo pkill -f rosbridge_websocket 2>/dev/null || true
sudo pkill -f tf2_web_republisher 2>/dev/null || true
sudo pkill -f rosapi_node 2>/dev/null || true
sudo pkill -f standalone_d300_driver 2>/dev/null || true
sudo pkill -f start_web_server 2>/dev/null || true
echo "All services stopped."
STOPEOF

chmod +x ~/AV-CPP2025/stop_web_services.sh

# Wait for user to press Ctrl+C
echo "Press Ctrl+C to stop all services"
wait
