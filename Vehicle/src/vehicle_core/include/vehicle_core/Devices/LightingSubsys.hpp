#pragma once

#include <memory>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>

#include "I2C/I2CDevice.hpp"

class LightingSubsys : public I2CDevice {
public:
  using I2CDevice::I2CDevice;

  LightingSubsys(std::shared_ptr<I2CBus> bus, uint8_t addr = 0x15);

  bool sendCommand(const uint8_t& cmd);

private:
};
