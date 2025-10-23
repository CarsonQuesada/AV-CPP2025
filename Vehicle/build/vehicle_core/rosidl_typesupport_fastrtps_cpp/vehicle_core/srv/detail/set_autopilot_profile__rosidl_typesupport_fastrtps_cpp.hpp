// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "vehicle_core/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "vehicle_core/srv/detail/set_autopilot_profile__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace vehicle_core
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_serialize(
  const vehicle_core::srv::SetAutopilotProfile_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::srv::SetAutopilotProfile_Request & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::srv::SetAutopilotProfile_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_SetAutopilotProfile_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vehicle_core

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile_Request)();

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vehicle_core/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace vehicle_core
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_serialize(
  const vehicle_core::srv::SetAutopilotProfile_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::srv::SetAutopilotProfile_Response & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::srv::SetAutopilotProfile_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_SetAutopilotProfile_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vehicle_core

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile_Response)();

#ifdef __cplusplus
}
#endif

#include "rmw/types.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "vehicle_core/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile)();

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
