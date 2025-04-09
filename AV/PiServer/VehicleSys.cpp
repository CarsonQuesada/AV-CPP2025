#include "VehicleSys.h"

#include "Debug/Logger.h"

VehicleSys::VehicleSys()
    : pi(Pigpio::get_instance()), lighting(Lighting::get_instance()), adc(ADC::get_instance()),
      lidarSP(LidarSP::get_instance()), 
      gps(GPS::get_instance()), drive(Drive::get_instance()), cameraServo(CameraServo::get_instance())
{
}

VehicleSys::~VehicleSys()
{
    VehicleSys::shutdown();
}

bool VehicleSys::init_io()
{
    bool status = true;	// Status flag to track initialization success
	
	// Initialize pigpio daemon. MUST BE DONE FIRST
	if (!pi.initialize())
        status = false;

	// Initialize I²C for the lighting subsystem
	if (!lighting.initialize())
        status = false;

	// Initialize SPI for the ADC (Analog-to-Digital Converter)
	if (!adc.initialize())
        status = false;

	// Initialize I²C for the lidar subsystem
	if (!lidarSP.initialize())
        status = false;

	// Initialize I²C for the GPS subsystem
	if (!gps.initialize())
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
    enable_vehicle(false);
    Drive::get_instance().cleanup();
    GPS::get_instance().cleanup();
    LidarSP::get_instance().cleanup();
    SerialPort::get_instance().cleanup();
    ADC::get_instance().cleanup();
    Lighting::get_instance().cleanup();
    Pigpio::get_instance().cleanup();
}

void VehicleSys::enable_vehicle(bool en)
{
    drive.enable_steering(true);  // enable steering
    // Disable motors and engage brakes for safety
	drive.enable_motors(false);
	drive.brake();
}

void VehicleSys::handle_other_input(OtherInput controlInput)
{
    switch (controlInput)
    {
        case OtherInput::NoInput:
            // Handle no input
            break;
        case OtherInput::LeftTurnSig:
            if (prevControlInput != controlInput)
                lighting.toggle_left_turn_signal();
            break;
        case OtherInput::RightTurnSig:
            if (prevControlInput != controlInput)
                lighting.toggle_right_turn_signal();
            break;
        case OtherInput::Headlights:
            if (prevControlInput != controlInput)
                lighting.toggle_headlights();
            break;
        case OtherInput::ResetMaxSpeed:
            // Nothing yet
            break;
        default:
            std::cout << "WARNING: Unkown command for control input: " << static_cast<int>(controlInput) << std::endl;
    }
    // Update previous control input
    prevControlInput = controlInput;
}

void VehicleSys::handle_camera_input(CameraCommand cameraCommand)
{
    switch (cameraCommand)
    {
        case CameraCommand::NoInput:
            break;
        case CameraCommand::CenterCamera:
            cameraServo.center_camera();
            break;
        case CameraCommand::PanCameraLeft:
            cameraServo.pan_camera_left();
            break;
        case CameraCommand::PanCameraRight:
            cameraServo.pan_camera_right();
            break;
    }
}
