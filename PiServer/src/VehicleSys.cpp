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
	drive.brake();
}

void VehicleSys::enableVehicle()
{
    drive.enableSteering(true);  // enable steering

    // Disable motors and engage brakes for safety
	drive.enableMotors(true);
	drive.relaxBrakes();
}

void VehicleSys::handleDisconnect()
{
    // Connected LED is set in TCPServer::waitForConnection()
    disableVehicle();
}

void VehicleSys::handleDriveInput(DriveVCommand command)
{
    int currPos = adc.getSteeringFeedback();
    printf("Actual steering position: %d\n", currPos);

    drive.accelerate(command.speed, command.gear);
    drive.brake(command.brake);
    drive.steer(command.steer, currPos);
    std::cout << "Set speed to: " << static_cast<int>(command.speed) << std::endl;
    std::cout << "Set gear to: " << static_cast<int>(command.gear) << std::endl;
    std::cout << "Set steer to: " << static_cast<int>(command.steer) << std::endl;

    if (drive.isMotorsEnabled())
        std::cout << "Motors Enabled" << std::endl;
    else
        std::cout << "Motors NOT Enabled" << std::endl;

    if (drive.isBraking())
        std::cout << "Braking" << std::endl;
    else
        std::cout << "NOT Braking" << std::endl;

    if (command.brake > brakeLightThresh)
        lighting.setBrakeLights(true);
    else
        lighting.setBrakeLights(false);
}

void VehicleSys::handleDriveInput(DriveAFeedback command)
{
    int currPos = adc.getSteeringFeedback();
    printf("Actual steering position: %d\n", currPos);

    adc.getSteeringFeedback();
    drive.accelerate(command.drive.speed, command.drive.gear);
    drive.brake(command.drive.brake);
    drive.steer(command.drive.steer, currPos);

    if (command.drive.brake > brakeLightThresh)
        lighting.setBrakeLights(true);
    else
        lighting.setBrakeLights(false);
}

void VehicleSys::setMaxSpeed(SetMaxSpeedVCommand command)
{
    accelScalar = (float)command.maxSpeed / 100.0;
}

void VehicleSys::handleCameraInput(CameraVCommand command)
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

void VehicleSys::handleLightsInput(LightsVCommand command)
{
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
}

void VehicleSys::setConnectionStatus(ConnectionStatus status)
{
    connectionStatus.store(status);
    lighting.setConnectLED(status);
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
    Pigpio::getInstance().cleanup();    // MUST BE DONE LAST
}

VehicleSys::~VehicleSys()
{
    shutdown();
}
