#include "VehicleControl.h"

#include <iostream>
#include <string>

#include "VehicleState.h"

std::optional<VehicleCommand> VehicleControl::genDriveCommand()
{
    VehicleCommand cmd;
    cmd.commandID = VehicleCommandID::Drive;

    // STEERING KEYS
	if (isDown(leftTurnKey))
        cmd.drive.steer = 100;		// left
    else if (isDown(rightTurnKey))
        cmd.drive.steer = 0;		// right
    else
        cmd.drive.steer = 50;		// center

    //	THROTTLE Keys
    if (isDown(reverseKey)) {
        cmd.drive.gear = GearID::Reverse;
        cmd.drive.speed = 100;
    } else if (isDown(forwardKey)) {
        cmd.drive.gear = GearID::Forward;
        cmd.drive.speed = 100;
    } else {
        cmd.drive.gear = GearID::Coast;
        cmd.drive.speed = 0;
    }

    // BRAKE KEYS
    if (isDown(brakeKey))
        cmd.drive.brake = 100;
    else
        cmd.drive.brake = 0;

    if (!vehicleState.autopilotActive) {
        // Autopilot inactive so send drive command
        return cmd;
    } else if (cmd.drive.brake || cmd.drive.speed || cmd.drive.steer) {
        // Autopilot active and driving input recieved. Override autopilot
        vehicleState.autopilotActive = false;
        return cmd;
    } else {
        // Autopilot active and no input recieved
        return std::nullopt;
    }
}

std::optional<VehicleCommand> VehicleControl::genLightsCommand()
{
    VehicleCommand cmd;
    cmd.commandID = VehicleCommandID::ToggleLights;

    if (isDown(rightSigKey)) // signal right
		cmd.lights.lightID = LightID::RightTurnSig;
	else if (isDown(leftSigKey)) // signal left
        cmd.lights.lightID = LightID::LeftTurnSig;
	else if (isDown(headlightKey)) // headlights
        cmd.lights.lightID = LightID::Headlights;
    else
        return std::nullopt;

    return cmd;
}

std::optional<VehicleCommand> VehicleControl::genCameraCommand()
{
    VehicleCommand cmd;
    cmd.commandID = VehicleCommandID::MoveCamera;

    if (isDown(panCamLeftKey)) // pan camera left
        cmd.camera.cameraMove = CameraCmdID::PanCameraLeft;
    else if (isDown(panCamRightKey)) // pan camera right
        cmd.camera.cameraMove = CameraCmdID::PanCameraRight;
    else if (isDown(CenterCamKey)) // camera center
        cmd.camera.cameraMove = CameraCmdID::CenterCamera;
    else
        return std::nullopt;

    return cmd;
}

std::optional<VehicleCommand> VehicleControl::genMaxSpeedCommand()
{
    VehicleCommand cmd;
    cmd.commandID = VehicleCommandID::SetMaxSpeed;

    std::string maxSpeed;
    int speed;
    bool invalidInput = true;
    while (invalidInput)
    {
        std::cout << "Set Max Speed (Speed range: 1-100, enter 'X' to escape): ";
        std::cin >> maxSpeed;
        if (maxSpeed.c_str()[0] == 'X')
            return std::nullopt;

        speed = std::stoi(maxSpeed);
        if (0 < speed && speed <= 100)
            invalidInput = false;
        else
            std::cout << "Invalid input. Try again." << std::endl;
    }
    cmd.setMaxSpeed.maxSpeed = speed;
    return cmd;
}

std::optional<VehicleCommand> VehicleControl::genAutopilotCommand()
{
    static AutopilotCommandID prevPress = AutopilotCommandID::Invalid;

    VehicleCommand cmd;
    cmd.commandID = VehicleCommandID::Autopilot;

    bool curInput;
    if (isDown(toggleAutopilotKey)) {
        if (prevPress != AutopilotCommandID::Start && prevPress != AutopilotCommandID::Stop) {
            // Toggle autopilot is pressed and user was not previosly pressing it
            vehicleState.autopilotActive  = !vehicleState.autopilotActive;    // toggle autopilot
            if (vehicleState.autopilotActive) {
                cmd.autopilot.autopilotCmd = AutopilotCommandID::Start;
                prevPress = AutopilotCommandID::Start;
            } else {
                cmd.autopilot.autopilotCmd = AutopilotCommandID::Stop;
                prevPress = AutopilotCommandID::Stop;
            }

            return cmd;
        } else {
            return std::nullopt;
        }
    } else {
        prevPress = AutopilotCommandID::Invalid;
        return std::nullopt;
    }
}

std::optional<VehicleCommand> VehicleControl::genStopCommand()
{
    if (!vehicleState.autopilotActive) {
        VehicleCommand cmd;
        cmd.commandID = VehicleCommandID::Drive;
        cmd.drive.speed = 0;
        cmd.drive.gear = GearID::Coast;
        cmd.drive.steer = 0;
        cmd.drive.brake = 100;
        return  cmd;
    } else {
        return std::nullopt;
    }
}
