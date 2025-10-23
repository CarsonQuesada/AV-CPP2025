// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/server_init__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'general_status'
#include "vehicle_core/msg/detail/general_status__traits.hpp"
// Member 'lights_status'
#include "vehicle_core/msg/detail/lights_status__traits.hpp"
// Member 'drive_status'
#include "vehicle_core/msg/detail/drive_status__traits.hpp"
// Member 'autopilot_status'
#include "vehicle_core/msg/detail/autopilot_status__traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServerInit & msg,
  std::ostream & out)
{
  out << "{";
  // member: general_status
  {
    out << "general_status: ";
    to_flow_style_yaml(msg.general_status, out);
    out << ", ";
  }

  // member: lights_status
  {
    out << "lights_status: ";
    to_flow_style_yaml(msg.lights_status, out);
    out << ", ";
  }

  // member: drive_status
  {
    out << "drive_status: ";
    to_flow_style_yaml(msg.drive_status, out);
    out << ", ";
  }

  // member: autopilot_status
  {
    out << "autopilot_status: ";
    to_flow_style_yaml(msg.autopilot_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServerInit & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: general_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "general_status:\n";
    to_block_style_yaml(msg.general_status, out, indentation + 2);
  }

  // member: lights_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lights_status:\n";
    to_block_style_yaml(msg.lights_status, out, indentation + 2);
  }

  // member: drive_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drive_status:\n";
    to_block_style_yaml(msg.drive_status, out, indentation + 2);
  }

  // member: autopilot_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "autopilot_status:\n";
    to_block_style_yaml(msg.autopilot_status, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServerInit & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::ServerInit & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::ServerInit & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::ServerInit>()
{
  return "vehicle_core::msg::ServerInit";
}

template<>
inline const char * name<vehicle_core::msg::ServerInit>()
{
  return "vehicle_core/msg/ServerInit";
}

template<>
struct has_fixed_size<vehicle_core::msg::ServerInit>
  : std::integral_constant<bool, has_fixed_size<vehicle_core::msg::AutopilotStatus>::value && has_fixed_size<vehicle_core::msg::DriveStatus>::value && has_fixed_size<vehicle_core::msg::GeneralStatus>::value && has_fixed_size<vehicle_core::msg::LightsStatus>::value> {};

template<>
struct has_bounded_size<vehicle_core::msg::ServerInit>
  : std::integral_constant<bool, has_bounded_size<vehicle_core::msg::AutopilotStatus>::value && has_bounded_size<vehicle_core::msg::DriveStatus>::value && has_bounded_size<vehicle_core::msg::GeneralStatus>::value && has_bounded_size<vehicle_core::msg::LightsStatus>::value> {};

template<>
struct is_message<vehicle_core::msg::ServerInit>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__TRAITS_HPP_
