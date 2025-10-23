// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_core:msg/DriveStatus.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/drive_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_core/msg/detail/drive_status__struct.hpp"

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
  const vehicle_core::msg::DriveStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: gear
  cdr << ros_message.gear;
  // Member: braking
  cdr << (ros_message.braking ? true : false);
  // Member: fault_bits
  cdr << ros_message.fault_bits;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::msg::DriveStatus & ros_message)
{
  // Member: gear
  cdr >> ros_message.gear;

  // Member: braking
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.braking = tmp ? true : false;
  }

  // Member: fault_bits
  cdr >> ros_message.fault_bits;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::msg::DriveStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: gear
  {
    size_t item_size = sizeof(ros_message.gear);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: braking
  {
    size_t item_size = sizeof(ros_message.braking);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: fault_bits
  {
    size_t item_size = sizeof(ros_message.fault_bits);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_DriveStatus(
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


  // Member: gear
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: braking
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: fault_bits
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
    using DataType = vehicle_core::msg::DriveStatus;
    is_plain =
      (
      offsetof(DataType, fault_bits) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _DriveStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::DriveStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _DriveStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_core::msg::DriveStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _DriveStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::DriveStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _DriveStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_DriveStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _DriveStatus__callbacks = {
  "vehicle_core::msg",
  "DriveStatus",
  _DriveStatus__cdr_serialize,
  _DriveStatus__cdr_deserialize,
  _DriveStatus__get_serialized_size,
  _DriveStatus__max_serialized_size
};

static rosidl_message_type_support_t _DriveStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_DriveStatus__callbacks,
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
get_message_type_support_handle<vehicle_core::msg::DriveStatus>()
{
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_DriveStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, msg, DriveStatus)() {
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_DriveStatus__handle;
}

#ifdef __cplusplus
}
#endif
