from launch import LaunchDescription
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node

def generate_launch_description():
    gscam_config = (
        'v4l2src device=/dev/video11 io-mode=dmabuf ! \
        video/x-raw,format=NV12,width=1280,height=720,framerate=15/1 ! \
        queue ! videoconvert n-threads=2 ! video/x-raw,format=BGR'
    )
    return LaunchDescription([
        SetEnvironmentVariable('GST_V4L2_USE_LIBV4L2', '0'),
        SetEnvironmentVariable('GSCAM_CONFIG', gscam_config),
        Node(
            package='gscam', executable='gscam_node', name='gscam_publisher',
            parameters=[{'image_encoding':'rgb8'},{'frame_id':'camera_frame'},
                        {'preroll':False},{'sync_sink':False}],
            output='screen'
        ),
        Node(
            package='opi_vision', executable='image_rate', name='image_rate',
            output='screen'
        ),
    ])