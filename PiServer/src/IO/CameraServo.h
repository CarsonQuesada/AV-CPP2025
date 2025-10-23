#pragma once
#include <iostream>
#include <pigpiod_if2.h>

#include "Shared/Message.h"
#include "Pigpio.h"

constexpr int cameraServoPin = 18;                // Camera servo GPIO pin

constexpr int cameraLeftVal = 600;                // Value for mapping input to servo pulse width (turns left)
constexpr int cameraCenterVal = 1500;             // Value for centering the camera
constexpr int cameraRightVal = 2400;              // Value for mapping input to servo pulse width (turns right)

constexpr int minCameraInput = 3;                 // Minimum input for camera (turns left)
constexpr int maxCameraInput = 25;                // Maximuminput for camera (turns right)

// Singleton class for CameraServo
class CameraServo
{
public:
    void panCameraLeft();
    void panCameraRight();
    void centerCamera();

    bool initialize();
    void cleanup();

    CameraServo() {}  
    ~CameraServo();
private:
    bool initialized = false;
    int piHandle;
    int currPos;
};