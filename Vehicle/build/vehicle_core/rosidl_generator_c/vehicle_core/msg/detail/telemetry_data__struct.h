// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/TelemetryData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TelemetryData in the package vehicle_core.
typedef struct vehicle_core__msg__TelemetryData
{
  bool gps_online;
  float lat;
  float lon;
  float heading;
  float speed;
  float distance_delta;
} vehicle_core__msg__TelemetryData;

// Struct for a sequence of vehicle_core__msg__TelemetryData.
typedef struct vehicle_core__msg__TelemetryData__Sequence
{
  vehicle_core__msg__TelemetryData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__TelemetryData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__STRUCT_H_
