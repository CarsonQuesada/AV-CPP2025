#pragma once
#include <iostream>

//#include <pigpiod_if2.h>

#include "Shared/UserInputTypes.h"

#include "Pigpio.h"
#include "Lighting.h"
#include "Debug/Logger.h"

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
constexpr int brakeLightThresh = 0;

// Steering Constants
constexpr int deadband = 11;

// Singleton class for driving feature
class Drive
{
public:
    static Drive& get_instance() {
        static Drive instance; 
        return instance;
    }
    void initialize();
    inline void enable_steering(bool en) { gpio_write(piHandle, steering_EN, en); }
    inline void enable_motors(bool en) {
        if (en)
            LOG(LogLevel::INFO, "Enabled motors");
        else
            LOG(LogLevel::INFO, "Disabled motors");
        // Set drive motor enable pins (REN and FEN) to LOW to stop power to the motor
        gpio_write(piHandle, drive_FEN, en);
        gpio_write(piHandle, drive_REN, en);
        
        // Enable steering motor
        // Set steering motor enable pin to LOW to cut power to the steering mechanism
        gpio_write(piHandle, steering_EN, en);
    }
    inline void brake() { brake(100); }
    void brake(int brakeVal);
    void accelerate(int accelValue, Gear gear);
    void steer(int targetPos, int currPos);
    void cleanup();
private:
    bool initialized = false;
    bool braking;
    int piHandle;
    Lighting& lighting;

    Drive() : lighting(Lighting::get_instance()) {}                                // Private constructor to make sure there is only one instance
    Drive(const Drive&) = delete;             // Prevent copy construction
    Drive& operator=(const Drive&) = delete;  // Prevent assignment
    ~Drive();

    inline void relax_brakes();
};