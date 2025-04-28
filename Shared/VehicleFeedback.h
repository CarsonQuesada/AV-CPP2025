#pragma once

#include "VehicleCommand.h"

enum class VehicleFeedbackID : uint8_t 
{
    Ping = 0x00,
    VehicleStatus = 0x01,
    BatteryInfo = 0x02,
    Error = 0x03,

    // Should not be sent over TCP
    Disconnected = 0xFE,
    Invalid = 0xFF,
};

enum class VehicleErrorCode 
{
    GPSOffline = 0x00,
    // Add fields as needed

    NoError = 0xFF
};

#pragma pack(push, 1)   // For packing the structs

struct PingVFeedback {
    VehicleFeedbackID feedbackID;
};

struct StatusVFeedback {
    VehicleFeedbackID feedbackID;
    uint8_t speed; // 0-100
    uint8_t rightSigOn; // 1 = true, 0 = false
    uint8_t leftSigOn; // 1 = true, 0 = false
    uint8_t headlightsOn; // 1 = true, 0 = false
    uint8_t autopilotActive;  // 1 = true, 0 = false
    uint8_t braking; // 1 = true, 0 = false
    GearID gear;
};

struct BatteryVFeedback {
    VehicleFeedbackID feedbackID;
    uint8_t batteryPercent; // 0-100%
    uint8_t charging; // 0 = not charging, 1 = charging
};

struct ErrorVFeedback {
    VehicleFeedbackID feedbackID;
    VehicleErrorCode errorCode;
};

// Disconnected feedback (Do not send across TCP)
struct DisconnectedVFeedback {
    VehicleFeedbackID feedbackID;
};

// Invalid feedback (Do not send across TCP)
struct InvalidVFeedback {
    VehicleFeedbackID feedbackID;
};

#pragma pack(pop)

union VehicleFeedback {
    VehicleFeedbackID feedbackID;
    StatusVFeedback status;
    BatteryVFeedback battery;
    ErrorVFeedback error;
    DisconnectedVFeedback disconnected;
    InvalidVFeedback invalid;
};

inline size_t getFeedbackSize(const VehicleFeedback& fb)
{
    switch (fb.feedbackID)
    {
        case VehicleFeedbackID::Ping:          return sizeof(PingVFeedback);
        case VehicleFeedbackID::VehicleStatus: return sizeof(StatusVFeedback);
        case VehicleFeedbackID::BatteryInfo:   return sizeof(BatteryVFeedback);
        case VehicleFeedbackID::Error:         return sizeof(ErrorVFeedback);
        case VehicleFeedbackID::Disconnected:  return sizeof(DisconnectedVFeedback);
        case VehicleFeedbackID::Invalid:       return sizeof(InvalidVFeedback);
        default: std::cout << "Not Sending a valid Feedback" << std::endl; return 0;
    }
}