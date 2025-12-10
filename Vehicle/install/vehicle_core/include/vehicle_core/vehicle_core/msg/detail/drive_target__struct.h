// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/DriveTarget.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DriveTarget in the package vehicle_core.
/**
  * Percent 0..100 (clamped in arbiter)
 */
typedef struct vehicle_core__msg__DriveTarget
{
  uint8_t brake_percent;
  /// Signed linear speed in mm/s (negative -> reverse, zero -> coast/neutral)
  int16_t target_speed_mmps;
  /// Signed steering in milliradians (-left, +right), clamped to steer.max_rad
  int16_t target_steer_millirad;
} vehicle_core__msg__DriveTarget;

// Struct for a sequence of vehicle_core__msg__DriveTarget.
typedef struct vehicle_core__msg__DriveTarget__Sequence
{
  vehicle_core__msg__DriveTarget * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__DriveTarget__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__STRUCT_H_
