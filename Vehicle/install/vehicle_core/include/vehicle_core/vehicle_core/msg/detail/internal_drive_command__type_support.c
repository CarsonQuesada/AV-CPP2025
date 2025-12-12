// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_core:msg/InternalDriveCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_core/msg/detail/internal_drive_command__rosidl_typesupport_introspection_c.h"
#include "vehicle_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_core/msg/detail/internal_drive_command__functions.h"
#include "vehicle_core/msg/detail/internal_drive_command__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `controller`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_core__msg__InternalDriveCommand__init(message_memory);
}

void vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_fini_function(void * message_memory)
{
  vehicle_core__msg__InternalDriveCommand__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_member_array[6] = {
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__InternalDriveCommand, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "controller",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__InternalDriveCommand, controller),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "brake",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__InternalDriveCommand, brake),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gear",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__InternalDriveCommand, gear),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_mps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__InternalDriveCommand, speed_mps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "steer_rad",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__InternalDriveCommand, steer_rad),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_members = {
  "vehicle_core__msg",  // message namespace
  "InternalDriveCommand",  // message name
  6,  // number of fields
  sizeof(vehicle_core__msg__InternalDriveCommand),
  vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_member_array,  // message members
  vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_type_support_handle = {
  0,
  &vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_core
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, InternalDriveCommand)() {
  vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_type_support_handle.typesupport_identifier) {
    vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_core__msg__InternalDriveCommand__rosidl_typesupport_introspection_c__InternalDriveCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
