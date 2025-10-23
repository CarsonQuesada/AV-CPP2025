#pragma once

#include "Shared/Message.h"

class VehicleState
{
public:
    static VehicleState& getInstance() {
        static VehicleState instance;
        return instance;
    }

    LightsStatus lightStatus;
    StateMode stateMode;
    DriveStatus driveStatus;
    GeneralStatus genStatus;

private:
    VehicleState() {}                                   // private constructor to prevent more than one instance
    VehicleState(const VehicleState&) = delete;               // Prevent copy construction
    VehicleState& operator=(const VehicleState&) = delete;    // Prevent assignment
    ~VehicleState() {}
};