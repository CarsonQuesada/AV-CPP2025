#!/usr/bin/env python3
import http.server
import socketserver
import webbrowser
import threading
import time

class WebVisualizerServer:
    def __init__(self, port=8000):
        self.port = port
        self.handler = http.server.SimpleHTTPRequestHandler
        self.httpd = None
        
    def start(self):
        # Start HTTP server in a separate thread
        def serve():
            with socketserver.TCPServer(("", self.port), self.handler) as httpd:
                self.httpd = httpd
                print(f"Web visualizer server running at http://localhost:{self.port}")
                print("Open http://localhost:8000/lidar_viewer.html in your browser")
                httpd.serve_forever()
        
        server_thread = threading.Thread(target=serve)
        server_thread.daemon = True
        server_thread.start()
        
        # Give server time to start
        time.sleep(2)
        
        # Try to open browser automatically (may not work on headless systems)
        try:
            webbrowser.open(f'http://localhost:{self.port}/lidar_viewer.html')
        except:
            print("Could not open browser automatically. Please open manually.")

if __name__ == "__main__":
    server = WebVisualizerServer()
    server.start()
    
    try:
        # Keep the main thread alive
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nShutting down web server...")
