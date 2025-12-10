// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'general_status'
#include "vehicle_core/msg/detail/general_status__struct.h"
// Member 'lights_status'
#include "vehicle_core/msg/detail/lights_status__struct.h"
// Member 'drive_status'
#include "vehicle_core/msg/detail/drive_status__struct.h"
// Member 'autopilot_status'
#include "vehicle_core/msg/detail/autopilot_status__struct.h"

/// Struct defined in msg/ServerInit in the package vehicle_core.
typedef struct vehicle_core__msg__ServerInit
{
  vehicle_core__msg__GeneralStatus general_status;
  vehicle_core__msg__LightsStatus lights_status;
  vehicle_core__msg__DriveStatus drive_status;
  vehicle_core__msg__AutopilotStatus autopilot_status;
} vehicle_core__msg__ServerInit;

// Struct for a sequence of vehicle_core__msg__ServerInit.
typedef struct vehicle_core__msg__ServerInit__Sequence
{
  vehicle_core__msg__ServerInit * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__ServerInit__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__STRUCT_H_
