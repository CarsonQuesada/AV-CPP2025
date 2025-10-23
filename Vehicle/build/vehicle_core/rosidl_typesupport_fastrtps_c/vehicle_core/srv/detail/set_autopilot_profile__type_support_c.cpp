// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice
#include "vehicle_core/srv/detail/set_autopilot_profile__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_core/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_core/srv/detail/set_autopilot_profile__struct.h"
#include "vehicle_core/srv/detail/set_autopilot_profile__functions.h"
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

#include "rosidl_runtime_c/primitives_sequence.h"  // values
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // values
#include "rosidl_runtime_c/string.h"  // keys
#include "rosidl_runtime_c/string_functions.h"  // keys

// forward declare type support functions


using _SetAutopilotProfile_Request__ros_msg_type = vehicle_core__srv__SetAutopilotProfile_Request;

static bool _SetAutopilotProfile_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SetAutopilotProfile_Request__ros_msg_type * ros_message = static_cast<const _SetAutopilotProfile_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: set_profile_id
  {
    cdr << (ros_message->set_profile_id ? true : false);
  }

  // Field name: profile_id
  {
    cdr << ros_message->profile_id;
  }

  // Field name: set_features_mask
  {
    cdr << (ros_message->set_features_mask ? true : false);
  }

  // Field name: features_mask
  {
    cdr << ros_message->features_mask;
  }

  // Field name: set_params
  {
    cdr << (ros_message->set_params ? true : false);
  }

  // Field name: keys
  {
    size_t size = ros_message->keys.size;
    auto array_ptr = ros_message->keys.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  // Field name: values
  {
    size_t size = ros_message->values.size;
    auto array_ptr = ros_message->values.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _SetAutopilotProfile_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SetAutopilotProfile_Request__ros_msg_type * ros_message = static_cast<_SetAutopilotProfile_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: set_profile_id
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->set_profile_id = tmp ? true : false;
  }

  // Field name: profile_id
  {
    cdr >> ros_message->profile_id;
  }

  // Field name: set_features_mask
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->set_features_mask = tmp ? true : false;
  }

  // Field name: features_mask
  {
    cdr >> ros_message->features_mask;
  }

  // Field name: set_params
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->set_params = tmp ? true : false;
  }

  // Field name: keys
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->keys.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->keys);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->keys, size)) {
      fprintf(stderr, "failed to create array for field 'keys'");
      return false;
    }
    auto array_ptr = ros_message->keys.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'keys'\n");
        return false;
      }
    }
  }

  // Field name: values
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->values.data) {
      rosidl_runtime_c__double__Sequence__fini(&ros_message->values);
    }
    if (!rosidl_runtime_c__double__Sequence__init(&ros_message->values, size)) {
      fprintf(stderr, "failed to create array for field 'values'");
      return false;
    }
    auto array_ptr = ros_message->values.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t get_serialized_size_vehicle_core__srv__SetAutopilotProfile_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SetAutopilotProfile_Request__ros_msg_type * ros_message = static_cast<const _SetAutopilotProfile_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name set_profile_id
  {
    size_t item_size = sizeof(ros_message->set_profile_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name profile_id
  {
    size_t item_size = sizeof(ros_message->profile_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name set_features_mask
  {
    size_t item_size = sizeof(ros_message->set_features_mask);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name features_mask
  {
    size_t item_size = sizeof(ros_message->features_mask);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name set_params
  {
    size_t item_size = sizeof(ros_message->set_params);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name keys
  {
    size_t array_size = ros_message->keys.size;
    auto array_ptr = ros_message->keys.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name values
  {
    size_t array_size = ros_message->values.size;
    auto array_ptr = ros_message->values.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SetAutopilotProfile_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_core__srv__SetAutopilotProfile_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t max_serialized_size_vehicle_core__srv__SetAutopilotProfile_Request(
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

  // member: set_profile_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: profile_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: set_features_mask
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: features_mask
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: set_params
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: keys
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
  // member: values
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
    using DataType = vehicle_core__srv__SetAutopilotProfile_Request;
    is_plain =
      (
      offsetof(DataType, values) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SetAutopilotProfile_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vehicle_core__srv__SetAutopilotProfile_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SetAutopilotProfile_Request = {
  "vehicle_core::srv",
  "SetAutopilotProfile_Request",
  _SetAutopilotProfile_Request__cdr_serialize,
  _SetAutopilotProfile_Request__cdr_deserialize,
  _SetAutopilotProfile_Request__get_serialized_size,
  _SetAutopilotProfile_Request__max_serialized_size
};

static rosidl_message_type_support_t _SetAutopilotProfile_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SetAutopilotProfile_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, srv, SetAutopilotProfile_Request)() {
  return &_SetAutopilotProfile_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "vehicle_core/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__struct.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

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

// already included above
// #include "rosidl_runtime_c/string.h"  // message
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // message

// forward declare type support functions


using _SetAutopilotProfile_Response__ros_msg_type = vehicle_core__srv__SetAutopilotProfile_Response;

static bool _SetAutopilotProfile_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SetAutopilotProfile_Response__ros_msg_type * ros_message = static_cast<const _SetAutopilotProfile_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    cdr << (ros_message->success ? true : false);
  }

  // Field name: message
  {
    const rosidl_runtime_c__String * str = &ros_message->message;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _SetAutopilotProfile_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SetAutopilotProfile_Response__ros_msg_type * ros_message = static_cast<_SetAutopilotProfile_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->success = tmp ? true : false;
  }

  // Field name: message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->message.data) {
      rosidl_runtime_c__String__init(&ros_message->message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'message'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t get_serialized_size_vehicle_core__srv__SetAutopilotProfile_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SetAutopilotProfile_Response__ros_msg_type * ros_message = static_cast<const _SetAutopilotProfile_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name success
  {
    size_t item_size = sizeof(ros_message->success);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->message.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _SetAutopilotProfile_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_core__srv__SetAutopilotProfile_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_core
size_t max_serialized_size_vehicle_core__srv__SetAutopilotProfile_Response(
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

  // member: success
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: message
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
    using DataType = vehicle_core__srv__SetAutopilotProfile_Response;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SetAutopilotProfile_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vehicle_core__srv__SetAutopilotProfile_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SetAutopilotProfile_Response = {
  "vehicle_core::srv",
  "SetAutopilotProfile_Response",
  _SetAutopilotProfile_Response__cdr_serialize,
  _SetAutopilotProfile_Response__cdr_deserialize,
  _SetAutopilotProfile_Response__get_serialized_size,
  _SetAutopilotProfile_Response__max_serialized_size
};

static rosidl_message_type_support_t _SetAutopilotProfile_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SetAutopilotProfile_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, srv, SetAutopilotProfile_Response)() {
  return &_SetAutopilotProfile_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "vehicle_core/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_core/srv/set_autopilot_profile.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t SetAutopilotProfile__callbacks = {
  "vehicle_core::srv",
  "SetAutopilotProfile",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, srv, SetAutopilotProfile_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, srv, SetAutopilotProfile_Response)(),
};

static rosidl_service_type_support_t SetAutopilotProfile__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &SetAutopilotProfile__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, srv, SetAutopilotProfile)() {
  return &SetAutopilotProfile__handle;
}

#if defined(__cplusplus)
}
#endif
