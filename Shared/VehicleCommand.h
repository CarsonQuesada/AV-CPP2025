#pragma once

#include <iostream>
#include <cstdint>

#include "AutopilotCommand.h"

enum class GearID : uint8_t
{
    NoInput = 0x00, Coast = 0x01, Forward = 0x02, Reverse = 0x03
};

enum class LightID : uint8_t
{
    NoInput = 0x00, LeftTurnSig = 0x01, RightTurnSig = 0x02, Headlights = 0x03
};

enum class CameraCmdID : uint8_t
{
    NoInput = 0x00, PanCameraLeft = 0x01, CenterCamera = 0x02, PanCameraRight = 0x03
};

enum class VehicleCommandID : uint8_t {
    Ping = 0x00,    // used to notify it is still connected
    Drive = 0x01,
    ToggleLights = 0x02,
    MoveCamera = 0x03,
    SetMaxSpeed = 0x04,
    Autopilot = 0x05,

    // Should not be sent over TCP
    Disconnected = 0xFE,
    Invalid = 0xFF
};

#pragma pack(push, 1)   // For packing the structs

// Ping command
struct PingVCommand {
    VehicleCommandID commandID;  // 0x00
};

// Drive command
struct DriveVCommand {
    VehicleCommandID commandID;  // 0x01
    uint8_t brake;  // Value 0-100
    GearID gear;
    uint8_t speed;  // Value 0-100
    uint8_t steer;  // Value 0-100
};

// Lights command
struct LightsVCommand {
    VehicleCommandID commandID;  // 0x02
    LightID lightID;
    uint8_t on;  // 0 = off, 1 = on
};

// Camera command
struct CameraVCommand {
    VehicleCommandID commandID;  // 0x03
    CameraCmdID cameraMove;
};

// Set max speed command
struct SetMaxSpeedVCommand {
    VehicleCommandID commandID;  // 0x04
    uint8_t maxSpeed;   // Value 1-100
};

// Set max speed command
struct AutopilotVCommand {
    VehicleCommandID commandID;  // 0x05
    AutopilotCommandID autopilotCmd;
};

// Disconnected command (Do not send across TCP)
struct DisconnectedVCommand {
    VehicleCommandID commandID;  // 0xFE
};

// Invalid command (Do not send across TCP)
struct InvalidVCommand {
    VehicleCommandID commandID;  // 0xFF
};

#pragma pack(pop)

union VehicleCommand {
    VehicleCommandID commandID;
    PingVCommand ping;
    DriveVCommand drive;
    LightsVCommand lights;
    CameraVCommand camera;
    SetMaxSpeedVCommand setMaxSpeed;
    AutopilotVCommand autopilot;
    DisconnectedVCommand disconnected;
    InvalidVCommand invalid;
};

inline size_t getCommandSize(const VehicleCommand& cmd)
{
    switch (cmd.commandID)
    {
        case VehicleCommandID::Ping:         return sizeof(PingVCommand);
        case VehicleCommandID::Drive:        return sizeof(DriveVCommand);
        case VehicleCommandID::MoveCamera:   return sizeof(CameraVCommand);
        case VehicleCommandID::SetMaxSpeed:  return sizeof(SetMaxSpeedVCommand);
        case VehicleCommandID::Autopilot:    return sizeof(AutopilotVCommand);
        case VehicleCommandID::ToggleLights: return sizeof(LightsVCommand);
        case VehicleCommandID::Disconnected: return sizeof(DisconnectedVCommand);
        case VehicleCommandID::Invalid:      return sizeof(InvalidVCommand);
        default: 
            std::cout << "Not Sending a valid command. ID: " << static_cast<int>(cmd.commandID) << std::endl; 
            return 0;
    }
}