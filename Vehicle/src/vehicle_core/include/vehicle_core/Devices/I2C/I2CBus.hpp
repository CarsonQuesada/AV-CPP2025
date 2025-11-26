#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <optional>
#include <cstdint>
#include <cstddef>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

class I2CBus : public std::enable_shared_from_this<I2CBus> {
public: 
    I2CBus();
    ~I2CBus();

    I2CBus(const I2CBus&) = delete;
    I2CBus& operator=(const I2CBus&) = delete;

    bool open(const std::string& path);
    void close();

    bool isOpen() const;
    const std::string& path() const;
    const std::string& lastError() const;

    bool writeBytes(uint16_t addr7, const uint8_t* data, size_t len);
    bool writeReg8(uint16_t addr7, uint8_t reg, const uint8_t* data, size_t len);
    bool readBytes(uint16_t addr7, uint8_t* data, size_t len);
    bool readReg8(uint16_t addr7, uint8_t reg, uint8_t* out, size_t len);

private:
    bool ensureOpenLocked_();
    bool ensureAddressLocked_(uint16_t addr7);

    int fd_ = -1;
    std::string path_;
    mutable std::mutex mut_;
    std::optional<uint16_t> addr_;
    std::string lastError_;
};
