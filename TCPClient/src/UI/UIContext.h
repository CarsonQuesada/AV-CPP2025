#pragma once

#include "VehicleClient.h"
#include "VehicleController.h"

//class VehicleController;

struct UIContext {
    VehicleClient* client = nullptr;
    VehicleController* controller = nullptr;

    inline bool isConnected() const {
        return client ? client->isConnected() : false;
    }

    inline ConnectionType connectionType() const {
        return client ? client->getConnectionType() : ConnectionType::None;
    }
};
