#pragma once
#include <cstring>
#include <cstdint>
#include <vector>
#include <stdexcept>

enum class MessageID : uint8_t {
    // To Vehicle
    Ping = 0,    // used to notify it is still connected
    Drive = 1,
    ToggleLights = 2,
    MoveCamera = 3,
    SetMaxSpeed = 4,
    ClientInit = 5,

    // To Autopilot
    StartAutopilot = 50, 
    StopAutopilot = 51,
    TelemetryData = 52,

    // To Client 
    LightsStatus = 100,
    GeneralStatus = 101,
    DriveStatus = 102,
    AutopilotStatus = 103,
    ServerInit = 104,
    Error = 105,

    // Should not be sent over TCP
    Disconnected = 254,
    Invalid = 255
};

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

enum class ErrorCode 
{
    GPSOffline = 0x00,
    // Add fields as needed

    NoError = 0xFF
};

#pragma pack(push, 1)

struct MessageHeader {
    uint32_t payloadLength;
    MessageID messageID;
};

struct Message {
    MessageID messageID;
    std::vector<uint8_t> payload;
};

struct Ping {
    uint64_t clientSendTimeNs;
};

struct DriveCommand {
    uint8_t brake;  // Value 0-100
    GearID gear;
    uint8_t speed;  // Value 0-100
    uint8_t steer;  // Value 0-100
};

struct LightsCommand {
    LightID lightID;
};

struct CameraCommand {
    CameraCmdID cameraMove;
};

struct SetMaxSpeedCommand {
    uint8_t maxSpeed;       // Value 1-100
};

struct ClientInit {
    // Add feilds as needed
};

// Suggestion: Use bitfield here
struct LightsStatus {
    uint8_t brakeLights;    // 1 = true, 0 = false
    uint8_t reverseLights;  // 1 = true, 0 = false
    uint8_t rightSig;       // 1 = true, 0 = false
    uint8_t leftSig;        // 1 = true, 0 = false
    uint8_t Headlights;     // 1 = true, 0 = false
    uint8_t hazards;        // 1 = true, 0 = false
};

struct GeneralStatus {
    uint32_t speed;
    uint32_t batteryPercent; // 0-100%
    uint8_t gpsOnline;       // 1 = true, 0 = false
    // Add feilds as needed (max speed maybe)
};

struct DriveStatus {
    GearID gear;
    uint8_t braking;        // 1 = true, 0 = false
    // Add feilds as needed
};

struct AutopilotStatus {
    uint8_t autopilotActive; // 1 = true, 0 = false
    uint8_t lidarReady;      // 1 = true, 0 = false
};

struct ServerInit {
    GeneralStatus generalStatus;
    LightsStatus lightsStatus;
    DriveStatus driveStatus;
    AutopilotStatus autopilotStatus;
    // Add feilds as needed
};

struct StartAutopilotCommand {
    // Add fields as needed
};

struct StopAutopilotCommand {
    // Add fields as needed
};

struct TelemetryData {
    uint8_t gpsOnline;      // 1 = true, 0 = false
    float lat;              // degrees
    float lon;              // degrees
    float heading;          // degrees
    float speed;            // m/s
    float distanceDelta;    // m
};

struct ErrorMessage {
    ErrorCode errorCode;
};

// Disconnected command (Do not send across TCP)
struct Disconnected  {
    // Add more fields as needed
};

struct InvalidMessage {
    // Add more fields as needed
};

#pragma pack(pop)

template<typename T>
constexpr MessageID getMessageID() {
    static_assert(sizeof(T) == 0, "getMessageID() not specialized for this type.");
    return {}; // Not reachable
}

#define REGISTER_MESSAGE_ID(TYPE, IDVAL) \
    template<> constexpr MessageID getMessageID<TYPE>() { return IDVAL; }

REGISTER_MESSAGE_ID(Ping, MessageID::Ping)
REGISTER_MESSAGE_ID(DriveCommand, MessageID::Drive)
REGISTER_MESSAGE_ID(LightsCommand, MessageID::ToggleLights)
REGISTER_MESSAGE_ID(CameraCommand, MessageID::MoveCamera)
REGISTER_MESSAGE_ID(SetMaxSpeedCommand, MessageID::SetMaxSpeed)
REGISTER_MESSAGE_ID(ClientInit, MessageID::ClientInit)
REGISTER_MESSAGE_ID(StartAutopilotCommand, MessageID::StartAutopilot)
REGISTER_MESSAGE_ID(StopAutopilotCommand, MessageID::StopAutopilot)
REGISTER_MESSAGE_ID(TelemetryData, MessageID::TelemetryData)
REGISTER_MESSAGE_ID(LightsStatus, MessageID::LightsStatus)
REGISTER_MESSAGE_ID(GeneralStatus, MessageID::GeneralStatus)
REGISTER_MESSAGE_ID(DriveStatus, MessageID::DriveStatus)
REGISTER_MESSAGE_ID(AutopilotStatus, MessageID::AutopilotStatus)
REGISTER_MESSAGE_ID(ServerInit, MessageID::ServerInit)
REGISTER_MESSAGE_ID(ErrorMessage, MessageID::Error)


template<typename T>
Message makeMessageFrom(const T& msg)
{
    Message toSend;
    toSend.messageID= getMessageID<T>();  // use T, not drive
    toSend.payload.resize(sizeof(T));
    std::memcpy(toSend.payload.data(), &msg, sizeof(T));
    return toSend;
}

template <typename T>
T extractPayload(const Message& message) {
    if (message.payload.size() != sizeof(T)) {
        throw std::runtime_error("Payload size does not match expected struct size.");
    }

    T result;
    std::memcpy(&result, message.payload.data(), sizeof(T));
    return result;
}
