#pragma once

#include <iostream>
#include <cstdint>

enum class AutopilotCommandID : uint8_t
{
    Start = 0x01, 
    Stop = 0x02,
    Update = 0x03,

    Invalid = 0xFF
};

#pragma pack(push, 1)   // For packing the structs

struct StartACommand
{
    AutopilotCommandID commandID;
    // Add fields as needed
};

struct StopACommand
{
    AutopilotCommandID commandID;
    // Add fields as needed
};

struct UpdateACommand
{
    AutopilotCommandID commandID;
    float speed;
    // Add fields as needed
};

#pragma pack(pop)

union AutopilotCommand
{
    AutopilotCommandID commandID;
    StartACommand start;
    StopACommand stop;
    UpdateACommand update;
};

inline size_t getCommandSize(const AutopilotCommand& cmd)
{
    switch (cmd.commandID)
    {
        case AutopilotCommandID::Start:   return sizeof(StartACommand);
        case AutopilotCommandID::Stop:    return sizeof(StopACommand);
        case AutopilotCommandID::Update:  return sizeof(UpdateACommand);
        case AutopilotCommandID::Invalid: return 0;
        default: 
            std::cout << "Not Sending a valid command. ID: " << static_cast<int>(cmd.commandID) << std::endl; 
            return 0;
    }
}
