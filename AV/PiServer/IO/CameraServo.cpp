#include "CameraServo.h"

#include "Utility.h"
#include "Debug/Logger.h"

void CameraServo::initialize()
{
    set_servo_pulsewidth(piHandle, cameraServoPin, cameraCenterVal);
}

void CameraServo::cleanup()
{
    if (initialized)
    {
        initialized = false;
        set_servo_pulsewidth(piHandle, cameraServoPin, cameraCenterVal); // Control camera panning
    }
    else
        printf("WARNING: Tried closing ADC I2C connection without initialization\n");
}

CameraServo::~CameraServo()
{
    if (initialized)
        set_servo_pulsewidth(piHandle, cameraServoPin, cameraCenterVal); // Control camera panning
}
