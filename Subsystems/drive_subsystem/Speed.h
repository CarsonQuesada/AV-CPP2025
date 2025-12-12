#pragma once

#include <Arduino.h>

// ------------ Motor ------------ //
class Motor {
public:
  Motor(uint8_t RPWM, uint8_t LPWM, uint8_t REN, uint8_t LEN);

  inline void setEnable(bool en) { enabled_ = en; }

  void begin();
  void update(int signedPwm);

private:
  uint8_t RPWM_, LPWM_, REN_, LEN_;
  bool    enabled_ = false;
};

// ------------ Speed Controller ------------ //
class SpeedController {
public:
  SpeedController(float kp, float ki);

  // returns PWM in [-PWM_MAX, PWM_MAX]
  int update(float target_mmps, float current_mmps, float dt_s);

  void reset();

private:
  float kp_;
  float ki_;
  float eIntegral_;
};

// ------------ Speed Estimator ------------ //
class SpeedEstimator {
public:
  SpeedEstimator(uint8_t encoderPinA, uint8_t encoderPinB);

  void  begin();
  float update(float dt_s);   // dt in seconds
  inline float currSpeed_mmps() const { return currSpeed_mmps_; }

private:
  // ISR trampoline
  static void onEncoderA_ISR();

  // Direct port read for encoder B (PD4) – adjust if needed
  static inline bool readEncoderB() {
    return (PIND & _BV(PD4)) != 0; // true if HIGH
  }

  uint8_t encoderPinA_;
  uint8_t encoderPinB_;

  // shared tick count updated from ISR
  static volatile long tickCount_;

  long  lastTickCount_    = 0;
  float currSpeed_mmps_   = 0.0f;
};
