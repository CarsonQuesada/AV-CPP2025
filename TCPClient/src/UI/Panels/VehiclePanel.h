#pragma once

#include <functional>

#include "UIPanel.h"
#include "Communication/VehicleClient.h"
#include "VehicleController.h"

class VehiclePanel : public UIPanel
{
public:
    VehiclePanel(UIContext& uiContext) : UIPanel(uiContext) {}
    ~VehiclePanel() = default;

    void onUpdate() override;

private:
    // Vehicle state
    bool headlights = true;
    bool brakeLights = true;
    bool leftTurn = false;
    bool rightTurn = true;

    // Speed
    int maxSpeed = 50;
    int lastSentSpeed = 50;

    void addLightRow(const char* label, const char* keyHint, bool state);
};
