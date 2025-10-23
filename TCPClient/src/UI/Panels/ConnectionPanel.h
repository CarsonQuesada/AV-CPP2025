#pragma once

#include "UIPanel.h"
#include "Communication/VehicleClient.h"

class ConnectionPanel : public UIPanel
{
public:
    ConnectionPanel(UIContext& uiContext) : UIPanel(uiContext) {}
    ~ConnectionPanel() = default;

    void onUpdate() override;

private:
    float lastPingMs = -1.0f;

    void disconnectedDisplay();
    void connectedDisplay();
    void connectingDisplay();
    void reconnectingDisplay();
};
