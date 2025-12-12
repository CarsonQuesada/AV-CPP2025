#include "SteerController.h"

#include "Utility.h"

SteerController::SteerController(uint8_t RPWM, uint8_t LPWM, uint8_t EN, uint8_t FEEDBACK)
 : RPWM_(RPWM), LPWM_(LPWM), EN_(EN), FEEDBACK_(FEEDBACK) {}


void SteerController::begin() {
  pinMode(RPWM_, OUTPUT);
  pinMode(LPWM_, OUTPUT);
  pinMode(EN_, OUTPUT);
}

void SteerController::update(float dt_s) {
  // Get measured steering
  int adc  = analogRead(FEEDBACK_);
  currSteerPos_rad_ = adc2Rad(adc);

  // PI controller
  float error = target_ - currSteerPos_rad_;
  float u = error * kp_ + eIntegral_ * ki_;
  int pwm = clampi((int)u, -PWM_MAX, PWM_MAX);

  // Anti-windup: don't integrate when pinned and pushing further
  bool atMax = (pwm ==  PWM_MAX) && (error > 0.0f);
  bool atMin = (pwm == -PWM_MAX) && (error < 0.0f);

  if (!atMax && !atMin) {
    eIntegral_ += error * dt_s;
  }
 
  // Apply pwm
  int magnitude = abs(pwm);
  if (pwm == 0) {
    analogWrite(LPWM_, 0);
    analogWrite(RPWM_, 0);
    digitalWrite(EN_, LOW);
    return;
  } else if (pwm > 0) {
    analogWrite(LPWM_, magnitude); // positive -> steer left
    analogWrite(RPWM_, 0);
    digitalWrite(EN_, HIGH);
  } else {
    analogWrite(LPWM_, 0);
    analogWrite(RPWM_, magnitude); // negative -> steer right
    digitalWrite(EN_, HIGH);
  }
}

float SteerController::adc2Rad(int adc) {
  float normalizedAdc = (float(adc) - STEER_ADC_LEFT) / (STEER_ADC_RIGHT - STEER_ADC_LEFT);
  normalizedAdc = clampf(normalizedAdc, 0.0f, 1.0f);
  float angle = STEER_LEFT_RAD + (normalizedAdc * (STEER_RIGHT_RAD - STEER_LEFT_RAD));
  float adjustedAngle = angle - STEER_OFFSET_RAD;
  return clampf(adjustedAngle, STEER_MIN_RAD, STEER_MAX_RAD);
}
