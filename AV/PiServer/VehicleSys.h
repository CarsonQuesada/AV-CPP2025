#pragma once

#include "Shared/UserInputTypes.h"

#include "IO/ADC.h"
#include "IO/Drive.h"
#include "IO/GPS.h"
#include "IO/LidarSP.h"
#include "IO/Lighting.h"
#include "IO/Pigpio.h"
#include "IO/SerialPort.h"
#include "IO/CameraServo.h"

class VehicleSys 
{
public:
    VehicleSys();
    ~VehicleSys();

    bool init_io();
    void shutdown();
    void enable_vehicle(bool en);
    inline void set_max_accel(int maxAccel) { accelScalar = (float)maxAccel / 100.0; }

    inline void enable_av_led(bool en) { lighting.enable_av_status_led(en); }
    void handle_camera_input(CameraCommand cameraCommand);
    void handle_other_input(OtherInput controlInput);
    inline void brake(int brakeVal) { drive.brake(brakeVal); }
    inline void accelerate(int accelVal, Gear gear) { drive.accelerate(accelVal * accelScalar, gear); }
    inline void steer(int steerVal) {
        int currPos = adc.get_steering_feedback();
        printf("Actual steering position: %d\n", currPos);
    
        drive.steer(steerVal, currPos);
    }
private:
    float accelScalar;
    OtherInput prevControlInput = OtherInput::NoInput;

    // IO Devices
    Pigpio& pi;
    Lighting& lighting;
    ADC& adc;
    LidarSP& lidarSP;
    GPS& gps;
    Drive& drive;
    CameraServo& cameraServo;
};
