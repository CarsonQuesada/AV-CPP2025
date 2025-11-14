#pragma once

#include "UIPanel.h"

class ControllsPanel : public UIPanel
{
public:
    ControllsPanel(UIContext& uiContext) : UIPanel(uiContext) {}
    ~ControllsPanel() = default;

    void onUpdate() override;
private:

};