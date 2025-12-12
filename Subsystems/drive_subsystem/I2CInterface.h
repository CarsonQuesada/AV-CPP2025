#pragma once

#include <Arduino.h>

#define I2C_CMD_MAX  32

// ---------------- Structs (packed) ----------------
#pragma pack(push, 1)
struct DriveCommand {
  uint8_t  flags;                  // bit0: enable, bit1: estop, bit2: reverse_ok
  uint8_t  brake_percent;          // 0..100
  int16_t  target_speed_mmps;      // mm/s
  int16_t  target_steer_millirad;  // mrad
};

struct DriveStatus {
  int16_t  measured_speed_mmps;     // mm/s
  int16_t  measured_steer_millirad; // mrad
  uint16_t fault_bits;              // bitfield
};
#pragma pack(pop)

class I2CInterface {
public:
  explicit I2CInterface(uint8_t address);

  void begin();

  inline bool hasNewCommand() const { return newCommand_; }

  DriveCommand getNewDriveCommand();
  void setDriveStatus(const DriveStatus& status);

private:
  static void onReceiveISR(int count);
  static void onRequestISR();

  void handleReceive(int count);
  void handleRequest();

  // Singleton instance pointer for the ISR to call into
  static I2CInterface* instance_;

  uint8_t address_;

  uint8_t     rxBuffer_[I2C_CMD_MAX];
  uint8_t     rxBufferLen_{0};
  volatile bool newCommand_{false};   // touched in ISR
  DriveCommand lastDriveCommand_{};   // last valid command
  DriveStatus  currDriveStatus_{};    // last status snapshot
};
