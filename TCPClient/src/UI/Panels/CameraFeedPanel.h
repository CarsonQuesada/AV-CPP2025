#pragma once

#include "UIPanel.h"
#include "MJPEGClient.h"
#include "FrameProcessor.h"
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

    inline std::string BuildMjpegUrl(ConnectionType type) const{
        switch (type) {
            case ConnectionType::Local:
                return "http://" + std::string(LOCAL_PI_IP) + ":" + std::to_string(LOCAL_VIDEO_PORT) + "/stream?topic=/camera/image_raw&width=640&height=360&fps=10&quality=50";
            case ConnectionType::Remote:
                return "http://" + std::string(VM_PUBLIC_IP) + ":" + std::to_string(REMOTE_VIDEO_PORT) + "/stream?topic=/camera/image_raw&width=640&height=360&fps=10&quality=50";
            default:
                return "";
        }
    }

    FrameProcessor frameProcessor;
    MJPEGClient videoStream;
    bool userEnabled = false;
    bool streaming = false;
    bool forceRemoteOnLocal = false;
    std::chrono::steady_clock::time_point lastToggle = std::chrono::steady_clock::now();

    int prevWidth = 0;
    int prevHeight = 0;
    unsigned int texture = 0;
};