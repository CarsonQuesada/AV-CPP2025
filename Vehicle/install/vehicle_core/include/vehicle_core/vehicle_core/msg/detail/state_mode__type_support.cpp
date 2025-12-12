// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_core:msg/StateMode.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vehicle_core/msg/detail/state_mode__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vehicle_core
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void StateMode_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vehicle_core::msg::StateMode(_init);
}

void StateMode_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vehicle_core::msg::StateMode *>(message_memory);
  typed_message->~StateMode();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember StateMode_message_member_array[1] = {
  {
    "mode",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_core::msg::StateMode, mode),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers StateMode_message_members = {
  "vehicle_core::msg",  // message namespace
  "StateMode",  // message name
  1,  // number of fields
  sizeof(vehicle_core::msg::StateMode),
  StateMode_message_member_array,  // message members
  StateMode_init_function,  // function to initialize message memory (memory has to be allocated)
  StateMode_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t StateMode_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &StateMode_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace vehicle_core


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_core::msg::StateMode>()
{
  return &::vehicle_core::msg::rosidl_typesupport_introspection_cpp::StateMode_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vehicle_core, msg, StateMode)() {
  return &::vehicle_core::msg::rosidl_typesupport_introspection_cpp::StateMode_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
