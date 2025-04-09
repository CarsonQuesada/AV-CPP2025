#include "Lighting.h"

bool Lighting::initialize()
{
    if(!initialized) {
        piHandle = Pigpio::get_instance().get_handle();
        lightingHandle = i2c_open(piHandle, 1, lightingAddr, 0);

        if (lightingHandle < 0) {
            printf("[!] Failed to init lidar!\n");
        } else {
            printf("> lighting subsystem \t\tINIT OK\n");
            enable_brake_lights(false);
            initialized = true;
        }
    } else {
        printf("Lighting already initialized\n");
    }
    return initialized;
}

void Lighting::enable_brake_lights(bool enable)
{
    // Check to see if enable will change light's state. If not do nothing
    if (enable != brakeLightsEnabled) {
        if (enable)
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::BrakeLightsOn)); // Command to activate brake lights
        else
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::BrakeLightsOff)); // Command to deactivate brake lights

        // Update brake light status
        brakeLightsEnabled = enable;
    }
}

void Lighting::enable_av_status_led(bool enable)
{
    // Check to see if enable will change light's state. If not do nothing
    if (enable != avStatusLedEnabled) {
        if (enable)
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::AVLightOn)); // Command to activate av status led
        else
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::AVLightOff)); // Command to deactivate av status led

        // Update cv status led light
        avStatusLedEnabled = enable;
    }
}

void Lighting::enable_reverse_lights(bool enable)
{
    // Check to see if enable will change light's state. If not do nothing
    if (enable != reverseLightsEnabled) {
        if (enable) {
            // Uncomment and replace `6` with the correct I²C command for activating reverse lights
			//i2c_write_byte(piHandle, lightingHandle, 6);
        }
        else {
            // Uncomment and replace `7` with the correct I²C command for deactivating reverse lights
			//i2c_write_byte(piHandle, lightingHandle, 7);
        }

        // Update cv status led light
        reverseLightsEnabled = enable;
    }
}

void Lighting::toggle_right_turn_signal()
{
    // If right turn signal toggle off
    if (leftTurnSignalEnabled)
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::ToggleLeftSig));

    // Command to toggle right turn signal
    i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::ToggleRightSig));

    rightTurnSignalEnabled = !rightTurnSignalEnabled;
}

void Lighting::toggle_left_turn_signal()
{
    // If right turn signal toggle off
    if (rightTurnSignalEnabled)
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::ToggleRightSig));

    // Command to toggle left turn signal
    i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::ToggleLeftSig));
    
    leftTurnSignalEnabled = !leftTurnSignalEnabled;
}

void Lighting::toggle_headlights()
{
    // Send command
    if (!headlightsEnabled) {
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::HeadlightsOn)); // Command to activate headlights
    } else {
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::HeadlightsOff)); // Command to deactivate headlights
    }

    // Toggle
    headlightsEnabled = !headlightsEnabled;
}

void Lighting::cleanup()
{
    if (initialized) {
        enable_brake_lights(false);
        enable_av_status_led(false);
        enable_reverse_lights(false);
        if (rightTurnSignalEnabled) toggle_right_turn_signal();
        if (leftTurnSignalEnabled) toggle_left_turn_signal();
        if (headlightsEnabled) toggle_headlights();
        i2c_close(piHandle, lightingHandle);
        initialized = false;
    }
    else
        printf("WARNING: Tried closing lighting I2C connection without initialization\n");
}

Lighting::~Lighting()
{
    if (initialized)
        i2c_close(piHandle, lightingHandle);
}
