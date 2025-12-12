// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/AutopilotConfig.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'keys'
#include "rosidl_runtime_c/string.h"
// Member 'values'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/AutopilotConfig in the package vehicle_core.
typedef struct vehicle_core__msg__AutopilotConfig
{
  /// 0=DEFAULT, 1=LANES_ONLY, 2=OBSTACLES_ONLY, ...
  uint8_t profile_id;
  /// bit flags to mix features (e.g., 1=LANES, 2=OBSTACLES, 4=SPEED_CTRL, ...)
  uint8_t features_mask;
  /// optional override names
  rosidl_runtime_c__String__Sequence keys;
  /// same length as keys; numeric overrides
  rosidl_runtime_c__double__Sequence values;
} vehicle_core__msg__AutopilotConfig;

// Struct for a sequence of vehicle_core__msg__AutopilotConfig.
typedef struct vehicle_core__msg__AutopilotConfig__Sequence
{
  vehicle_core__msg__AutopilotConfig * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__AutopilotConfig__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__STRUCT_H_
