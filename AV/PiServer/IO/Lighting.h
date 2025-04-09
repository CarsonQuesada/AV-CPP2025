#pragma once

//#include <pigpiod_if2.h>

#include "Pigpio.h"

constexpr int lightingAddr   = 6;                  // I2C address for lighting subsystem

// This enum is also used in lighting subsystem
// Any change to this one should be made to the other and vice versa
enum class LightingCommand
{
  Unkown = 0, HeadlightsOn, HeadlightsOff, ToggleLeftSig, ToggleRightSig,
  ToggleHazards, BrakeLightsOn, BrakeLightsOff, AVLightOn, AVLightOff
};

class Lighting
{
public:
    static Lighting& get_instance() {
      static Lighting instance; 
      return instance;
    }

    bool initialize();
    void enable_brake_lights(bool enable);
    void enable_av_status_led(bool enable);
    void enable_reverse_lights(bool enable);
    void toggle_right_turn_signal();
    void toggle_left_turn_signal();
    void toggle_headlights();
    void cleanup();
private:
    bool initialized = false;
    bool brakeLightsEnabled;
    bool avStatusLedEnabled;
    bool reverseLightsEnabled;
    bool rightTurnSignalEnabled;
    bool leftTurnSignalEnabled;
    bool headlightsEnabled;

    int piHandle;
    int lightingAddress;
    int lightingHandle;

    Lighting() {}                              // Private constructor to make sure there is only one instance
    Lighting(const Lighting&) = delete;             // Prevent copy construction
    Lighting& operator=(const Lighting&) = delete;  // Prevent assignment
    ~Lighting();
};