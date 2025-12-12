#pragma once

#include <Arduino.h>

// ---------------- Steering calibration ----------------
constexpr float STEER_ADC_LEFT   = 421.0f;  // raw ADC at full-left
constexpr float STEER_ADC_RIGHT  = 112.0f;  // raw ADC at full-right
constexpr float STEER_OFFSET_RAD = -0.040f;  // if 0 rad isn't straight. May need tuning

// Mechanical steering limits in radians (left positive).
constexpr float STEER_LEFT_RAD   = +0.500f; // May need further measurments
constexpr float STEER_RIGHT_RAD  = -0.500f; // May need further measurments
constexpr float MARGIN_RAD       =  0.030f;
constexpr float STEER_MIN_RAD    =  (STEER_LEFT_RAD < STEER_RIGHT_RAD ? STEER_LEFT_RAD : STEER_RIGHT_RAD) + MARGIN_RAD;
constexpr float STEER_MAX_RAD    =  (STEER_LEFT_RAD > STEER_RIGHT_RAD ? STEER_LEFT_RAD : STEER_RIGHT_RAD) - MARGIN_RAD;

class SteerController {
public:
  SteerController(uint8_t RPWM, uint8_t LPWM, uint8_t EN, uint8_t FEEDBACK);

  inline void setTarget(float target) { target_ = target; }
  inline void setGain(float kp, float ki) { kp_ = kp; ki_ = ki; }
  inline float currSteerPos_rad() const { return currSteerPos_rad_; }

  void begin();
  void update(float dt_s);

private:
  float adc2Rad(int adc);

  uint8_t RPWM_, LPWM_, EN_, FEEDBACK_;
  float target_{0.0f};
  float kp_{0.0f}, ki_{0.0f};
  float eIntegral_;

  float currSteerPos_rad_{0.0f};
};
