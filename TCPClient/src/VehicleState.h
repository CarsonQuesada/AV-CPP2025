#pragma once

#include "Shared/Message.h"

class VehicleState
{
public:
    static VehicleState& getInstance() {
        static VehicleState instance;
        return instance;
    }

    bool headlightsOn = false;
    bool brakeLightsOn = false;
    bool leftSigOn = false;
    bool rightSigOn = false;

    GearID gear;
    bool braking;

    bool autopilotActive = false;
    float currentSpeed = 0.0f;

private:
    VehicleState() {}                                   // private constructor to prevent more than one instance
    VehicleState(const VehicleState&) = delete;               // Prevent copy construction
    VehicleState& operator=(const VehicleState&) = delete;    // Prevent assignment
    ~VehicleState() {}
};