// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/LightsCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/lights_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const LightsCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: light_id
  {
    out << "light_id: ";
    rosidl_generator_traits::value_to_yaml(msg.light_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LightsCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: light_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "light_id: ";
    rosidl_generator_traits::value_to_yaml(msg.light_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LightsCommand & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::LightsCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::LightsCommand & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::LightsCommand>()
{
  return "vehicle_core::msg::LightsCommand";
}

template<>
inline const char * name<vehicle_core::msg::LightsCommand>()
{
  return "vehicle_core/msg/LightsCommand";
}

template<>
struct has_fixed_size<vehicle_core::msg::LightsCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_core::msg::LightsCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_core::msg::LightsCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__TRAITS_HPP_
