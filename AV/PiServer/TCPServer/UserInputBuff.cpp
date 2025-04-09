#include "UserInputBuff.h"

#include <sstream>
#include <cstring>

#include "Debug/Logger.h"


void UserInputBuff::clear_buffer()
{
    std::memset(buffer, 0, sizeof(buffer)); // clear receive buffer
}

UserInput UserInputBuff::parse_control_data()
{
    UserInput userInput = UserInput();
    char gearChar;

    memcpy(preParseBuff, buffer, preParseBuffSize);

    // Begin Parsing. String format "%1c-%3d-%3d-%3d-%1d-%1d-%1d", gear, steer, accel, brake, cam, avTog, other
    char* token;
    // parse forward / reverse
    token = strtok(buffer, "-");
    gearChar = token[0];
    switch (gearChar)	
    {
        case 'C':
            userInput.gear = Gear::Coast;
            break;
        case 'F':
            userInput.gear = Gear::Forward;
            break;
        case 'R':
            userInput.gear = Gear::Reverse;
            break;
        default:
            LOG(LogLevel::ERROR, "ERROR: Invalid input for gear: %c\n", gearChar);
            break;
    }
    // parse steering
    token = strtok(NULL, "-");
    userInput.steerValue = atoi(token);
    // parse acceleration
    token = strtok(NULL, "-");
    userInput.accelValue = atoi(token);
    // parse braking
    token = strtok(NULL, "-");
    userInput.brakeValue = atoi(token);
    // parse camera command
    token = strtok(NULL, "-");
    userInput.cameraCommand = static_cast<CameraCommand>(atoi(token));
    // parse av toggle
    token = strtok(NULL, "-");
    userInput.toggleAV = atoi(token);
    // parse other input
    token = strtok(NULL, "-");
    userInput.otherInput = static_cast<OtherInput>(atoi(token));

    // Display Data
    printf("Gear: %c\n", gearChar);
    printf("Steering: %i\n", userInput.steerValue);
    printf("Acceleration: %i\n", userInput.accelValue);
    printf("Braking: %i\n", userInput.brakeValue);
    printf("Camera Command: %i\n", userInput.cameraCommand);
    printf("Autopilot toggle key is %s being pressed\n", userInput.toggleAV ? "" : "NOT");
    printf("Other control input: %i\n", userInput.otherInput);

    return userInput;
}
