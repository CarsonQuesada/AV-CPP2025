#include "Speed.h"

#include <Arduino.h>
#include <util/atomic.h>
#include <math.h>      // for fabsf / fabs

#include "Utility.h"   // for clampi, PWM_MAX, etc.

// --- Speed Controller ---------------------------------- //
constexpr float speedDeadband_mmps = 30.0f;
constexpr float maxAccel_mmps2     = 150000.0f;

// --- Speed Estimator ----------------------------------- //
constexpr float WHEEL_CIRCUM_MM   = 600.0f;
constexpr int   ENC_TICKS_PER_REV = 2400;     // 600 PPR * 4 (quad) with belt
constexpr float MM_PER_TICK       = WHEEL_CIRCUM_MM / ENC_TICKS_PER_REV;
constexpr float LOW_PASS_ALPHA    = 0.10;

// =======================================================
// SpeedController
// =======================================================
SpeedController::SpeedController(float kp, float ki)
  : kp_(kp), ki_(ki), eIntegral_(0.0f) {}

void SpeedController::reset() {
  eIntegral_ = 0.0f;
}

int SpeedController::update(float target, float current, float dt_s) {
  if (dt_s <= 0.0f) return 0;

  // Reset integral when stopped
  if ((target == 0.0f) && (fabsf(current) < speedDeadband_mmps)) {
    eIntegral_ = 0.0f;
    return 0;
  }

  float error = target - current;

  // Acceleration limit
  float maxDelta = maxAccel_mmps2 * dt_s;
  error = clampf(error, -maxDelta, maxDelta);

  // PI output before saturation
  float pwmRaw = kp_ * error + ki_ * eIntegral_;

  // Saturate and convert to int
  int pwm = clampi(static_cast<int>(pwmRaw), -PWM_MAX, PWM_MAX);

  // Anti-windup: don't integrate when pinned and pushing further
  bool atMax = (pwm ==  PWM_MAX) && (error > 0.0f);
  bool atMin = (pwm == -PWM_MAX) && (error < 0.0f);

  if (!atMax && !atMin) {
    eIntegral_ += error * dt_s;
  }

  return pwm;
}

// =======================================================
// Motor
// =======================================================
Motor::Motor(uint8_t RPWM, uint8_t LPWM, uint8_t REN, uint8_t LEN)
  : RPWM_(RPWM), LPWM_(LPWM), REN_(REN), LEN_(LEN) {}

void Motor::begin() {
  pinMode(RPWM_, OUTPUT);
  pinMode(LPWM_, OUTPUT);
  pinMode(REN_,  OUTPUT);
  pinMode(LEN_,  OUTPUT);

  digitalWrite(REN_, LOW);
  digitalWrite(LEN_, LOW);
  analogWrite(RPWM_, 0);
  analogWrite(LPWM_, 0);
}

void Motor::update(int signed_pwm) {
  if (!enabled_) {
    // If you want: force outputs off when disabled
    analogWrite(RPWM_, 0);
    analogWrite(LPWM_, 0);
    digitalWrite(REN_, LOW);
    digitalWrite(LEN_, LOW);
    return;
  }

  int magnitude = abs(signed_pwm);
  if (signed_pwm == 0) {
    analogWrite(RPWM_, 0);
    analogWrite(LPWM_, 0);
    digitalWrite(REN_, LOW);
    digitalWrite(LEN_, LOW);
  } else if (signed_pwm > 0) {
    analogWrite(RPWM_, magnitude); // forward
    analogWrite(LPWM_, 0);
    digitalWrite(REN_, HIGH);
    digitalWrite(LEN_, HIGH);
  } else { // signed_pwm < 0
    analogWrite(RPWM_, 0);
    analogWrite(LPWM_, magnitude); // reverse
    digitalWrite(REN_, HIGH);
    digitalWrite(LEN_, HIGH);
  }
}

// =======================================================
// SpeedEstimator
// =======================================================

// static member definition
volatile long SpeedEstimator::tickCount_ = 0;

SpeedEstimator::SpeedEstimator(uint8_t encoderPinA, uint8_t encoderPinB)
  : encoderPinA_(encoderPinA), encoderPinB_(encoderPinB) {}

void SpeedEstimator::begin() {
  pinMode(encoderPinA_, INPUT_PULLUP);
  pinMode(encoderPinB_, INPUT_PULLUP);

  // Attach ISR on A's rising edge
  attachInterrupt(digitalPinToInterrupt(encoderPinA_),
                  SpeedEstimator::onEncoderA_ISR,
                  RISING);
}

float SpeedEstimator::update(float dt_s) {
  if (dt_s <= 0.0f) return currSpeed_mmps_;

  long currTicks;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    currTicks = tickCount_;
  }

  long deltaTicks = currTicks - lastTickCount_;
  lastTickCount_  = currTicks;

  float speed_mmps = (static_cast<float>(deltaTicks) * MM_PER_TICK) / dt_s;

  // TODO: optional low-pass filter here
  speed_mmps = (speed_mmps * LOW_PASS_ALPHA) + (1 - LOW_PASS_ALPHA) * currSpeed_mmps_;

  currSpeed_mmps_ = speed_mmps;
  return speed_mmps;
}

void SpeedEstimator::onEncoderA_ISR() {
  // Direction from B state on A's rising edge
  if (readEncoderB())
    tickCount_++;  // forward direction
  else
    tickCount_--;  // reverse direction
}
