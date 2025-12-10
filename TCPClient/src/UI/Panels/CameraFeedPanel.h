#pragma once

#include "UIPanel.h"
#include "video/FfmpegRtspClient.h"
#include "video/FrameProcessor.h"
#include "Shared/Keys.h"

class CameraFeedPanel : public UIPanel
{
public:
    CameraFeedPanel(UIContext& uiContext);
    ~CameraFeedPanel();

    void onUpdate() override;
private:
    void startStream();
    void stopStream();
    bool canToggle() const;

    inline std::string BuildRtspUrl(ConnectionType type) const {
        // const char* host = nullptr;
        // const char* port = nullptr;
        // switch (type) {
        //     case ConnectionType::Local:  
        //         host = LOCAL_PI_IP;  
        //         port = std::to_string(LOCAL_VIDEO_PORT).c_str();  
        //         break; // Pi on LAN
        //     case ConnectionType::Remote: 
        //         host = VM_PUBLIC_IP; 
        //         port = std::to_string(REMOTE_VIDEO_PORT).c_str(); 
        //         break; // your cloud VM
        //     default: return "";
        // }
        // // Adjust 8554 or "stream1" if your server uses a different port/path
        // return std::string("rtsp://") + host + ":" + port + "/stream1";
        return std::string("rtsp://") + LOCAL_PI_IP + ":8554/stream";
    }

    FrameProcessor frameProcessor;
    FfmpegRtspClient videoStream;
    bool userEnabled = false;
    bool streaming = false;
    bool forceRemoteOnLocal = false;
    std::chrono::steady_clock::time_point lastToggle = std::chrono::steady_clock::now();

    int prevWidth = 0;
    int prevHeight = 0;
    unsigned int texture = 0;
};