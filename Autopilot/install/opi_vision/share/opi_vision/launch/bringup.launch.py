from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node

def generate_launch_description():
    gst_pipeline = (
        "v4l2src device=/dev/video11 io-mode=4 do-timestamp=true ! "
        "video/x-raw,format=NV12,width=1280,height=720,framerate=15/1,interlace-mode=progressive,colorimetry=1:3:5:1 ! "
        "capssetter caps=video/x-raw,colorimetry=2:3:5:1 replace=true ! "
        "videoconvert ! "
        "video/x-raw,format=BGR ! "
        "queue leaky=2 max-size-buffers=1 ! "
        "appsink name=appsink max-buffers=1 drop=true"
    )

    gscam = Node(
        package="gscam",
        executable="gscam_node",
        name="gscam",
        output="screen",
        parameters=[{
            "gscam_config": gst_pipeline,
            "image_encoding": "bgr8",   # matches format=BGR above
            "frame_id": "camera_frame",
            "use_gst_timestamps": True,
            "sync_sink": False,
            "camera_name": "orangepi_cam",
        }],
        remappings=[("camera/image_raw", "/camera/image_raw")],
    )

    # If your Python nodes still sometimes pick the wrong NumPy,
    # you can run them with your venv's python like this:
    yolo = ExecuteProcess(
        cmd=["/home/avcpp/AV-CPP2025/Autopilot/.venv/bin/python", "-m", "opi_vision.yolo_annotate"],
        output="screen"
    )
    mjpeg = ExecuteProcess(
        cmd=["/home/avcpp/AV-CPP2025/Autopilot/.venv/bin/python", "-m", "opi_vision.mjpeg_server"],
        output="screen"
    )
    rate = ExecuteProcess(
        cmd=["/home/avcpp/AV-CPP2025/Autopilot/.venv/bin/python", "-m", "opi_vision.image_rate"],
        output="screen"
    )

    return LaunchDescription([gscam, yolo, mjpeg, rate])
