#pragma once

#include "VehicleCommand.h"

enum class AutopilotFeedbackID : uint8_t 
{
    Drive = 0x00,
    Status = 0x01,
    Error = 0x02,

    Invalid = 0xFF
};

enum class AutopilotErrorCode : uint8_t
{
    GPSOffline = 0x00,

    NoError = 0xFF
};

#pragma pack(push, 1)   // For packing the structs

struct DriveAFeedback {
    AutopilotFeedbackID feedbackID;
    DriveVCommand drive;
};

struct StatusAFeedback {
    AutopilotFeedbackID feedbackID;
    uint8_t gpsConnected;   // 1 = true, 0 = false
    uint8_t lidarReady;   // 1 = true, 0 = false
};

struct ErrorAFeedback {
    AutopilotFeedbackID feedbackID;
    AutopilotErrorCode errorCode;
};

struct InvalidAFeedback {
    AutopilotFeedbackID feedbackID;
};

#pragma pack(pop)

union AutopilotFeedback {
    AutopilotFeedbackID feedbackID;
    DriveAFeedback drive;
    StatusAFeedback status;
    ErrorAFeedback error;
};

inline size_t getFeedbackSize(const AutopilotFeedback& fb)
{
    switch (fb.feedbackID)
    {
        case AutopilotFeedbackID::Drive:   return sizeof(DriveAFeedback);
        case AutopilotFeedbackID::Status:  return sizeof(StatusAFeedback);
        case AutopilotFeedbackID::Error:   return sizeof(ErrorAFeedback);
        case AutopilotFeedbackID::Invalid: return sizeof(InvalidAFeedback);
        default: std::cout << "Not Sending a valid Feedback" << std::endl; return 0;
    }
}