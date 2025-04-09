#pragma once
#include <iostream>

#include <pigpiod_if2.h>

class Pigpio
{
public:
    static inline Pigpio& get_instance() {
        static Pigpio pigpioInstance;
        return pigpioInstance;
    }
    inline int const get_handle() { return piHandle; }
    bool initialize();
    void cleanup();
private:
    bool initialized = false; 
    int piHandle;

    Pigpio() {}                                   // private constructor to prevent more than one instance
    Pigpio(const Pigpio&) = delete;               // Prevent copy construction
    Pigpio& operator=(const Pigpio&) = delete;    // Prevent assignment
    ~Pigpio();
};