#pragma once

#include "UIPanel.h"
#include "UI/MJPEGClient.h"
#include "UI/FrameProcessor.h"

class CameraFeedPanel : public UIPanel
{
public:
    CameraFeedPanel(UIContext& uiContext, FrameProcessor& fp);
    ~CameraFeedPanel();

    void onUpdate() override;
private:
    FrameProcessor& frameProcessor;
    int prevWidth = 0;
    int prevHeight = 0;
    unsigned int texture = 0;
};