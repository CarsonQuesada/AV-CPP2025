#pragma once
#include <iostream>

#include "Pigpio.h"
#include "Shared/UserInputTypes.h"
#include "Utility.h"

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
    static CameraServo& get_instance() {
        static CameraServo instance; 
        return instance;
    }
    inline void pan_camera_left() { 
        if (currPos < 25) // Ensure position doesn't exceed maximum
            currPos++; // Increment the current position
        set_servo_pulsewidth(piHandle, cameraServoPin, map(currPos, minCameraInput, maxCameraInput, cameraLeftVal, cameraRightVal)); // Control camera panning
    }
    inline void pan_camera_right() {
        if (currPos > 3) // Ensure position doesn't go below minimum
            currPos--; // Decrement the current position
        set_servo_pulsewidth(piHandle, cameraServoPin, map(currPos, minCameraInput, maxCameraInput, cameraLeftVal, cameraRightVal)); // Control camera panning
    }
    inline void center_camera() {
        currPos = 14; // Reset position to center
        set_servo_pulsewidth(piHandle, cameraServoPin, map(currPos, minCameraInput, maxCameraInput, cameraLeftVal, cameraRightVal)); // Control camera panning
    }
    void initialize();
    void cleanup();
private:
    bool initialized = false;
    int piHandle;
    int currPos;

    CameraServo() {}                              // Private constructor to make sure there is only one instance
    CameraServo(const CameraServo&) = delete;             // Prevent copy construction
    CameraServo& operator=(const CameraServo&) = delete;  // Prevent assignment
    ~CameraServo();
};