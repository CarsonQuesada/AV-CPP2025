// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_core/msg/detail/server_init__rosidl_typesupport_introspection_c.h"
#include "vehicle_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_core/msg/detail/server_init__functions.h"
#include "vehicle_core/msg/detail/server_init__struct.h"


// Include directives for member types
// Member `general_status`
#include "vehicle_core/msg/general_status.h"
// Member `general_status`
#include "vehicle_core/msg/detail/general_status__rosidl_typesupport_introspection_c.h"
// Member `lights_status`
#include "vehicle_core/msg/lights_status.h"
// Member `lights_status`
#include "vehicle_core/msg/detail/lights_status__rosidl_typesupport_introspection_c.h"
// Member `drive_status`
#include "vehicle_core/msg/drive_status.h"
// Member `drive_status`
#include "vehicle_core/msg/detail/drive_status__rosidl_typesupport_introspection_c.h"
// Member `autopilot_status`
#include "vehicle_core/msg/autopilot_status.h"
// Member `autopilot_status`
#include "vehicle_core/msg/detail/autopilot_status__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_core__msg__ServerInit__init(message_memory);
}

void vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_fini_function(void * message_memory)
{
  vehicle_core__msg__ServerInit__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_member_array[4] = {
  {
    "general_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__ServerInit, general_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "lights_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__ServerInit, lights_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drive_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__ServerInit, drive_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "autopilot_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core__msg__ServerInit, autopilot_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_members = {
  "vehicle_core__msg",  // message namespace
  "ServerInit",  // message name
  4,  // number of fields
  sizeof(vehicle_core__msg__ServerInit),
  vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_member_array,  // message members
  vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_type_support_handle = {
  0,
  &vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_core
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, ServerInit)() {
  vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, GeneralStatus)();
  vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, LightsStatus)();
  vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, DriveStatus)();
  vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, AutopilotStatus)();
  if (!vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_type_support_handle.typesupport_identifier) {
    vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_core__msg__ServerInit__rosidl_typesupport_introspection_c__ServerInit_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
