// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:srv/RequestInternalControl.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__REQUEST_INTERNAL_CONTROL__STRUCT_H_
#define VEHICLE_CORE__SRV__DETAIL__REQUEST_INTERNAL_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'controller'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/RequestInternalControl in the package vehicle_core.
typedef struct vehicle_core__srv__RequestInternalControl_Request
{
  rosidl_runtime_c__String controller;
} vehicle_core__srv__RequestInternalControl_Request;

// Struct for a sequence of vehicle_core__srv__RequestInternalControl_Request.
typedef struct vehicle_core__srv__RequestInternalControl_Request__Sequence
{
  vehicle_core__srv__RequestInternalControl_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__srv__RequestInternalControl_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/RequestInternalControl in the package vehicle_core.
typedef struct vehicle_core__srv__RequestInternalControl_Response
{
  bool success;
  rosidl_runtime_c__String message;
} vehicle_core__srv__RequestInternalControl_Response;

// Struct for a sequence of vehicle_core__srv__RequestInternalControl_Response.
typedef struct vehicle_core__srv__RequestInternalControl_Response__Sequence
{
  vehicle_core__srv__RequestInternalControl_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__srv__RequestInternalControl_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__SRV__DETAIL__REQUEST_INTERNAL_CONTROL__STRUCT_H_
