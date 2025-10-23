// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/DriveFeedback.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DriveFeedback in the package vehicle_core.
typedef struct vehicle_core__msg__DriveFeedback
{
  int16_t speed_mmps;
  int16_t steer_millirad;
} vehicle_core__msg__DriveFeedback;

// Struct for a sequence of vehicle_core__msg__DriveFeedback.
typedef struct vehicle_core__msg__DriveFeedback__Sequence
{
  vehicle_core__msg__DriveFeedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__DriveFeedback__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__STRUCT_H_
