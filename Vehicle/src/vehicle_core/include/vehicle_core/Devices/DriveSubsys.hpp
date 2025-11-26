#pragma once

#include <memory>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <cmath>

#include "vehicle_core/Devices/I2C/I2CDevice.hpp"

#pragma pack(push,1)
struct DriveCommandWire {
  uint8_t  flags;                  // bit0: enable, bit1: estop, bit2: reverse_ok
  uint8_t  brake_percent;          // 0..100
  int16_t  target_speed_mmps;      // signed mm/s
  int16_t  target_steer_millirad;  // signed mrad
};

struct DriveStatusWire {
  int16_t  measured_speed_mmps;     // signed mm/s
  int16_t  measured_steer_millirad; // signed mrad
  uint16_t fault_bits;              // 1=WATCHDOG,2=ESTOP,4=OVERCURR(placeholder)
};
#pragma pack(pop)

class DriveSubsys : public I2CDevice {
public:
  using I2CDevice::I2CDevice;

  DriveSubsys(std::shared_ptr<I2CBus> bus, uint8_t addr = 0x20);

  bool sendCommand(const DriveCommandWire& cmd);
  bool readStatus(DriveStatusWire& status);

private:
};
