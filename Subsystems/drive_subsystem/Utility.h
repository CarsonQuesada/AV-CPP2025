#pragma once

constexpr int PWM_MAX = 255;

inline int clampi(int val, int min, int max) {
    if (val < min)
        return min;
    else if (val > max)
        return max;
    else
        return val;
}

inline float clampf(float val, float min, float max) {
    if (val < min)
        return min;
    else if (val > max)
        return max;
    else
        return val;
}

inline int lerpi(int val, int fromMin, int fromMax, int toMin, int toMax)
{
    // Avoid division by zero
    if (fromMax == fromMin) return toMin;

    // Compute the proportion within the source range
    float t = float(val - fromMin) / float(fromMax - fromMin);

    // Map to destination range
    return int(toMin + t * (toMax - toMin));
}
