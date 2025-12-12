// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/LightsStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/lights_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const LightsStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: brake_lights
  {
    out << "brake_lights: ";
    rosidl_generator_traits::value_to_yaml(msg.brake_lights, out);
    out << ", ";
  }

  // member: reverse_lights
  {
    out << "reverse_lights: ";
    rosidl_generator_traits::value_to_yaml(msg.reverse_lights, out);
    out << ", ";
  }

  // member: right_sig
  {
    out << "right_sig: ";
    rosidl_generator_traits::value_to_yaml(msg.right_sig, out);
    out << ", ";
  }

  // member: left_sig
  {
    out << "left_sig: ";
    rosidl_generator_traits::value_to_yaml(msg.left_sig, out);
    out << ", ";
  }

  // member: headlights
  {
    out << "headlights: ";
    rosidl_generator_traits::value_to_yaml(msg.headlights, out);
    out << ", ";
  }

  // member: hazards
  {
    out << "hazards: ";
    rosidl_generator_traits::value_to_yaml(msg.hazards, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LightsStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: brake_lights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brake_lights: ";
    rosidl_generator_traits::value_to_yaml(msg.brake_lights, out);
    out << "\n";
  }

  // member: reverse_lights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reverse_lights: ";
    rosidl_generator_traits::value_to_yaml(msg.reverse_lights, out);
    out << "\n";
  }

  // member: right_sig
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_sig: ";
    rosidl_generator_traits::value_to_yaml(msg.right_sig, out);
    out << "\n";
  }

  // member: left_sig
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_sig: ";
    rosidl_generator_traits::value_to_yaml(msg.left_sig, out);
    out << "\n";
  }

  // member: headlights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "headlights: ";
    rosidl_generator_traits::value_to_yaml(msg.headlights, out);
    out << "\n";
  }

  // member: hazards
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hazards: ";
    rosidl_generator_traits::value_to_yaml(msg.hazards, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LightsStatus & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::LightsStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::LightsStatus & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::LightsStatus>()
{
  return "vehicle_core::msg::LightsStatus";
}

template<>
inline const char * name<vehicle_core::msg::LightsStatus>()
{
  return "vehicle_core/msg/LightsStatus";
}

template<>
struct has_fixed_size<vehicle_core::msg::LightsStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_core::msg::LightsStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_core::msg::LightsStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__TRAITS_HPP_
