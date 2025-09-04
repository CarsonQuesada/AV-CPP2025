#pragma once

#include <GLFW/glfw3.h>
#include <optional>
#include <string>
#include <vector>
#include <array>
#include <chrono>

#include "Shared/Message.h"
#include "VehicleState.h"

// Button used for both keys and UI buttons
enum class ButtonID {
    Left,
    Right,
    Forward,
    Reverse,
    Brake,
    LeftTurnSig,
    RightTurnSig,
    Headlights,
    PanCameraLeft,
    PanCameraRight,
    CenterCamera,
    ToggleAutopilot,
    Count // MUST BE AT END
};

enum class SliderID {
    MaxSpeed,
    Count // MUST BE AT END
};

namespace std {
    template <>
    struct hash<ButtonID> {
        std::size_t operator()(const ButtonID& id) const {
            return static_cast<std::size_t>(id);
        }
    };

    template <>
    struct hash<SliderID> {
        std::size_t operator()(const SliderID& id) const {
            return static_cast<std::size_t>(id);
        }
    };
}

struct ButtonState {
    bool pressed = false;
    bool prevPress = false;
    inline bool isPressedEdge() const { return pressed && !prevPress; }
    inline void update(bool newState) {
        prevPress = pressed;
        pressed = newState;
    }
};

struct SliderInputInt {
    int value = 0;
    int prevValue = 0;
    inline bool changed() const { return value != prevValue; }
    inline void update(int newValue) {
        prevValue = value;
        value = newValue;
    }
};

class VehicleController
{
public:
    VehicleController(GLFWwindow* window) : window(window) {}
    ~VehicleController() = default;

    // UI Input
    void updateUIButton(ButtonID, bool pressed);
    void updateUISliderInt(SliderID, int value);

    // Keyborad Input
    void pollKeyboardInput();

    std::vector<Message> generateCommands(bool connected, bool autopilotOn);

private:
    GLFWwindow* window;
    std::chrono::steady_clock::time_point lastSendTime = std::chrono::steady_clock::now();

    std::array<ButtonState, static_cast<size_t>(ButtonID::Count)> buttonInputs;
    std::array<SliderInputInt, static_cast<size_t>(SliderID::Count)> slidersInt;

    inline ButtonState& button(ButtonID id) {
        return buttonInputs[static_cast<size_t>(id)];
    }
    inline SliderInputInt& slider(SliderID id) {
        return slidersInt[static_cast<size_t>(id)];
    }
};