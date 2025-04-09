#pragma once

#include "Shared/UserInputTypes.h"

constexpr int bufferSize = 512;
constexpr int preParseBuffSize = 18;

struct UserInput
{
    Gear gear;
    int steerValue;
    int accelValue;
    int brakeValue;
    CameraCommand cameraCommand;
    bool toggleAV;
    OtherInput otherInput;
};

class UserInputBuff
{
public:
    UserInputBuff() {};
    inline char* expose_buffer() { return buffer; }
    void clear_buffer();
    UserInput parse_control_data();
private:
    char buffer[bufferSize];
    char preParseBuff[preParseBuffSize];
};
