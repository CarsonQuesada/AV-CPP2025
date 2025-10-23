// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice
#include "vehicle_core/srv/detail/set_autopilot_profile__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_core/srv/detail/set_autopilot_profile__struct.hpp"

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

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_serialize(
  const vehicle_core::srv::SetAutopilotProfile_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: set_profile_id
  cdr << (ros_message.set_profile_id ? true : false);
  // Member: profile_id
  cdr << ros_message.profile_id;
  // Member: set_features_mask
  cdr << (ros_message.set_features_mask ? true : false);
  // Member: features_mask
  cdr << ros_message.features_mask;
  // Member: set_params
  cdr << (ros_message.set_params ? true : false);
  // Member: keys
  {
    cdr << ros_message.keys;
  }
  // Member: values
  {
    cdr << ros_message.values;
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::srv::SetAutopilotProfile_Request & ros_message)
{
  // Member: set_profile_id
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.set_profile_id = tmp ? true : false;
  }

  // Member: profile_id
  cdr >> ros_message.profile_id;

  // Member: set_features_mask
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.set_features_mask = tmp ? true : false;
  }

  // Member: features_mask
  cdr >> ros_message.features_mask;

  // Member: set_params
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.set_params = tmp ? true : false;
  }

  // Member: keys
  {
    cdr >> ros_message.keys;
  }

  // Member: values
  {
    cdr >> ros_message.values;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::srv::SetAutopilotProfile_Request & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: set_profile_id
  {
    size_t item_size = sizeof(ros_message.set_profile_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: profile_id
  {
    size_t item_size = sizeof(ros_message.profile_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: set_features_mask
  {
    size_t item_size = sizeof(ros_message.set_features_mask);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: features_mask
  {
    size_t item_size = sizeof(ros_message.features_mask);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: set_params
  {
    size_t item_size = sizeof(ros_message.set_params);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: keys
  {
    size_t array_size = ros_message.keys.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.keys[index].size() + 1);
    }
  }
  // Member: values
  {
    size_t array_size = ros_message.values.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.values[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_SetAutopilotProfile_Request(
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


  // Member: set_profile_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: profile_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: set_features_mask
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: features_mask
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: set_params
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: keys
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: values
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vehicle_core::srv::SetAutopilotProfile_Request;
    is_plain =
      (
      offsetof(DataType, values) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _SetAutopilotProfile_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_core::srv::SetAutopilotProfile_Request *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SetAutopilotProfile_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_core::srv::SetAutopilotProfile_Request *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SetAutopilotProfile_Request__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_core::srv::SetAutopilotProfile_Request *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SetAutopilotProfile_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_SetAutopilotProfile_Request(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _SetAutopilotProfile_Request__callbacks = {
  "vehicle_core::srv",
  "SetAutopilotProfile_Request",
  _SetAutopilotProfile_Request__cdr_serialize,
  _SetAutopilotProfile_Request__cdr_deserialize,
  _SetAutopilotProfile_Request__get_serialized_size,
  _SetAutopilotProfile_Request__max_serialized_size
};

static rosidl_message_type_support_t _SetAutopilotProfile_Request__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SetAutopilotProfile_Request__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vehicle_core

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vehicle_core
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_core::srv::SetAutopilotProfile_Request>()
{
  return &vehicle_core::srv::typesupport_fastrtps_cpp::_SetAutopilotProfile_Request__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile_Request)() {
  return &vehicle_core::srv::typesupport_fastrtps_cpp::_SetAutopilotProfile_Request__handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include <limits>
// already included above
// #include <stdexcept>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
// already included above
// #include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

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
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: success
  cdr << (ros_message.success ? true : false);
  // Member: message
  cdr << ros_message.message;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_core::srv::SetAutopilotProfile_Response & ros_message)
{
  // Member: success
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.success = tmp ? true : false;
  }

  // Member: message
  cdr >> ros_message.message;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
get_serialized_size(
  const vehicle_core::srv::SetAutopilotProfile_Response & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: success
  {
    size_t item_size = sizeof(ros_message.success);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.message.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_core
max_serialized_size_SetAutopilotProfile_Response(
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


  // Member: success
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: message
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vehicle_core::srv::SetAutopilotProfile_Response;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _SetAutopilotProfile_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_core::srv::SetAutopilotProfile_Response *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SetAutopilotProfile_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_core::srv::SetAutopilotProfile_Response *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SetAutopilotProfile_Response__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_core::srv::SetAutopilotProfile_Response *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SetAutopilotProfile_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_SetAutopilotProfile_Response(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _SetAutopilotProfile_Response__callbacks = {
  "vehicle_core::srv",
  "SetAutopilotProfile_Response",
  _SetAutopilotProfile_Response__cdr_serialize,
  _SetAutopilotProfile_Response__cdr_deserialize,
  _SetAutopilotProfile_Response__get_serialized_size,
  _SetAutopilotProfile_Response__max_serialized_size
};

static rosidl_message_type_support_t _SetAutopilotProfile_Response__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SetAutopilotProfile_Response__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vehicle_core

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vehicle_core
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_core::srv::SetAutopilotProfile_Response>()
{
  return &vehicle_core::srv::typesupport_fastrtps_cpp::_SetAutopilotProfile_Response__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile_Response)() {
  return &vehicle_core::srv::typesupport_fastrtps_cpp::_SetAutopilotProfile_Response__handle;
}

#ifdef __cplusplus
}
#endif

#include "rmw/error_handling.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support_decl.hpp"

namespace vehicle_core
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

static service_type_support_callbacks_t _SetAutopilotProfile__callbacks = {
  "vehicle_core::srv",
  "SetAutopilotProfile",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile_Response)(),
};

static rosidl_service_type_support_t _SetAutopilotProfile__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SetAutopilotProfile__callbacks,
  get_service_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vehicle_core

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vehicle_core
const rosidl_service_type_support_t *
get_service_type_support_handle<vehicle_core::srv::SetAutopilotProfile>()
{
  return &vehicle_core::srv::typesupport_fastrtps_cpp::_SetAutopilotProfile__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_core, srv, SetAutopilotProfile)() {
  return &vehicle_core::srv::typesupport_fastrtps_cpp::_SetAutopilotProfile__handle;
}

#ifdef __cplusplus
}
#endif
