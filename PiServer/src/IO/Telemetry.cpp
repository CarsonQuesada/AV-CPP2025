#include "Telemetry.h"

TelemetryData Telemetry::getData() {
    TelemetryData data;
    memset(&data, 0, sizeof(data)); // Clear in case of partial read

    int bytesRead = i2c_read_device(piHandle, telemetryHandle, (char*)&data, sizeof(data));

    if (bytesRead != sizeof(data)) {
        std::cerr << "Telemetry read error: expected " << sizeof(data)
                  << " bytes, got " << bytesRead << "\n";
        std::cout << "Reinitializing telemetry I2C handle...\n";

        i2c_close(piHandle, telemetryAddr);
        telemetryHandle = i2c_open(piHandle, 1, telemetryAddr, 0);
    }

    return data;
}

bool Telemetry::initialize()
{
    if(!initialized) {
        piHandle = Pigpio::getInstance().getHandle();
        telemetryHandle = i2c_open(piHandle, 1, telemetryAddr, 0);

        if (telemetryHandle < 0) {
            printf("Failed to init GPS (Telementary)!\n");
        } else {
            printf("> GPS (Telementary) subsystem \tINIT OK\n");
            initialized = true;
        }
    } else {
        printf("GPS already initialized\n");
    }
    return initialized;
}

void Telemetry::cleanup()
{
    if (initialized)
    {
        initialized = false;
        i2c_close(piHandle, telemetryHandle);
    }
    else
        printf("WARNING: Tried closing GPS I2C connection without initialization\n");
}

Telemetry::~Telemetry()
{
    if (initialized)
        i2c_close(piHandle, telemetryHandle);
}
