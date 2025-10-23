// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_core:msg/AutopilotStatus.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/autopilot_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_core/msg/detail/autopilot_status__struct.hpp"

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
  const vehicle_core::msg::AutopilotStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: autopilot_ready
  cdr << (ros_message.autopilot_ready ? true : false);
  // Member: lidar_ready
  cdr << (ros_message.lidar_ready ? true : false);
  // Member: camera_ready
  cdr << (ros_message.camera_ready ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::msg::AutopilotStatus & ros_message)
{
  // Member: autopilot_ready
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.autopilot_ready = tmp ? true : false;
  }

  // Member: lidar_ready
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.lidar_ready = tmp ? true : false;
  }

  // Member: camera_ready
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.camera_ready = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::msg::AutopilotStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: autopilot_ready
  {
    size_t item_size = sizeof(ros_message.autopilot_ready);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: lidar_ready
  {
    size_t item_size = sizeof(ros_message.lidar_ready);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: camera_ready
  {
    size_t item_size = sizeof(ros_message.camera_ready);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_AutopilotStatus(
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


  // Member: autopilot_ready
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: lidar_ready
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: camera_ready
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
    using DataType = vehicle_core::msg::AutopilotStatus;
    is_plain =
      (
      offsetof(DataType, camera_ready) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _AutopilotStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::AutopilotStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _AutopilotStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_core::msg::AutopilotStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _AutopilotStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::AutopilotStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _AutopilotStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_AutopilotStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _AutopilotStatus__callbacks = {
  "vehicle_core::msg",
  "AutopilotStatus",
  _AutopilotStatus__cdr_serialize,
  _AutopilotStatus__cdr_deserialize,
  _AutopilotStatus__get_serialized_size,
  _AutopilotStatus__max_serialized_size
};

static rosidl_message_type_support_t _AutopilotStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_AutopilotStatus__callbacks,
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
get_message_type_support_handle<vehicle_core::msg::AutopilotStatus>()
{
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_AutopilotStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, msg, AutopilotStatus)() {
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_AutopilotStatus__handle;
}

#ifdef __cplusplus
}
#endif
