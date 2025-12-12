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

    std::string buildRtspUrl() const;

    FrameProcessor frameProcessor;
    FfmpegRtspClient videoStream;

    bool userEnabled = false;
    bool streaming = false;
    bool forceRemoteOnLocal = false;
    std::chrono::steady_clock::time_point lastToggle = std::chrono::steady_clock::now();

    bool urlDirty = true;
    ConnectionType currHost = ConnectionType::None;
    ConnectionType lastHost = ConnectionType::None;

    int prevWidth = 0;
    int prevHeight = 0;
    unsigned int texture = 0;
};