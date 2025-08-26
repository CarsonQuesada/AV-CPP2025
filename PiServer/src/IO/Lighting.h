#pragma once

#include <pigpiod_if2.h>
#include <atomic>

#include "Shared/Message.h"
#include "Communication/VehicleServer.h"
#include "Pigpio.h"

constexpr int lightingAddr   = 6;                  // I2C address for lighting subsystem

// This enum is also used in lighting subsystem
// Any change to this one should be made to the other and vice versa
enum class LightingCommand : uint8_t
{
  Unkown = 0, 
  HeadlightsOn,   HeadlightsOff, 
  LeftSigOn,      LeftSigOff,
  RightSigOn,     RightSigOff,
  HazardsOn,      HazardsOff,
  BrakeLightsOn,  BrakeLightsOff, 
  StopConnecting, Connected,      Reconnecting
};

class Lighting
{
public:
    void setBrakeLights(bool en);
    void setReverseLights(bool en);
    void setRightSig(bool en);
    void setLeftSig(bool en);
    void setHeadlights(bool en);
    void setConnectLED(ServerConnectionState state);

    inline bool isBrakeLightsOn() const { return brakeLightsEnabled.load(); }
    inline bool isReverseLightsOn() const { return reverseLightsEnabled.load(); }
    inline bool isRightSigOn() const { return rightSigEnabled.load(); }
    inline bool isLeftSigOn() const { return leftSigEnabled.load(); }
    inline bool isHeadlightsOn() const { return headlightsEnabled.load(); }
    inline bool isHazardsOn() const { return hazardsEnabled.load(); }

    bool initialize();
    void cleanup();

    Lighting() {}
    ~Lighting();
private:
    bool initialized = false;

    // State information
    std::atomic<bool> brakeLightsEnabled{false};
    std::atomic<bool> reverseLightsEnabled{false};
    std::atomic<bool> rightSigEnabled{false};
    std::atomic<bool> leftSigEnabled{false};
    std::atomic<bool> headlightsEnabled{false};
    std::atomic<bool> hazardsEnabled{false};
    std::atomic<ServerConnectionState> connectLEDStatus{ServerConnectionState::Disconnected};

    int piHandle;
    int lightingAddress;
    int lightingHandle;
};