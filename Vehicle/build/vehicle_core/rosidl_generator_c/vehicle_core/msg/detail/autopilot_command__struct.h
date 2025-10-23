// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/AutopilotCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_COMMAND__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AutopilotCommand in the package vehicle_core.
typedef struct vehicle_core__msg__AutopilotCommand
{
  /// 0=STOP, 1=START
  uint8_t action;
} vehicle_core__msg__AutopilotCommand;

// Struct for a sequence of vehicle_core__msg__AutopilotCommand.
typedef struct vehicle_core__msg__AutopilotCommand__Sequence
{
  vehicle_core__msg__AutopilotCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__AutopilotCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_COMMAND__STRUCT_H_
