// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_core:msg/DriveTarget.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_core/msg/detail/drive_target__rosidl_typesupport_introspection_c.h"
#include "vehicle_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_core/msg/detail/drive_target__functions.h"
#include "vehicle_core/msg/detail/drive_target__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_core__msg__DriveTarget__init(message_memory);
}

void vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_fini_function(void * message_memory)
{
  vehicle_core__msg__DriveTarget__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_member_array[3] = {
  {
    "brake_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__DriveTarget, brake_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_speed_mmps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__DriveTarget, target_speed_mmps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_steer_millirad",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__DriveTarget, target_steer_millirad),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_members = {
  "vehicle_core__msg",  // message namespace
  "DriveTarget",  // message name
  3,  // number of fields
  sizeof(vehicle_core__msg__DriveTarget),
  vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_member_array,  // message members
  vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_type_support_handle = {
  0,
  &vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_core
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, DriveTarget)() {
  if (!vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_type_support_handle.typesupport_identifier) {
    vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_core__msg__DriveTarget__rosidl_typesupport_introspection_c__DriveTarget_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
