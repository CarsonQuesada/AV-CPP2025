#include <Wire.h>

#define I2C_SLAVE_ADDRESS 6 // Set the Arduino's I2C address

// This enum is also used in PiServer/IO/Lighting.h
// Any change to this one should be made to the other and vice versa
enum class LightingCommand
{
  Unkown = 0, HeadlightsOn, HeadlightsOff, ToggleLeftSig, ToggleRightSig,
  ToggleHazards, BrakeLightsOn, BrakeLightsOff, AVLightOn, AVLightOff
};

// Define pins for controlling the lights
const int headlightsPin = 2;
const int leftTurnSignalPin = 3;
const int rightTurnSignalPin = 4;
const int brakeLightsPin = 5;
const int avLightsPin = 6;

LightingCommand receivedAction = LightingCommand::Unkown; // Variable to store the received action
bool blinkLeftSignal = false;
bool blinkRightSignal = false;
bool activateHazards = false;

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  // Initialize pins as outputs
  pinMode(headlightsPin, OUTPUT);
  pinMode(leftTurnSignalPin, OUTPUT);
  pinMode(rightTurnSignalPin, OUTPUT);
  pinMode(brakeLightsPin, OUTPUT);
  pinMode(avLightsPin, OUTPUT);

  // Turn off all lights initially
  turnOffLights();
}

void loop() {
if (activateHazards) {
    // Toggle both left and right turn signals for hazard lights
    digitalWrite(leftTurnSignalPin, !digitalRead(leftTurnSignalPin));
    digitalWrite(rightTurnSignalPin, !digitalRead(rightTurnSignalPin));
    delay(400);  // Control the blink rate of hazard lights
  } else {
    // Handle left turn signal
    if (blinkLeftSignal) {
      digitalWrite(leftTurnSignalPin, !digitalRead(leftTurnSignalPin));
      delay(400);
    } else{
      digitalWrite(leftTurnSignalPin, LOW);
    }
  
    // Handle right turn signal
    if (blinkRightSignal) {
      digitalWrite(rightTurnSignalPin, !digitalRead(rightTurnSignalPin));
      delay(400);
    } else {
      digitalWrite(rightTurnSignalPin, LOW);
    }
  }
}

void receiveEvent(int byteCount) {
  if (byteCount == 1) {  // Expecting a single byte for the action
      int receivedValue = Wire.read();

    if (receivedValue < static_cast<int>(LightingCommand::Unkown) || receivedValue > static_cast<int>(LightingCommand::AVLightOff)) {
      receivedAction = LightingCommand::Unkown;  // Handle invalid input
    } else {
      receivedAction = static_cast<LightingCommand>(receivedValue);
    }

    // Process the received action
    switch (receivedAction) {
      case LightingCommand::HeadlightsOn:  // Turn on headlights
        digitalWrite(headlightsPin, HIGH);
        break;
      case LightingCommand::HeadlightsOff:  // Turn off headlights
        digitalWrite(headlightsPin, LOW);
        break;
      case LightingCommand::ToggleLeftSig:  // Toggle left turn signal
        blinkLeftSignal = !blinkLeftSignal;
        break;
      case LightingCommand::ToggleRightSig:  // toggle right turn signal
        blinkRightSignal = !blinkRightSignal;
        break;
      case LightingCommand::ToggleHazards:  // Toggle hazard lights
        activateHazards = !activateHazards;
        break;
      case LightingCommand::BrakeLightsOn:  // Apply brake lights
        digitalWrite(brakeLightsPin, HIGH);
        break;
      case LightingCommand::BrakeLightsOff:  // Release brake lights
        digitalWrite(brakeLightsPin, LOW);
        break;
      case LightingCommand::AVLightOn:  // Turn on AV light
        digitalWrite(avLightsPin, HIGH);
        break;
      case LightingCommand::AVLightOff:  // Turn off AV light
        digitalWrite(avLightsPin, LOW);
        break;
      default:
        // Handle unknown action or add custom cases as needed
        break;
    }
  }
}

void turnOffLights() {
  digitalWrite(headlightsPin, LOW);
  digitalWrite(leftTurnSignalPin, LOW);
  digitalWrite(rightTurnSignalPin, LOW);
  digitalWrite(brakeLightsPin, LOW);
  digitalWrite(CVlightsPin, LOW);
}
