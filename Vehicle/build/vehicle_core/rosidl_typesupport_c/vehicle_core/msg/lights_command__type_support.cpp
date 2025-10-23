// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from vehicle_core:msg/LightsCommand.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "vehicle_core/msg/detail/lights_command__struct.h"
#include "vehicle_core/msg/detail/lights_command__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace vehicle_core
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _LightsCommand_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LightsCommand_type_support_ids_t;

static const _LightsCommand_type_support_ids_t _LightsCommand_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LightsCommand_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LightsCommand_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LightsCommand_type_support_symbol_names_t _LightsCommand_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_core, msg, LightsCommand)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_core, msg, LightsCommand)),
  }
};

typedef struct _LightsCommand_type_support_data_t
{
  void * data[2];
} _LightsCommand_type_support_data_t;

static _LightsCommand_type_support_data_t _LightsCommand_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LightsCommand_message_typesupport_map = {
  2,
  "vehicle_core",
  &_LightsCommand_message_typesupport_ids.typesupport_identifier[0],
  &_LightsCommand_message_typesupport_symbol_names.symbol_name[0],
  &_LightsCommand_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t LightsCommand_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LightsCommand_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace vehicle_core

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, vehicle_core, msg, LightsCommand)() {
  return &::vehicle_core::msg::rosidl_typesupport_c::LightsCommand_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
