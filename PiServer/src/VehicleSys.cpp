#include "VehicleSys.h"

// #include <sys/socket.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <netdb.h>

//#include <sys/socket.h>

#include "Debug/Logger.h"
#include "IO/Pigpio.h"

void VehicleSys::disableVehicle()
{
    drive.enableSteering(false);  // enable steering

    // Disable motors and engage brakes for safety
	drive.enableMotors(false);
	brake();
}

void VehicleSys::enableVehicle()
{
    drive.enableSteering(true);  // enable steering

    // Disable motors and engage brakes for safety
	drive.enableMotors(true);
	relaxBrakes();
}

void VehicleSys::handleDisconnect()
{
    // Connected LED is set in TCPServer::waitForConnection()
    disableVehicle();
}

void VehicleSys::handleDriveInput(DriveCommand command)
{
    int currPos = adc.getSteeringFeedback();

    drive.accelerate(command.speed, command.gear);
    drive.steer(command.steer, currPos);
    brake(command.brake);
}

void VehicleSys::setMaxSpeed(SetMaxSpeedCommand command)
{
    std::scoped_lock lock(dataMutex);
    accelScalar = (float)command.maxSpeed / 100.0;
}

void VehicleSys::handleCameraInput(CameraCommand command)
{
    switch (command.cameraMove)
    {
        case CameraCmdID::CenterCamera:
            cameraServo.centerCamera();
            break;
        case CameraCmdID::PanCameraLeft:
            cameraServo.panCameraLeft();
            break;
        case CameraCmdID::PanCameraRight:
            cameraServo.panCameraRight();
            break;
        case CameraCmdID::NoInput:
            break;  // Should never happen
    }
}

void VehicleSys::handleLightsInput(LightsCommand command)
{
    std::scoped_lock lock(lightsMutex);
    switch (command.lightID)
    {
        case LightID::Headlights:
            // Toggle headlights
            lighting.setHeadlights(!lighting.isHeadlightsOn());
            break;
        case LightID::LeftTurnSig:
            // Toggle left turn signal
            lighting.setLeftSig(!lighting.isLeftSigOn());
            break;
        case LightID::RightTurnSig:
            // Toggle right turn signal
            lighting.setRightSig(!lighting.isRightSigOn());
            break;
        case LightID::NoInput:
            break;  // Should never happen
    }
    lightsStatusDirty.store(true);
}

void VehicleSys::setConnectStatusLED(ServerConnectionState state)
{
    std::scoped_lock lock(lightsMutex);
    lighting.setConnectLED(state);
}

LightsStatus VehicleSys::getLightsStatus()
{
    std::scoped_lock lock(lightsMutex);
    return {
        lighting.isBrakeLightsOn(),
        lighting.isReverseLightsOn(),
        lighting.isRightSigOn(),
        lighting.isLeftSigOn(),
        lighting.isHeadlightsOn(),
        lighting.isHazardsOn()
    };
}

GeneralStatus VehicleSys::getGeneralStatus()
{
    std::scoped_lock lock(dataMutex);
    uint32_t speedRaw;
    memcpy(&speedRaw, &telemetryData.speed, sizeof(float));
    uint32_t batteryRaw;
    memcpy(&batteryRaw, &batteryPercent, sizeof(float));
    return {
        speedRaw,
        batteryRaw,
        telemetryData.gpsOnline
    };
}

DriveStatus VehicleSys::getDriveStatus()
{
    return {
        drive.getGear(),
        drive.isBraking()
    };
}

void VehicleSys::statusUpdate()
{
    std::scoped_lock lock(dataMutex);
    telemetryData = telemetry.getData();
    std::cout << "Telemetry Data:" << std::endl;
    std::cout << "GPS status: " << telemetryData.gpsOnline << std::endl;
    std::cout << "Latidude:   " << telemetryData.lat << std::endl;
    std::cout << "Longitude:  " << telemetryData.lon << std::endl;
    std::cout << "Heading:    " << telemetryData.heading << std::endl;
    std::cout << "Speed:      " << telemetryData.speed << std::endl;
    std::cout << "Distance:   " << telemetryData.distanceDelta << std::endl;
    // In the future: battery percent, 
}

bool VehicleSys::initIO()
{
    bool status = true;	// Status flag to track initialization success
	
	// Initialize pigpio daemon. MUST BE DONE FIRST
	if (!Pigpio::getInstance().initialize())
        status = false;

	// Initialize I²C for the lighting subsystem
	if (!lighting.initialize())
        status = false;

	// Initialize SPI for the ADC (Analog-to-Digital Converter)
	if (!adc.initialize())
        status = false;

    // Initialize I²C for the telemetry subsystem
	if (!telemetry.initialize())
        status = false;   

	// Notify the user if any subsystem initialization failed
	if (status == false) {
        printf("[!!] One or more I/O devices failed to initialize!\n");
        printf("[!!] Try typing 'init pigpiod' before running program!\n");
	}
	
	// Configure GPIO for steering motor enable
    drive.initialize();

    cameraServo.initialize();

	// Return the overall initialization status
	return status;
}

void VehicleSys::shutdown()
{
    drive.cleanup();
    adc.cleanup();
    lighting.cleanup();
    telemetry.cleanup();
    Pigpio::getInstance().cleanup();    // MUST BE DONE LAST
}

void VehicleSys::relaxBrakes()
{
    std::scoped_lock lightsLock(lightsMutex);
    drive.relaxBrakes();
    lighting.setBrakeLights(false);
}

void VehicleSys::brake()
{
    std::scoped_lock lightsLock(lightsMutex);
    // Applies full brakes
    drive.brake();
    if (!lighting.isBrakeLightsOn()){
        // If brake lights are not on
        lighting.setBrakeLights(true);
        lightsStatusDirty.store(true);
    }
}

void VehicleSys::brake(int brakeVal)
{
    std::scoped_lock lightsLock(lightsMutex);
    drive.brake(brakeVal);
    if (brakeVal > brakeLightThresh) {
        if (!lighting.isBrakeLightsOn()) {
            // If brake lights are not on
            lighting.setBrakeLights(true);
            lightsStatusDirty.store(true);
        }
    } else {
        if (lighting.isBrakeLightsOn()) {
            // If brake lights are on
            lighting.setBrakeLights(false);
            lightsStatusDirty.store(true);
        }
    }
}

VehicleSys::~VehicleSys()
{
    shutdown();
}
