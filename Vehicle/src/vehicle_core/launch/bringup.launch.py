from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer, Node
from launch_ros.descriptions import ComposableNode
from ament_index_python.packages import get_package_share_directory
from os.path import join as path_join
import os

def generate_launch_description():
    pkg_share = get_package_share_directory('vehicle_core')
    cfg_sm   = path_join(pkg_share, 'cfg', 'state_manager.yaml')
    cfg_da   = path_join(pkg_share, 'cfg', 'drive_arbiter.yaml')
    cfg_i2c  = path_join(pkg_share, 'cfg', 'i2c_bridge.yaml')
    cfg_cam  = path_join(pkg_share, 'cfg', 'camera_gscam.yaml')   # <-- NEW

    # If you want to bind web_video_server to Tailscale only, set this env var
    tailscale_ip = os.environ.get("TAILSCALE_IP", "")  # e.g. export TAILSCALE_IP=100.x.x.x

    container = ComposableNodeContainer(
        name='vehicle_core_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container_mt',
        output='screen',
        composable_node_descriptions=[
            ComposableNode(
                package='vehicle_core',
                plugin='vehicle_core::StateManagerNode',
                name='state_manager_node',
                parameters=[cfg_sm],
            ),
            ComposableNode(
                package='vehicle_core',
                plugin='vehicle_core::DriveArbiterNode',
                name='drive_arbiter_node',
                parameters=[cfg_da],
            ),
            ComposableNode(
                package='vehicle_core',
                plugin='vehicle_core::TcpServerNode',
                name='tcp_server_node'
            ),
            ComposableNode(
                package='vehicle_core',
                plugin='vehicle_core::I2cBridgeNode',
                name='i2c_bridge_node',
                parameters=[cfg_i2c],
            ),
            ComposableNode(
                package='vehicle_core',
                plugin='vehicle_core::GstCameraNode',
                name='camera',
                parameters=[{
                    "device": "/dev/video11",
                    "width": 2112,
                    "height": 1568,
                    "fps": 15,
                    "topic": "/camera/image_raw",
                    "frame_id": "camera_link",
                    "queue_depth": 5,
                }],
            ),
        ],
        emulate_tty=True,
    )

    # --- NEW: MJPEG server for remote viewing over Tailscale ---
    wvs_params = {}
    if tailscale_ip:
        wvs_params["address"] = tailscale_ip  # bind only to tailnet interface
    # wvs_params["port"] = 8080               # change if you need a custom port

    web_video = Node(
        package="web_video_server",
        executable="web_video_server",
        name="web_video_server",
        parameters=[wvs_params] if wvs_params else [],
        output="screen"
    )

    return LaunchDescription([
        container,
        web_video
    ])
