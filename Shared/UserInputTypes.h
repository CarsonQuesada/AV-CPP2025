#pragma once
enum class Gear 
{
    NoInput = 0, Coast, Forward, Reverse
};

enum class CameraCommand
{
    NoInput = 0, PanCameraLeft, CenterCamera, PanCameraRight
};

enum class OtherInput
{
    NoInput = 0, LeftTurnSig, RightTurnSig, Headlights, ResetMaxSpeed
};