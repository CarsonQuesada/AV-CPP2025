// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/server_init__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_core/msg/detail/server_init__struct.hpp"

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
bool cdr_serialize(
  const vehicle_core::msg::GeneralStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_core::msg::GeneralStatus &);
size_t get_serialized_size(
  const vehicle_core::msg::GeneralStatus &,
  size_t current_alignment);
size_t
max_serialized_size_GeneralStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_core

namespace vehicle_core
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_core::msg::LightsStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_core::msg::LightsStatus &);
size_t get_serialized_size(
  const vehicle_core::msg::LightsStatus &,
  size_t current_alignment);
size_t
max_serialized_size_LightsStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_core

namespace vehicle_core
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_core::msg::DriveStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_core::msg::DriveStatus &);
size_t get_serialized_size(
  const vehicle_core::msg::DriveStatus &,
  size_t current_alignment);
size_t
max_serialized_size_DriveStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_core

namespace vehicle_core
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vehicle_core::msg::AutopilotStatus &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vehicle_core::msg::AutopilotStatus &);
size_t get_serialized_size(
  const vehicle_core::msg::AutopilotStatus &,
  size_t current_alignment);
size_t
max_serialized_size_AutopilotStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vehicle_core


namespace vehicle_core
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_serialize(
  const vehicle_core::msg::ServerInit & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: general_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.general_status,
    cdr);
  // Member: lights_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.lights_status,
    cdr);
  // Member: drive_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.drive_status,
    cdr);
  // Member: autopilot_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.autopilot_status,
    cdr);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::msg::ServerInit & ros_message)
{
  // Member: general_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.general_status);

  // Member: lights_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.lights_status);

  // Member: drive_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.drive_status);

  // Member: autopilot_status
  vehicle_core::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.autopilot_status);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::msg::ServerInit & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: general_status

  current_alignment +=
    vehicle_core::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.general_status, current_alignment);
  // Member: lights_status

  current_alignment +=
    vehicle_core::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.lights_status, current_alignment);
  // Member: drive_status

  current_alignment +=
    vehicle_core::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.drive_status, current_alignment);
  // Member: autopilot_status

  current_alignment +=
    vehicle_core::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.autopilot_status, current_alignment);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_ServerInit(
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


  // Member: general_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        vehicle_core::msg::typesupport_fastrtps_cpp::max_serialized_size_GeneralStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: lights_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        vehicle_core::msg::typesupport_fastrtps_cpp::max_serialized_size_LightsStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: drive_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        vehicle_core::msg::typesupport_fastrtps_cpp::max_serialized_size_DriveStatus(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: autopilot_status
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        vehicle_core::msg::typesupport_fastrtps_cpp::max_serialized_size_AutopilotStatus(
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
    using DataType = vehicle_core::msg::ServerInit;
    is_plain =
      (
      offsetof(DataType, autopilot_status) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ServerInit__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::ServerInit *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ServerInit__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_core::msg::ServerInit *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ServerInit__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_core::msg::ServerInit *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ServerInit__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ServerInit(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ServerInit__callbacks = {
  "vehicle_core::msg",
  "ServerInit",
  _ServerInit__cdr_serialize,
  _ServerInit__cdr_deserialize,
  _ServerInit__get_serialized_size,
  _ServerInit__max_serialized_size
};

static rosidl_message_type_support_t _ServerInit__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ServerInit__callbacks,
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
get_message_type_support_handle<vehicle_core::msg::ServerInit>()
{
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_ServerInit__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, msg, ServerInit)() {
  return &vehicle_core::msg::typesupport_fastrtps_cpp::_ServerInit__handle;
}

#ifdef __cplusplus
}
#endif
