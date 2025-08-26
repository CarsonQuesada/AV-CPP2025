#pragma once

#include "UIPanel.h"
#include "Communication/VehicleClient.h"

class ControllsPanel : public UIPanel
{
public:
    ControllsPanel(UIContext& uiContext) : UIPanel(uiContext) {}
    ~ControllsPanel() = default;

    void onUpdate() override;
private:

};