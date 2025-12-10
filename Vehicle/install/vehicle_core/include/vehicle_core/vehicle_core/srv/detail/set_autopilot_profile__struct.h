// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__STRUCT_H_
#define VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'keys'
#include "rosidl_runtime_c/string.h"
// Member 'values'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/SetAutopilotProfile in the package vehicle_core.
typedef struct vehicle_core__srv__SetAutopilotProfile_Request
{
  bool set_profile_id;
  uint8_t profile_id;
  bool set_features_mask;
  uint8_t features_mask;
  /// Optional overrides; both arrays must be the same length if provided
  bool set_params;
  rosidl_runtime_c__String__Sequence keys;
  rosidl_runtime_c__double__Sequence values;
} vehicle_core__srv__SetAutopilotProfile_Request;

// Struct for a sequence of vehicle_core__srv__SetAutopilotProfile_Request.
typedef struct vehicle_core__srv__SetAutopilotProfile_Request__Sequence
{
  vehicle_core__srv__SetAutopilotProfile_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__srv__SetAutopilotProfile_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetAutopilotProfile in the package vehicle_core.
typedef struct vehicle_core__srv__SetAutopilotProfile_Response
{
  bool success;
  rosidl_runtime_c__String message;
} vehicle_core__srv__SetAutopilotProfile_Response;

// Struct for a sequence of vehicle_core__srv__SetAutopilotProfile_Response.
typedef struct vehicle_core__srv__SetAutopilotProfile_Response__Sequence
{
  vehicle_core__srv__SetAutopilotProfile_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_core__srv__SetAutopilotProfile_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__STRUCT_H_
