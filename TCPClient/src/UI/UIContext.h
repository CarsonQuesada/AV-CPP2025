#pragma once

#include "Communication/VehicleClient.h"
class VehicleController;

struct UIContext {
    VehicleClient* client = nullptr;
    VehicleController* controller = nullptr;

    inline bool isConnected() const {
        return client && (client->getConnectionState() == ClientConnectionState::Connected);
    }
};
