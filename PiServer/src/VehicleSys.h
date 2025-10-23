#pragma once
#include <atomic>

#include "Shared/Message.h"

#include "IO/ADC.h"
#include "IO/Drive.h"
#include "IO/Lighting.h"
#include "IO/CameraServo.h"
#include "IO/Telemetry.h"

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
    void handleDriveInput(DriveCommand command);
    void handleCameraInput(CameraCommand command);
    void setMaxSpeed(SetMaxSpeedCommand command);
    void handleLightsInput(LightsCommand command);
    void setConnectStatusLED(ServerConnectionState state);
    inline void setAutopilotActive(bool acitve) { autopilotActive.store(acitve); }

    // Vehicle state information
    inline bool isAutopilotActive() const { return autopilotActive.load(); }
    LightsStatus getLightsStatus();
    GeneralStatus getGeneralStatus();
    DriveStatus getDriveStatus();
    inline TelemetryData getTelemetryData() { return telemetryData; }
    inline StateMode getStateMode() { return stateMode; }
    inline bool consumeLightsStatusDirty() { return lightsStatusDirty.exchange(false); }

    void statusUpdate();
    bool initIO();
    void shutdown();

private:
    std::chrono::_V2::steady_clock::time_point lastStatusTime;
    mutable std::mutex dataMutex;
    mutable std::mutex lightsMutex;
    float accelScalar = 0.0;

    // Vehicle State information
    std::atomic<bool> autopilotActive = false;
    std::atomic<bool> lightsStatusDirty = false; // Set true when a light's state changes (except connect status LED)
    float batteryPercent = 0.0;
    TelemetryData telemetryData;
    StateMode stateMode;

    // IO Devices
    Lighting lighting;
    ADC adc;
    Drive drive;
    CameraServo cameraServo;
    Telemetry telemetry;

    void relaxBrakes();
    void brake();
    void brake(int brakeVal);

    VehicleSys() {}                                   // private constructor to prevent more than one instance
    VehicleSys(const VehicleSys&) = delete;               // Prevent copy construction
    VehicleSys& operator=(const VehicleSys&) = delete;    // Prevent assignment
    ~VehicleSys();
};
