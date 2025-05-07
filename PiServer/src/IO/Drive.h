#pragma once
#include <iostream>
#include <pigpiod_if2.h>
#include <atomic>

#include "Shared/VehicleCommand.h"
#include "Pigpio.h"

// --- Drive Motor Pin Assignments ---
constexpr int drive_FPWM     = 17;	// GPIO pin for controlling the drive motor's forward PWM signal
constexpr int drive_RPWM     = 27;	// GPIO pin for controlling the drive motor's reverse PWM signal
constexpr int drive_FEN      = 20;	// GPIO pin for enabling the drive motor in forward
constexpr int drive_REN      = 21;	// GPIO pin for enabling the drive motor in reverse

// --- Steering Motor Pin Assignments ---
constexpr int steering_RPWM  = 24;	// GPIO pin for controlling the steering motor's right-turn PWM signal
constexpr int steering_LPWM  = 23;	// GPIO pin for controlling the steering motor's left-turn PWM signal
constexpr int steering_EN  = 19;	// GPIO pin for enabling the steering motor

// --- Brake Servo Pin Assignment ---
constexpr int brakeServoPin  = 13;                  // Brake servo GPIO pin

// Servo and braking constants
constexpr int relaxedBrakeVal = 2050;               // Relaxed brake servo position
constexpr int fullBrakeVal = 2250;                  // Fully engaged brake servo position
constexpr int serialMaxBytes = 17;	      	     // Max bytes of string for processing in bus

// Steering Constants
constexpr int deadband = 11;

// Singleton class for driving feature
class Drive
{
public:
    void enableSteering(bool en);
    void enableMotors(bool en);
    void brake();
    void brake(int brakeVal);
    void relaxBrakes();
    void accelerate(int accelValue, GearID gear);
    void steer(int targetPos, int currPos);

    inline GearID getGear() const { return activeGear.load(); }
    inline bool isBraking() const { return braking.load(); }
    inline bool isMotorsEnabled() const { return motorsEnabled.load(); }
    inline bool isSteerEnabled() const { return steerEnabled.load(); }

    void initialize();
    void cleanup();

    Drive() {}  
    ~Drive();
private:
    bool initialized = false;
    int piHandle;

    std::atomic<GearID> activeGear{GearID::Coast};
    std::atomic<bool> braking{false};
    std::atomic<bool> motorsEnabled{false};
    std::atomic<bool> steerEnabled{false};
};