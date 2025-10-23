#include "CameraServo.h"

#include "Utility.h"

void CameraServo::panCameraLeft()
{
    if (currPos < 25) // Ensure position doesn't exceed maximum
        currPos++; // Increment the current position
    set_servo_pulsewidth(piHandle, cameraServoPin, map(currPos, minCameraInput, maxCameraInput, cameraLeftVal, cameraRightVal)); // Control camera panning
}

void CameraServo::panCameraRight()
{
    if (currPos > 3) // Ensure position doesn't go below minimum
        currPos--; // Decrement the current position
    set_servo_pulsewidth(piHandle, cameraServoPin, map(currPos, minCameraInput, maxCameraInput, cameraLeftVal, cameraRightVal)); // Control camera panning
}

void CameraServo::centerCamera()
{
    currPos = 14; // Reset position to center
    set_servo_pulsewidth(piHandle, cameraServoPin, map(currPos, minCameraInput, maxCameraInput, cameraLeftVal, cameraRightVal)); // Control camera panning
}

bool CameraServo::initialize()
{
    set_servo_pulsewidth(piHandle, cameraServoPin, cameraCenterVal);
    return true;
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
