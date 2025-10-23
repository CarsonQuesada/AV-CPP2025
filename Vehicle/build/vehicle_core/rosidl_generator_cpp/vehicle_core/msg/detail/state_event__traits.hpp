// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/StateEvent.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/state_event__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const StateEvent & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: from_mode
  {
    out << "from_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.from_mode, out);
    out << ", ";
  }

  // member: to_mode
  {
    out << "to_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.to_mode, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StateEvent & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: from_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "from_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.from_mode, out);
    out << "\n";
  }

  // member: to_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "to_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.to_mode, out);
    out << "\n";
  }

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StateEvent & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace vehicle_core

namespace rosidl_generator_traits
{

[[deprecated("use vehicle_core::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vehicle_core::msg::StateEvent & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::StateEvent & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::StateEvent>()
{
  return "vehicle_core::msg::StateEvent";
}

template<>
inline const char * name<vehicle_core::msg::StateEvent>()
{
  return "vehicle_core/msg/StateEvent";
}

template<>
struct has_fixed_size<vehicle_core::msg::StateEvent>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_core::msg::StateEvent>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_core::msg::StateEvent>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__TRAITS_HPP_
