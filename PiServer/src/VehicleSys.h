#pragma once
#include <atomic>

#include "Shared/VehicleCommand.h"
#include "Shared/AutopilotFeedback.h"
#include "Shared/TCPCommunication.h"

#include "IO/ADC.h"
#include "IO/Drive.h"
#include "IO/Lighting.h"
#include "IO/CameraServo.h"

constexpr int brakeLightThresh = 10;

class VehicleSys 
{
public:
    static inline VehicleSys& getInstance() 
    {
        static VehicleSys vehicleSysInstance;
        return vehicleSysInstance;
    }

    void disableVehicle();
    void enableVehicle();
    void handleDisconnect();
    void handleDriveInput(DriveVCommand command);
    void handleDriveInput(DriveAFeedback command);
    void handleCameraInput(CameraVCommand command);
    void setMaxSpeed(SetMaxSpeedVCommand command);
    void handleLightsInput(LightsVCommand command);
    void setConnectionStatus(ConnectionStatus status);
    inline void setAutopilotActive(bool acitve) { autopilotAcitve.store(acitve); }

    // Vehicle state information
    inline GearID getGear() { return drive.getGear(); }
    inline bool isAutopilotActive() const { return autopilotAcitve.load(); }
    inline bool isBrakeLightsOn() { return lighting.isBrakeLightsOn(); }
    inline bool isReverseLightsOn() { return lighting.isReverseLightsOn(); }
    inline bool isRightSigOn() { return lighting.isRightSigOn(); }
    inline bool isLeftSigOn() { return lighting.isLeftSigOn(); }
    inline bool isHeadlightsOn() { return lighting.isHeadlightsOn(); }
    inline bool isBraking() { return drive.isBraking(); }

    bool initIO();
    void shutdown();

private:
    float accelScalar = 0.0;

    // Vehicle State information
    std::atomic<bool> autopilotAcitve;
    std::atomic<ConnectionStatus> connectionStatus;

    // IO Devices
    Lighting lighting;
    ADC adc;
    Drive drive;
    CameraServo cameraServo;

    VehicleSys() {}                                   // private constructor to prevent more than one instance
    VehicleSys(const VehicleSys&) = delete;               // Prevent copy construction
    VehicleSys& operator=(const VehicleSys&) = delete;    // Prevent assignment
    ~VehicleSys();
};
