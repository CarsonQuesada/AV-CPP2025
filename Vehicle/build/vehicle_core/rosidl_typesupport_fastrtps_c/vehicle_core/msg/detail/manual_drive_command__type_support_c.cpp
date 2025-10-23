// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_core:msg/ManualDriveCommand.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/manual_drive_command__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_core/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_core/msg/detail/manual_drive_command__struct.h"
#include "vehicle_core/msg/detail/manual_drive_command__functions.h"
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


// forward declare type support functions


using _ManualDriveCommand__ros_msg_type = vehicle_core__msg__ManualDriveCommand;

static bool _ManualDriveCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ManualDriveCommand__ros_msg_type * ros_message = static_cast<const _ManualDriveCommand__ros_msg_type *>(untyped_ros_message);
  // Field name: brake
  {
    cdr << ros_message->brake;
  }

  // Field name: gear
  {
    cdr << ros_message->gear;
  }

  // Field name: speed
  {
    cdr << ros_message->speed;
  }

  // Field name: steer
  {
    cdr << ros_message->steer;
  }

  return true;
}

static bool _ManualDriveCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ManualDriveCommand__ros_msg_type * ros_message = static_cast<_ManualDriveCommand__ros_msg_type *>(untyped_ros_message);
  // Field name: brake
  {
    cdr >> ros_message->brake;
  }

  // Field name: gear
  {
    cdr >> ros_message->gear;
  }

  // Field name: speed
  {
    cdr >> ros_message->speed;
  }

  // Field name: steer
  {
    cdr >> ros_message->steer;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t get_serialized_size_vehicle_core__msg__ManualDriveCommand(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ManualDriveCommand__ros_msg_type * ros_message = static_cast<const _ManualDriveCommand__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name brake
  {
    size_t item_size = sizeof(ros_message->brake);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name gear
  {
    size_t item_size = sizeof(ros_message->gear);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name speed
  {
    size_t item_size = sizeof(ros_message->speed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name steer
  {
    size_t item_size = sizeof(ros_message->steer);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ManualDriveCommand__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_core__msg__ManualDriveCommand(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t max_serialized_size_vehicle_core__msg__ManualDriveCommand(
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

  // member: brake
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: gear
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: speed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: steer
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vehicle_core__msg__ManualDriveCommand;
    is_plain =
      (
      offsetof(DataType, steer) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ManualDriveCommand__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vehicle_core__msg__ManualDriveCommand(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ManualDriveCommand = {
  "vehicle_core::msg",
  "ManualDriveCommand",
  _ManualDriveCommand__cdr_serialize,
  _ManualDriveCommand__cdr_deserialize,
  _ManualDriveCommand__get_serialized_size,
  _ManualDriveCommand__max_serialized_size
};

static rosidl_message_type_support_t _ManualDriveCommand__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ManualDriveCommand,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, msg, ManualDriveCommand)() {
  return &_ManualDriveCommand__type_support;
}

#if defined(__cplusplus)
}
#endif
