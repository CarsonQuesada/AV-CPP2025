from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'port',
            default_value='/dev/ttyUSB0',
            description='LiDAR serial port'
        ),
        DeclareLaunchArgument(
            'baudrate', 
            default_value='1000000',
            description='LiDAR baud rate (confirmed: 1Mbps)'
        ),
        DeclareLaunchArgument(
            'frame_id',
            default_value='laser_frame',
            description='LiDAR frame ID'
        ),
        
        Node(
            package='av_cpp2025',
            executable='d300_custom_driver.py',
            name='d300_custom_driver',
            parameters=[{
                'port': LaunchConfiguration('port'),
                'baudrate': LaunchConfiguration('baudrate'),
                'frame_id': LaunchConfiguration('frame_id'),
                'range_min': 0.1,
                'range_max': 16.0,
            }],
            output='screen'
        ),
    ])
