#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "vehicle_core/Devices/I2C/I2CBus.hpp"

class I2CBusRegistry {
public: 
    static I2CBusRegistry& getInstance();

    std::shared_ptr<I2CBus> getOrOpen(const std::string& path,
                                      std::string* err = nullptr);

private:
    I2CBusRegistry() = default;
    ~I2CBusRegistry() = default;

    I2CBusRegistry(const I2CBusRegistry&) = delete;
    I2CBusRegistry& operator=(const I2CBusRegistry&) = delete;

    std::mutex mut_;
    std::unordered_map<std::string, std::weak_ptr<I2CBus>> buses_;
};
