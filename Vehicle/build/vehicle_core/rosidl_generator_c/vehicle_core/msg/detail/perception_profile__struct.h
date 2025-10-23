// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/PerceptionProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__PERCEPTION_PROFILE__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__PERCEPTION_PROFILE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/PerceptionProfile in the package vehicle_core.
typedef struct vehicle_core__msg__PerceptionProfile
{
  /// 0=OFF, 1=LIDAR_ONLY, 2=CAMERA_ONLY, 3=FULL
  uint8_t profile;
} vehicle_core__msg__PerceptionProfile;

// Struct for a sequence of vehicle_core__msg__PerceptionProfile.
typedef struct vehicle_core__msg__PerceptionProfile__Sequence
{
  vehicle_core__msg__PerceptionProfile * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__PerceptionProfile__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__PERCEPTION_PROFILE__STRUCT_H_
