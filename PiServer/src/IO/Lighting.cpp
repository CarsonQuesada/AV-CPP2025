#include "Lighting.h"

void Lighting::setBrakeLights(bool en)
{
    if (en)
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::BrakeLightsOn));
    else
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::BrakeLightsOff));

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
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::RightSigOn));
        if (leftSigEnabled.load()) {
            i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::LeftSigOff));
            leftSigEnabled.store(false);
        }
    } else {
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::RightSigOff));
    }

    rightSigEnabled.store(en);
}

void Lighting::setLeftSig(bool en)
{
    if (en) {
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::LeftSigOn));
        if (rightSigEnabled.load()) {
            i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::RightSigOff));
            rightSigEnabled.store(false);
        }
    } else {
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::LeftSigOff));
    }

    leftSigEnabled.store(en);
}

void Lighting::setHeadlights(bool en)
{
    if (en)
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::HeadlightsOn));
    else
        i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::HeadlightsOff));

    headlightsEnabled.store(en);
}

void Lighting::setConnectLED(ServerConnectionState state)
{
    // Check to see if enable will change light's state. If not do nothing
    switch (state)
    {
        case ServerConnectionState::Disconnected:
            i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::StopConnecting));
            break;
        case ServerConnectionState::Connected:
            i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::Connected));
            break;
        case ServerConnectionState::Listening:
            i2c_write_byte(piHandle, lightingHandle, static_cast<uint8_t>(LightingCommand::Reconnecting));
            break;
        default:
            std::cout << "Setting ConnectLED to unknown status. Status: " << static_cast<uint8_t>(state) << std::endl;
            break;
    }

    connectLEDStatus.store(state);
}

bool Lighting::initialize()
{
    if(!initialized) {
        piHandle = Pigpio::getInstance().getHandle();
        lightingHandle = i2c_open(piHandle, 1, lightingAddr, 0);

        if (lightingHandle < 0) {
            printf("[!] Failed to init Lighting!\n");
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
        setConnectLED(ServerConnectionState::Disconnected);

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