#include "Lighting.h"

void Lighting::setBrakeLights(bool en)
{
    if (en)
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::BrakeLightsOn));
    else
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::BrakeLightsOff));

    brakeLightsEnabled.store(en);
}

void Lighting::setReverseLights(bool en)
{
    // Check to see if enable will change light's state. If not do nothing
    if (en) {
        // Uncomment and replace `6` with the correct I²C command for activating reverse lights
		//i2c_write_byte(piHandle, lightingHandle, 6);
    } else {
        // Uncomment and replace `7` with the correct I²C command for deactivating reverse lights
		//i2c_write_byte(piHandle, lightingHandle, 7);
    }

    reverseLightsEnabled.store(en);
}

void Lighting::setRightSig(bool en)
{
    // If right turn signal toggle off
    if (en) {
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::RightSigOff));
        if (leftSigEnabled.load()) {
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::LeftSigOff));
            leftSigEnabled.store(false);
        }
    } else {
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::RightSigOn));
    }

    rightSigEnabled.store(en);
}

void Lighting::setLeftSig(bool en)
{
    if (en) {
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::LeftSigOff));
        if (rightSigEnabled.load()) {
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::RightSigOff));
            rightSigEnabled.store(false);
        }
    } else {
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::LeftSigOn));
    }

    leftSigEnabled.store(en);
}

void Lighting::setHeadlights(bool en)
{
    // Send command
    if (en)
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::HeadlightsOff));
    else
        i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::HeadlightsOn));

    headlightsEnabled.store(en);
}

void Lighting::setConnectLED(ConnectionStatus status)
{
    // Check to see if enable will change light's state. If not do nothing
    switch (status)
    {
        case ConnectionStatus::Disabled:
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::StopConnecting));
            break;
        case ConnectionStatus::Connected:
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::Connected));
            break;
        case ConnectionStatus::Reconnecting:
            i2c_write_byte(piHandle, lightingHandle, static_cast<int>(LightingCommand::Reconnecting));
            break;
        default:
            std::cout << "Setting ConnectLED to unknown status. Status: " << static_cast<int>(status) << std::endl;
            break;
    }

    connectLEDStatus.store(status);
}

bool Lighting::initialize()
{
    if(!initialized) {
        piHandle = Pigpio::getInstance().getHandle();
        lightingHandle = i2c_open(piHandle, 1, lightingAddr, 0);

        if (lightingHandle < 0) {
            printf("[!] Failed to init lidar!\n");
        } else {
            printf("> lighting subsystem \t\tINIT OK\n");
            setBrakeLights(false);
            initialized = true;
        }
    } else {
        printf("Lighting already initialized\n");
    }

    return initialized;
}

void Lighting::cleanup()
{
    if (initialized) {
        setBrakeLights(false);
        setReverseLights(false);
        setRightSig(false);
        setLeftSig(false);
        setHeadlights(false);
        setConnectLED(ConnectionStatus::Disabled);

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