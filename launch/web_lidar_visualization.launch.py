from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        # LiDAR Driver
        Node(
            package='av_cpp2025',
            executable='d300_custom_driver.py',
            name='d300_driver',
            output='screen'
        ),
        
        # Web Video Server (for future camera topics)
        Node(
            package='web_video_server',
            executable='web_video_server',
            name='web_video_server',
            output='screen',
            parameters=[{
                'port': 8080,
                'address': '0.0.0.0'
            }]
        ),
        
        # ROS Bridge for web communication
        Node(
            package='rosbridge_server',
            executable='rosbridge_websocket',
            name='rosbridge_websocket',
            output='screen',
            parameters=[{
                'port': 9090,
                'address': '0.0.0.0'
            }]
        ),
        
        # TF2 Web Republisher (for coordinate frames)
        Node(
            package='tf2_web_republisher',
            executable='tf2_web_republisher',
            name='tf2_web_republisher',
            output='screen'
        ),
        
        # ROS API (additional web services)
        Node(
            package='rosapi',
            executable='rosapi_node',
            name='rosapi',
            output='screen'
        ),
    ])
