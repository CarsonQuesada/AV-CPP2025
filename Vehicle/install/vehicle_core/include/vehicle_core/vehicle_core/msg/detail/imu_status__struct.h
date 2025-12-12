// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/IMUStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/IMUStatus in the package vehicle_core.
typedef struct vehicle_core__msg__IMUStatus
{
  std_msgs__msg__Header header;
  bool imu_data_ok;
  uint8_t calib_sys;
  uint8_t calib_gyro;
  uint8_t calib_accel;
  uint8_t calib_mag;
  uint8_t op_mode;
  uint8_t err_code;
} vehicle_core__msg__IMUStatus;

// Struct for a sequence of vehicle_core__msg__IMUStatus.
typedef struct vehicle_core__msg__IMUStatus__Sequence
{
  vehicle_core__msg__IMUStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__IMUStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__STRUCT_H_
