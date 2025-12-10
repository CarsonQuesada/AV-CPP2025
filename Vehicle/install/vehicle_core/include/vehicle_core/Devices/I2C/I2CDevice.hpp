#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <cstdio>

#include "vehicle_core/Devices/I2C/I2CBus.hpp"

class I2CDevice {
public:
    I2CDevice();
    I2CDevice(std::string tag);

    bool open(std::shared_ptr<I2CBus> bus, uint16_t addr);

    bool isOpen() const;
    uint16_t address() const;
    std::string busPath() const;
    const std::string& getTag() const;
    void setTag(std::string t);
    const std::string& getLastError() const;

    std::string prefix() const;

    static std::string to_hex(uint8_t v);

protected:
    bool readReg8(uint8_t reg, uint8_t* out, size_t len);
    bool writeReg8(uint8_t reg, const uint8_t* data, size_t len);
    bool readBytes(uint8_t* data, size_t len);
    bool writeBytes(const uint8_t* data, size_t len);

    std::string tag_;
    std::shared_ptr<I2CBus> bus_;
    std::string lastError_;
    uint8_t address_ = 0;
};
