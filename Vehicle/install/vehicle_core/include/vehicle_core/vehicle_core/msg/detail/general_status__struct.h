// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/GeneralStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/GeneralStatus in the package vehicle_core.
typedef struct vehicle_core__msg__GeneralStatus
{
  uint32_t speed;
  uint32_t battery_percent;
  bool gps_online;
} vehicle_core__msg__GeneralStatus;

// Struct for a sequence of vehicle_core__msg__GeneralStatus.
typedef struct vehicle_core__msg__GeneralStatus__Sequence
{
  vehicle_core__msg__GeneralStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__GeneralStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__STRUCT_H_
