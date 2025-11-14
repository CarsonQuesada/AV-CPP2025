#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <optional>
#include "Message.h"

inline std::string hexDump(const uint8_t* p, size_t n) {
    std::ostringstream os; os<<std::hex<<std::setfill('0');
    for (size_t i=0;i<n;++i){ os<<std::setw(2)<<unsigned(p[i])<<(i+1<n?' ':'\0'); }
    return os.str();
}

inline const char* msgName(MessageID id){
    switch(id){
        case MessageID::Ping: return "Ping";
        case MessageID::Drive: return "Drive";
        case MessageID::ToggleLights: return "ToggleLights";
        case MessageID::SetMaxSpeed: return "SetMaxSpeed";
        case MessageID::ClientInit: return "ClientInit";
        case MessageID::StartAutopilot: return "StartAutopilot";
        case MessageID::StopAutopilot: return "StopAutopilot";
        case MessageID::TelemetryData: return "TelemetryData";
        case MessageID::LightsStatus: return "LightsStatus";
        case MessageID::GeneralStatus: return "GeneralStatus";
        case MessageID::DriveStatus: return "DriveStatus";
        case MessageID::StateMode: return "StateMode";
        case MessageID::ServerInit: return "ServerInit";
        case MessageID::Error: return "Error";
        case MessageID::Disconnected: return "Disconnected";
        case MessageID::Invalid: return "Invalid";
        default: return "Unknown";
    }
}

// For your current protocol all are fixed-size; adjust if any become variable.
inline std::optional<size_t> expectedPayloadSize(MessageID id){
    switch(id){
        case MessageID::Ping:            return sizeof(Ping);
        case MessageID::Drive:           return sizeof(DriveCommand);
        case MessageID::ToggleLights:    return sizeof(LightsCommand);
        case MessageID::SetMaxSpeed:     return sizeof(SetMaxSpeedCommand);
        case MessageID::ClientInit:      return sizeof(ClientInit);
        case MessageID::StartAutopilot:  return sizeof(StartAutopilotCommand);
        case MessageID::StopAutopilot:   return sizeof(StopAutopilotCommand);
        case MessageID::TelemetryData:   return sizeof(TelemetryData);
        case MessageID::LightsStatus:    return sizeof(LightsStatus);
        case MessageID::GeneralStatus:   return sizeof(GeneralStatus);
        case MessageID::DriveStatus:     return sizeof(DriveStatus);
        case MessageID::StateMode:       return sizeof(StateMode);
        case MessageID::ServerInit:      return sizeof(ServerInit);
        case MessageID::Error:           return sizeof(ErrorMessage);
        default:                         return std::nullopt; // unknown/invalid/not on wire
    }
}
