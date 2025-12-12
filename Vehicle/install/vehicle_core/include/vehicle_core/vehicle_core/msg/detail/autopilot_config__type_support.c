// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_core:msg/AutopilotConfig.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_core/msg/detail/autopilot_config__rosidl_typesupport_introspection_c.h"
#include "vehicle_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_core/msg/detail/autopilot_config__functions.h"
#include "vehicle_core/msg/detail/autopilot_config__struct.h"


// Include directives for member types
// Member `keys`
#include "rosidl_runtime_c/string_functions.h"
// Member `values`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_core__msg__AutopilotConfig__init(message_memory);
}

void vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_fini_function(void * message_memory)
{
  vehicle_core__msg__AutopilotConfig__fini(message_memory);
}

size_t vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__size_function__AutopilotConfig__keys(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_const_function__AutopilotConfig__keys(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_function__AutopilotConfig__keys(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__fetch_function__AutopilotConfig__keys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_const_function__AutopilotConfig__keys(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__assign_function__AutopilotConfig__keys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_function__AutopilotConfig__keys(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__resize_function__AutopilotConfig__keys(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__size_function__AutopilotConfig__values(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_const_function__AutopilotConfig__values(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_function__AutopilotConfig__values(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__fetch_function__AutopilotConfig__values(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_const_function__AutopilotConfig__values(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__assign_function__AutopilotConfig__values(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_function__AutopilotConfig__values(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__resize_function__AutopilotConfig__values(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_member_array[4] = {
  {
    "profile_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__AutopilotConfig, profile_id),  // bytes offset in struct
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
    offsetof(vehicle_core__msg__AutopilotConfig, features_mask),  // bytes offset in struct
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
    offsetof(vehicle_core__msg__AutopilotConfig, keys),  // bytes offset in struct
    NULL,  // default value
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__size_function__AutopilotConfig__keys,  // size() function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_const_function__AutopilotConfig__keys,  // get_const(index) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_function__AutopilotConfig__keys,  // get(index) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__fetch_function__AutopilotConfig__keys,  // fetch(index, &value) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__assign_function__AutopilotConfig__keys,  // assign(index, value) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__resize_function__AutopilotConfig__keys  // resize(index) function pointer
  },
  {
    "values",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__AutopilotConfig, values),  // bytes offset in struct
    NULL,  // default value
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__size_function__AutopilotConfig__values,  // size() function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_const_function__AutopilotConfig__values,  // get_const(index) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__get_function__AutopilotConfig__values,  // get(index) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__fetch_function__AutopilotConfig__values,  // fetch(index, &value) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__assign_function__AutopilotConfig__values,  // assign(index, value) function pointer
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__resize_function__AutopilotConfig__values  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_members = {
  "vehicle_core__msg",  // message namespace
  "AutopilotConfig",  // message name
  4,  // number of fields
  sizeof(vehicle_core__msg__AutopilotConfig),
  vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_member_array,  // message members
  vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_type_support_handle = {
  0,
  &vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_core
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, AutopilotConfig)() {
  if (!vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_type_support_handle.typesupport_identifier) {
    vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_core__msg__AutopilotConfig__rosidl_typesupport_introspection_c__AutopilotConfig_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
