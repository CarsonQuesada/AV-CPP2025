#pragma once
#include <algorithm>

#define PI 3.14159


template<typename T>
inline T map(T x, T in_min, T in_max, T out_min, T out_max)
{
	x = std::clamp(x, in_min, in_max); // Clamp input to avoid extrapolation
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T>
inline T rad_2_deg(T rad) 
{
    return rad * (180.0 / PI);
}

template<typename T>
inline T deg_2_rad(T deg) 
{
    return deg * (PI / 180.0); 
}