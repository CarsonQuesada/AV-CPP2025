// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/AutopilotDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_DRIVE_COMMAND__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_DRIVE_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AutopilotDriveCommand in the package vehicle_core.
typedef struct vehicle_core__msg__AutopilotDriveCommand
{
  uint8_t brake;
  uint8_t gear;
  float speed_mps;
  float steer_rad;
} vehicle_core__msg__AutopilotDriveCommand;

// Struct for a sequence of vehicle_core__msg__AutopilotDriveCommand.
typedef struct vehicle_core__msg__AutopilotDriveCommand__Sequence
{
  vehicle_core__msg__AutopilotDriveCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__AutopilotDriveCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_DRIVE_COMMAND__STRUCT_H_
