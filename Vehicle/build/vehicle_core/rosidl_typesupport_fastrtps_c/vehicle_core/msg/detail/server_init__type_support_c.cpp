// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/server_init__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_core/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_core/msg/detail/server_init__struct.h"
#include "vehicle_core/msg/detail/server_init__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "vehicle_core/msg/detail/autopilot_status__functions.h"  // autopilot_status
#include "vehicle_core/msg/detail/drive_status__functions.h"  // drive_status
#include "vehicle_core/msg/detail/general_status__functions.h"  // general_status
#include "vehicle_core/msg/detail/lights_status__functions.h"  // lights_status

// forward declare type support functions
size_t get_serialized_size_vehicle_core__msg__AutopilotStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_core__msg__AutopilotStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, msg, AutopilotStatus)();
size_t get_serialized_size_vehicle_core__msg__DriveStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_core__msg__DriveStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, msg, DriveStatus)();
size_t get_serialized_size_vehicle_core__msg__GeneralStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_core__msg__GeneralStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, msg, GeneralStatus)();
size_t get_serialized_size_vehicle_core__msg__LightsStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vehicle_core__msg__LightsStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, msg, LightsStatus)();


using _ServerInit__ros_msg_type = vehicle_core__msg__ServerInit;

static bool _ServerInit__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ServerInit__ros_msg_type * ros_message = static_cast<const _ServerInit__ros_msg_type *>(untyped_ros_message);
  // Field name: general_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, GeneralStatus
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->general_status, cdr))
    {
      return false;
    }
  }

  // Field name: lights_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, LightsStatus
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->lights_status, cdr))
    {
      return false;
    }
  }

  // Field name: drive_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, DriveStatus
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->drive_status, cdr))
    {
      return false;
    }
  }

  // Field name: autopilot_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, AutopilotStatus
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->autopilot_status, cdr))
    {
      return false;
    }
  }

  return true;
}

static bool _ServerInit__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ServerInit__ros_msg_type * ros_message = static_cast<_ServerInit__ros_msg_type *>(untyped_ros_message);
  // Field name: general_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, GeneralStatus
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->general_status))
    {
      return false;
    }
  }

  // Field name: lights_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, LightsStatus
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->lights_status))
    {
      return false;
    }
  }

  // Field name: drive_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, DriveStatus
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->drive_status))
    {
      return false;
    }
  }

  // Field name: autopilot_status
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vehicle_core, msg, AutopilotStatus
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->autopilot_status))
    {
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t get_serialized_size_vehicle_core__msg__ServerInit(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ServerInit__ros_msg_type * ros_message = static_cast<const _ServerInit__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name general_status

  current_alignment += get_serialized_size_vehicle_core__msg__GeneralStatus(
    &(ros_message->general_status), current_alignment);
  // field.name lights_status

  current_alignment += get_serialized_size_vehicle_core__msg__LightsStatus(
    &(ros_message->lights_status), current_alignment);
  // field.name drive_status

  current_alignment += get_serialized_size_vehicle_core__msg__DriveStatus(
    &(ros_message->drive_status), current_alignment);
  // field.name autopilot_status

  current_alignment += get_serialized_size_vehicle_core__msg__AutopilotStatus(
    &(ros_message->autopilot_status), current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _ServerInit__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_core__msg__ServerInit(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t max_serialized_size_vehicle_core__msg__ServerInit(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: general_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_vehicle_core__msg__GeneralStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: lights_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_vehicle_core__msg__LightsStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: drive_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_vehicle_core__msg__DriveStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: autopilot_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_vehicle_core__msg__AutopilotStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vehicle_core__msg__ServerInit;
    is_plain =
      (
      offsetof(DataType, autopilot_status) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ServerInit__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vehicle_core__msg__ServerInit(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ServerInit = {
  "vehicle_core::msg",
  "ServerInit",
  _ServerInit__cdr_serialize,
  _ServerInit__cdr_deserialize,
  _ServerInit__get_serialized_size,
  _ServerInit__max_serialized_size
};

static rosidl_message_type_support_t _ServerInit__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ServerInit,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, msg, ServerInit)() {
  return &_ServerInit__type_support;
}

#if defined(__cplusplus)
}
#endif
