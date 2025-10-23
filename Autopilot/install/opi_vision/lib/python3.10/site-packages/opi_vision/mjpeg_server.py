#!/usr/bin/env python3
import time, threading
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from flask import Flask, Response

app = Flask(__name__)

class MJPEGServer(Node):
    def __init__(self):
        super().__init__('mjpeg_server')
        self.declare_parameter('image_topic', '/camera/image_annotated/compressed')
        self.declare_parameter('bind', '0.0.0.0')
        self.declare_parameter('port', 8080)

        self.image_topic = self.get_parameter('image_topic').get_parameter_value().string_value
        self.bind = self.get_parameter('bind').get_parameter_value().string_value
        self.port = int(self.get_parameter('port').value)

        self._last = None
        self._lock = threading.Lock()
        self.sub = self.create_subscription(CompressedImage, self.image_topic, self.cb, 10)

        t = threading.Thread(target=self._run_flask, daemon=True)
        t.start()
        self.get_logger().info(f"Serving MJPEG at http://{self.bind}:{self.port}/stream from {self.image_topic}")

    def cb(self, msg: CompressedImage):
        with self._lock:
            self._last = msg.data

    def _run_flask(self):
        @app.route('/stream')
        def stream():
            def gen():
                while True:
                    with self._lock:
                        frame = self._last
                    if frame:
                        yield (b'--frame\r\nContent-Type: image/jpeg\r\n'
                               b'Content-Length: ' + str(len(frame)).encode() + b'\r\n\r\n' +
                               frame + b'\r\n')
                    time.sleep(0.03)  # ~33 fps cap
            return Response(gen(), mimetype='multipart/x-mixed-replace; boundary=frame')
        app.run(host=self.bind, port=self.port, debug=False, threaded=True, use_reloader=False)

def main():
    rclpy.init(); rclpy.spin(MJPEGServer()); rclpy.shutdown()

if __name__ == "__main__":
    main()
