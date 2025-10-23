// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_core:msg/DriveTarget.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/drive_target__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_core/msg/detail/drive_target__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace vehicle_core
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_serialize(
  const vehicle_core::msg::DriveTarget & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: brake_percent
  cdr << ros_message.brake_percent;
  // Member: target_speed_mmps
  cdr << ros_message.target_speed_mmps;
  // Member: target_steer_millirad
  cdr << ros_message.target_steer_millirad;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::msg::DriveTarget & ros_message)
{
  // Member: brake_percent
  cdr >> ros_message.brake_percent;

  // Member: target_speed_mmps
  cdr >> ros_message.target_speed_mmps;

  // Member: target_steer_millirad
  cdr >> ros_message.target_steer_millirad;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::msg::DriveTarget & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: brake_percent
  {
    size_t item_size = sizeof(ros_message.brake_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: target_speed_mmps
  {
    size_t item_size = sizeof(ros_message.target_speed_mmps);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: target_steer_millirad
  {
    size_t item_size = sizeof(ros_message.target_steer_millirad);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_DriveTarget(
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


  // Member: brake_percent
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: target_speed_mmps
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: target_steer_millirad
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vehicle_core::msg::DriveTarget;
    is_plain =
      (
      offsetof(DataType, target_steer_millirad) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _DriveTarget__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::DriveTarget *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _DriveTarget__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_core::msg::DriveTarget *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _DriveTarget__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::DriveTarget *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _DriveTarget__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_DriveTarget(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _DriveTarget__callbacks = {
  "vehicle_core::msg",
  "DriveTarget",
  _DriveTarget__cdr_serialize,
  _DriveTarget__cdr_deserialize,
  _DriveTarget__get_serialized_size,
  _DriveTarget__max_serialized_size
};

static rosidl_message_type_support_t _DriveTarget__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_DriveTarget__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vehicle_core

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vehicle_core
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_core::msg::DriveTarget>()
{
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_DriveTarget__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, msg, DriveTarget)() {
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_DriveTarget__handle;
}

#ifdef __cplusplus
}
#endif
