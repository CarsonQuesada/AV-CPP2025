// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_core/srv/detail/set_autopilot_profile__rosidl_typesupport_introspection_c.h"
#include "vehicle_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_core/srv/detail/set_autopilot_profile__functions.h"
#include "vehicle_core/srv/detail/set_autopilot_profile__struct.h"


// Include directives for member types
// Member `keys`
#include "rosidl_runtime_c/string_functions.h"
// Member `values`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_core__srv__SetAutopilotProfile_Request__init(message_memory);
}

void vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_fini_function(void * message_memory)
{
  vehicle_core__srv__SetAutopilotProfile_Request__fini(message_memory);
}

size_t vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__size_function__SetAutopilotProfile_Request__keys(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetAutopilotProfile_Request__keys(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_function__SetAutopilotProfile_Request__keys(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__fetch_function__SetAutopilotProfile_Request__keys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetAutopilotProfile_Request__keys(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__assign_function__SetAutopilotProfile_Request__keys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_function__SetAutopilotProfile_Request__keys(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__resize_function__SetAutopilotProfile_Request__keys(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__size_function__SetAutopilotProfile_Request__values(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetAutopilotProfile_Request__values(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_function__SetAutopilotProfile_Request__values(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__fetch_function__SetAutopilotProfile_Request__values(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetAutopilotProfile_Request__values(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__assign_function__SetAutopilotProfile_Request__values(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_function__SetAutopilotProfile_Request__values(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__resize_function__SetAutopilotProfile_Request__values(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_member_array[7] = {
  {
    "set_profile_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Request, set_profile_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "profile_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Request, profile_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "set_features_mask",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Request, set_features_mask),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "features_mask",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Request, features_mask),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "set_params",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Request, set_params),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "keys",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Request, keys),  // bytes offset in struct
    NULL,  // default value
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__size_function__SetAutopilotProfile_Request__keys,  // size() function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetAutopilotProfile_Request__keys,  // get_const(index) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_function__SetAutopilotProfile_Request__keys,  // get(index) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__fetch_function__SetAutopilotProfile_Request__keys,  // fetch(index, &value) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__assign_function__SetAutopilotProfile_Request__keys,  // assign(index, value) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__resize_function__SetAutopilotProfile_Request__keys  // resize(index) function pointer
  },
  {
    "values",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Request, values),  // bytes offset in struct
    NULL,  // default value
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__size_function__SetAutopilotProfile_Request__values,  // size() function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetAutopilotProfile_Request__values,  // get_const(index) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__get_function__SetAutopilotProfile_Request__values,  // get(index) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__fetch_function__SetAutopilotProfile_Request__values,  // fetch(index, &value) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__assign_function__SetAutopilotProfile_Request__values,  // assign(index, value) function pointer
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__resize_function__SetAutopilotProfile_Request__values  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_members = {
  "vehicle_core__srv",  // message namespace
  "SetAutopilotProfile_Request",  // message name
  7,  // number of fields
  sizeof(vehicle_core__srv__SetAutopilotProfile_Request),
  vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_member_array,  // message members
  vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_type_support_handle = {
  0,
  &vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_core
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, srv, SetAutopilotProfile_Request)() {
  if (!vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_type_support_handle.typesupport_identifier) {
    vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_core__srv__SetAutopilotProfile_Request__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vehicle_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__functions.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_core__srv__SetAutopilotProfile_Response__init(message_memory);
}

void vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_fini_function(void * message_memory)
{
  vehicle_core__srv__SetAutopilotProfile_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__srv__SetAutopilotProfile_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_members = {
  "vehicle_core__srv",  // message namespace
  "SetAutopilotProfile_Response",  // message name
  2,  // number of fields
  sizeof(vehicle_core__srv__SetAutopilotProfile_Response),
  vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_member_array,  // message members
  vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_type_support_handle = {
  0,
  &vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_core
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, srv, SetAutopilotProfile_Response)() {
  if (!vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_type_support_handle.typesupport_identifier) {
    vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_core__srv__SetAutopilotProfile_Response__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vehicle_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_service_members = {
  "vehicle_core__srv",  // service namespace
  "SetAutopilotProfile",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_Request_message_type_support_handle,
  NULL  // response message
  // vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_Response_message_type_support_handle
};

static rosidl_service_type_support_t vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_service_type_support_handle = {
  0,
  &vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, srv, SetAutopilotProfile_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, srv, SetAutopilotProfile_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_core
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, srv, SetAutopilotProfile)() {
  if (!vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_service_type_support_handle.typesupport_identifier) {
    vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, srv, SetAutopilotProfile_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, srv, SetAutopilotProfile_Response)()->data;
  }

  return &vehicle_core__srv__detail__set_autopilot_profile__rosidl_typesupport_introspection_c__SetAutopilotProfile_service_type_support_handle;
}
