// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/ManualDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ManualDriveCommand in the package vehicle_core.
typedef struct vehicle_core__msg__ManualDriveCommand
{
  uint8_t brake;
  uint8_t gear;
  uint8_t speed;
  uint8_t steer;
} vehicle_core__msg__ManualDriveCommand;

// Struct for a sequence of vehicle_core__msg__ManualDriveCommand.
typedef struct vehicle_core__msg__ManualDriveCommand__Sequence
{
  vehicle_core__msg__ManualDriveCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__ManualDriveCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__STRUCT_H_
