#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <cassert>

#ifdef DEBUG
    #define LOG(level, message, ...) Logger::Log(level, message, ##__VA_ARGS__)
    #define ASSERT(condition, message, ...) Logger::Assert(condition, message, ##__VA_ARGS__)
#else
    #define LOG(level, message, ...) (void)0        // Disable logging in debug builds
    #define ASSERT(condition, message, ...) (void)0 // Disable asserting in debug builds
#endif

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static void Log(LogLevel level, const char* message, ...) {
        const char* colorCode;
        switch (level) {
            case LogLevel::INFO:    colorCode = "\033[0m";   break;  // Default color
            case LogLevel::WARNING: colorCode = "\033[33m";  break;  // Yellow
            case LogLevel::ERROR:   colorCode = "\033[31m";  break;  // Red
            default:                colorCode = "\033[0m";   break;  // Defautl color
        }

        printf("%s", colorCode);  // Apply color
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        va_end(args);
        printf("\033[0m\n");  // Reset color
    }

    // If condition is false message will be printed and program asserted
    static void Assert(bool condition, const char* message, ...) {
        if (!condition) {
            printf("%s", "\033[31m");  // Print in read
            va_list args;
            va_start(args, message);
            vprintf(message, args);
            va_end(args);
            printf("\033[0m\n");  // Reset color
            assert(false);
        }
    }
};

#endif // LOGGER_H