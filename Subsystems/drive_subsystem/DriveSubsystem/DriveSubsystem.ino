/*
 * Kart Drive & Steering Controller (I2C target) — modular version
 * Board: Arduino Uno/Nano (ATmega328P) or similar
 */

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include "Utility.h"
#include "Speed.h"
#include "SteerController.h"
#include "Brakes.h"
#include "I2CInterface.h"

// ---------------- Pin Assignments ----------------
constexpr uint8_t DRIVE_RPWM = 5;   // PWM (OK with Servo library; not Timer1)
constexpr uint8_t DRIVE_LPWM = 6;   // PWM (OK with Servo library; not Timer1)
constexpr uint8_t DRIVE_R_EN = 7;   // digital
constexpr uint8_t DRIVE_L_EN = 8;   // digital

constexpr uint8_t STEER_RPWM = 3;   // PWM (Timer2)
constexpr uint8_t STEER_LPWM = 11;  // PWM (Timer2)
constexpr uint8_t STEER_EN   = 13;  // digital

constexpr uint8_t BRAKE_SERVO_PIN    = 9;   // Servo signal (Timer1 pin)
constexpr uint8_t STEER_FEEDBACK_PIN = A0;  // analog

// Quadrature encoder pins (A on INT0/D2, B on D4)
constexpr uint8_t ENC_A_PIN = 2; // INT0
constexpr uint8_t ENC_B_PIN = 4; // D4 (read in ISR inside SpeedEstimator)

// ---------------- I2C Settings ----------------
constexpr uint8_t I2C_ADDRESS = 0x20;

// DriveCommand / DriveStatus are defined in I2CInterface.h

// ---------------- Control timing ----------------
constexpr float CONTROL_HZ = 100.0f;             // target control rate
constexpr float CONTROL_DT_S = 1.0f / CONTROL_HZ;

// ---------------- Watchdog & Faults ----------------
constexpr uint16_t WATCHDOG_TIMEOUT_MS = 200; // if no valid cmd in time -> fault

enum FaultBits : uint16_t {
  FAULT_WATCHDOG = 1 << 0,
  FAULT_ESTOP    = 1 << 1,
  FAULT_OVERCURR = 1 << 2
};

volatile uint16_t fault_bits = 0;

// ---------------- Subsystem objects ----------------
Motor           motor(DRIVE_RPWM, DRIVE_LPWM, DRIVE_R_EN, DRIVE_L_EN);
SpeedController speedCtrl(0.15f, 1.0f);                // TODO: tune Kp/Ki
SpeedEstimator  speedEst(ENC_A_PIN, ENC_B_PIN);

SteerController steer(STEER_RPWM, STEER_LPWM, STEER_EN, STEER_FEEDBACK_PIN);
Brakes          brakes(BRAKE_SERVO_PIN);
I2CInterface    i2c(I2C_ADDRESS);

// ---------------- Latched command state ----------------
bool     g_haveCommand       = false;
bool     g_enable            = false;
bool     g_estop             = false;
bool     g_reverseAllowed    = false;
uint8_t  g_brake_percent     = 0;
float    g_targetSpeed_mmps  = 0.0f;
float    g_targetSteer_rad   = 0.0f;

// status / telemetry
float    g_measuredSpeed_mmps = 0.0f;

// timing
unsigned long last_command_ms  = 0;
unsigned long last_loop_us     = 0;
unsigned long last_print_ms    = 0;

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);

  // Speed
  motor.begin();
  motor.setEnable(false);   // start disabled
  speedEst.begin();

  // Steering
  steer.begin();
  steer.setGain(800.0f, 1000.0f);    // rough starting point; tune
  steer.setTarget(0.0f);

  // Brakes
  brakes.begin();

  // I2C
  i2c.begin();

  // Initial timing
  last_command_ms = millis();
  last_loop_us    = micros();

  Serial.println("Kart controller starting up...");
}

// ---------------- Main Loop ----------------
void loop() {
  unsigned long now_ms = millis();
  unsigned long now_us = micros();

  // Compute dt (seconds) from last loop
  float dt_s = (now_us - last_loop_us) / 1e6f;
  if (dt_s <= 0.0f || dt_s > 0.1f) {
    // guard against micros wrap or long pauses
    dt_s = CONTROL_DT_S;
  }
  last_loop_us = now_us;

  // ---------- 1. Handle I2C command updates ----------
  if (i2c.hasNewCommand()) {
    DriveCommand cmd = i2c.getNewDriveCommand();
    g_haveCommand    = true;
    last_command_ms  = now_ms;

    g_enable         = (cmd.flags & 0x01);
    g_estop          = (cmd.flags & 0x02);
    g_reverseAllowed = (cmd.flags & 0x04); // currently unused

    g_brake_percent  = cmd.brake_percent;
    g_targetSpeed_mmps = (float)cmd.target_speed_mmps;
    g_targetSteer_rad  = (float)cmd.target_steer_millirad / 1000.0f;

    // Only change steering target when command changes
    steer.setTarget(g_targetSteer_rad);
  }

  // ---------- 2. Watchdog ----------
  if (now_ms - last_command_ms > WATCHDOG_TIMEOUT_MS)
    fault_bits |= FAULT_WATCHDOG;
  else
    fault_bits &= ~FAULT_WATCHDOG;

  // estop bit is latched directly from last command
  if (g_estop)
    fault_bits |= FAULT_ESTOP;
  else
    fault_bits &= ~FAULT_ESTOP;

  // ---------- 3. Speed estimation ----------
  // One estimator call per control loop, using dt_s
  g_measuredSpeed_mmps = speedEst.update(dt_s);

  // ---------- 4. Safety / drive logic ----------
  bool safe_stop = (!g_enable) || g_estop || (fault_bits & FAULT_WATCHDOG);

  // Brakes: force full if safe_stop, otherwise use commanded
  uint8_t brake_cmd = g_brake_percent;
  if (safe_stop) brake_cmd = 100;
  if (brake_cmd > 100) brake_cmd = 100;
  brakes.applyBrakes(brake_cmd);

  // Speed
  motor.setEnable(!safe_stop);

  if (safe_stop) {
    motor.update(0);
  } else {
    int pwm = speedCtrl.update(g_targetSpeed_mmps, g_measuredSpeed_mmps, dt_s);
    motor.update(pwm);
  }

  // Steering: target already latched when command updated
  steer.update(dt_s);

  // ---------- 5. Build status and send to I2C layer ----------
  DriveStatus status{};
  status.measured_speed_mmps     = (int16_t)g_measuredSpeed_mmps;
  status.measured_steer_millirad = (int16_t)(steer.currSteerPos_rad() * 1000.0f);
  status.fault_bits              = fault_bits;

  i2c.setDriveStatus(status);

  // ---------- 6. Debug ----------
  Serial.print(g_targetSpeed_mmps);
  Serial.print(" ");
  Serial.println(g_measuredSpeed_mmps);
  // if (now_ms - last_print_ms >= 500) {
  //   last_print_ms = now_ms;
  //   Serial.print("v(mm/s)=");
  //   Serial.print(g_measuredSpeed_mmps);
  //   Serial.print("  tgt(mm/s)=");
  //   Serial.print(g_targetSpeed_mmps);
  //   Serial.print("  brake(%)=");
  //   Serial.print(brake_cmd);
  //   Serial.print("  faults=0x");
  //   Serial.println(fault_bits, HEX);
  // }
}
