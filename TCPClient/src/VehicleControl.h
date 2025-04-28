#pragma once

#include <windows.h>
#include <optional>

#include "Shared/VehicleCommand.h"
#include "VehicleState.h"

// Keys for driving the vehicle
constexpr int forwardKey = VK_UP;
constexpr int reverseKey = VK_DOWN;
constexpr int leftTurnKey = VK_LEFT;
constexpr int rightTurnKey = VK_RIGHT;
constexpr int brakeKey =  VK_SPACE;

// Keys to toggle lights
constexpr int rightSigKey = 'X';
constexpr int leftSigKey = 'Z';
constexpr int headlightKey = 'H';

// Keys to control camera
constexpr int panCamLeftKey = 'Q';
constexpr int panCamRightKey = 'E';
constexpr int CenterCamKey = 'W';

// Other user inputs
constexpr int setMaxSpeedKey = '1';
constexpr int toggleAutopilotKey = '2';

class VehicleControl
{
public:
    VehicleControl() : vehicleState(VehicleState::getInstance()) {}
    ~VehicleControl() {}

    std::optional<VehicleCommand> genDriveCommand();
    std::optional<VehicleCommand> genLightsCommand();
    std::optional<VehicleCommand> genCameraCommand();
    std::optional<VehicleCommand> genMaxSpeedCommand();
    std::optional<VehicleCommand> genAutopilotCommand();
    std::optional<VehicleCommand> genStopCommand();

    inline bool isDown(int key) { return GetKeyState(key) & 0x8000; }
private:
    VehicleState& vehicleState;
};