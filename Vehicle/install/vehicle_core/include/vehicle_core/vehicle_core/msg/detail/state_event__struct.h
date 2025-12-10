// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:msg/StateEvent.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__STRUCT_H_
#define VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__STRUCT_H_

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
// Member 'reason'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/StateEvent in the package vehicle_core.
typedef struct vehicle_core__msg__StateEvent
{
  builtin_interfaces__msg__Time stamp;
  uint8_t from_mode;
  uint8_t to_mode;
  rosidl_runtime_c__String reason;
} vehicle_core__msg__StateEvent;

// Struct for a sequence of vehicle_core__msg__StateEvent.
typedef struct vehicle_core__msg__StateEvent__Sequence
{
  vehicle_core__msg__StateEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__msg__StateEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__STRUCT_H_
