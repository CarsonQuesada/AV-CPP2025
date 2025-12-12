#pragma once
#include <Servo.h>
#include "Utility.h"

class Brakes {
public:
  Brakes(uint8_t brakePin) : brakePin_(brakePin) {}


  void begin() {
    brakeServo.attach(brakePin_, brakeServoRelaxed, brakeServoFull);
    brakeServo.writeMicroseconds(brakeServoRelaxed);
    // Raise Timer2 PWM (pins 3 & 11) to ~31 kHz to eliminate audible whine
    TCCR2B = (TCCR2B & 0b11111000) | 0x01;
  }


  void applyBrakes(int val) {
    int brake = lerpi(val, 0, 100, brakeServoRelaxed, brakeServoFull);
    brake = clampi(brake, brakeServoRelaxed, brakeServoFull);
    brakeServo.writeMicroseconds(brake);
  }


private:
  static constexpr int brakeServoRelaxed = 2050;
  static constexpr int brakeServoFull    = 2250;


  uint8_t brakePin_;
  Servo   brakeServo;
};