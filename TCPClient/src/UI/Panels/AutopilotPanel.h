#pragma once

#include "UIPanel.h"

class AutopilotPanel : public UIPanel
{
public:
    AutopilotPanel(UIContext& uiContext) : UIPanel(uiContext) {}
    ~AutopilotPanel() = default;

    void onUpdate() override;

private:

};
