from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'serial_port',
            default_value='/dev/ttyUSB0',
            description='LiDAR serial port'
        ),
        DeclareLaunchArgument(
            'serial_baudrate',
            default_value='256000',
            description='LiDAR baud rate (D300 uses 256000)'
        ),
        DeclareLaunchArgument(
            'frame_id',
            default_value='laser_frame',
            description='LiDAR frame ID'
        ),
        DeclareLaunchArgument(
            'angle_compensate',
            default_value='true',
            description='Enable angle compensation'
        ),
        DeclareLaunchArgument(
            'scan_mode',
            default_value='Standard',
            description='Scan mode: Standard, Express, Boost'
        ),
        
        Node(
            package='rplidar_ros',
            executable='rplidar_node',
            name='rplidar_node',
            parameters=[{
                'serial_port': LaunchConfiguration('serial_port'),
                'serial_baudrate': LaunchConfiguration('serial_baudrate'),
                'frame_id': LaunchConfiguration('frame_id'),
                'angle_compensate': LaunchConfiguration('angle_compensate'),
                'scan_mode': LaunchConfiguration('scan_mode'),
                'inverted': False,
                'auto_standby': True,
            }],
            output='screen',
            respawn=True,
            respawn_delay=3
        ),
    ])
