// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/InternalDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'controller'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/InternalDriveCommand in the package vehicle_core.
typedef struct vehicle_core__msg__InternalDriveCommand
{
  builtin_interfaces__msg__Time stamp;
  rosidl_runtime_c__String controller;
  uint8_t brake;
  uint8_t gear;
  float speed_mps;
  float steer_rad;
} vehicle_core__msg__InternalDriveCommand;

// Struct for a sequence of vehicle_core__msg__InternalDriveCommand.
typedef struct vehicle_core__msg__InternalDriveCommand__Sequence
{
  vehicle_core__msg__InternalDriveCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__InternalDriveCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__STRUCT_H_
