#include "VehicleController.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "VehicleState.h"

void VehicleController::updateUIButton(ButtonID id, bool pressed) 
{
    buttonInputs[static_cast<int>(id)].update(pressed);
}

void VehicleController::updateUISliderInt(SliderID id, int value) 
{
    slidersInt[static_cast<int>(id)].update(value);
}

void VehicleController::pollKeyboardInput()
{
    // STEERING KEYS
    button(ButtonID::Left).update(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
    button(ButtonID::Right).update(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

    //THROTTLE KEYS
    button(ButtonID::Forward).update(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
    button(ButtonID::Reverse).update(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);

    // BRAKE KEY
    button(ButtonID::Brake).update(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);

    // LIGHT KEYS
    button(ButtonID::LeftTurnSig).update(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
    button(ButtonID::RightTurnSig).update(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS);
    button(ButtonID::Headlights).update(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS);

    // CAMERA KEYS
    button(ButtonID::PanCameraLeft).update(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS);
    button(ButtonID::PanCameraRight).update(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS);
    button(ButtonID::CenterCamera).update(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS);
}

std::vector<Message> VehicleController::generateCommands(bool connected, bool autopilotOn)
{
    std::vector<Message> msgs;
    Message msg;

    // DRIVE COMMAND
    if (connected) {
        DriveCommand drive;
        // Steer
        if (button(ButtonID::Left).pressed)
            drive.steer = 100;		// left
        else if (button(ButtonID::Right).pressed)
            drive.steer = 0;		// right
        else
            drive.steer = 50;		// center

        //	Throttle
        if (button(ButtonID::Forward).pressed) {
            drive.gear = GearID::Forward;
            drive.speed = 100;
        } else if (button(ButtonID::Reverse).pressed) {
            drive.gear = GearID::Reverse;
            drive.speed = 100;
        } else {
            drive.gear = GearID::Coast;
            drive.speed = 0;
        }

        // Brake
        if (button(ButtonID::Brake).pressed)
            drive.brake = 100;
        else
            drive.brake = 0;

        // Decide if drive command should be sent
        if (!VehicleState::getInstance().autopilotActive) {
            // Autopilot inactive so send drive command
            msgs.push_back(makeMessageFrom(drive));
        } else if (drive.brake || drive.speed || (drive.steer != 50)) {
            // Autopilot active and driving input recieved. send command to override autopilot
            msgs.push_back(makeMessageFrom(drive));
        }
    }

    // LIGHT COMMANDS
    LightsCommand lights;
    if (button(ButtonID::RightTurnSig).isPressedEdge()) { // signal right
		lights.lightID = LightID::RightTurnSig;
        msgs.push_back(makeMessageFrom(lights));
    }
	if (button(ButtonID::LeftTurnSig).isPressedEdge()) { // signal left
        lights.lightID = LightID::LeftTurnSig;
        msgs.push_back(makeMessageFrom(lights));
    }
	if (button(ButtonID::Headlights).isPressedEdge()) { // headlights
        lights.lightID = LightID::Headlights;
        msgs.push_back(makeMessageFrom(lights));
    }

    // CAMERA COMMAND
    if (connected && autopilotOn) {
        CameraCommand camera;
        if (button(ButtonID::PanCameraLeft).pressed) { // pan camera left
            camera.cameraMove = CameraCmdID::PanCameraLeft;
        } else if (button(ButtonID::PanCameraRight).pressed) { // pan camera right
            camera.cameraMove = CameraCmdID::PanCameraRight;
        } else if (button(ButtonID::CenterCamera).pressed) { // camera center
            camera.cameraMove = CameraCmdID::CenterCamera;
        }
        msgs.push_back(makeMessageFrom(camera));
    }

    // SET MAX SPEED COMMAND
    if (connected) {
        SetMaxSpeedCommand setMaxSpeed;
        if (slider(SliderID::MaxSpeed).changed()) {
            setMaxSpeed.maxSpeed = slider(SliderID::MaxSpeed).value;
            msgs.push_back(makeMessageFrom(setMaxSpeed));
        }
    }

    // TOGGLE AUTOPILOT COMMAND
    if (button(ButtonID::ToggleAutopilot).isPressedEdge()) {
        if (VehicleState::getInstance().autopilotActive) {
            StopAutopilotCommand stopAutopilot;
            msgs.push_back(makeMessageFrom(stopAutopilot));
        } else {
            StartAutopilotCommand startAutopilot;
            msgs.push_back(makeMessageFrom(startAutopilot));
        }
    }

    return msgs;
}
