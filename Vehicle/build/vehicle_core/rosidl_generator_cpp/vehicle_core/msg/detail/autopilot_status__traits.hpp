// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/AutopilotStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/autopilot_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const AutopilotStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: autopilot_ready
  {
    out << "autopilot_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.autopilot_ready, out);
    out << ", ";
  }

  // member: lidar_ready
  {
    out << "lidar_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.lidar_ready, out);
    out << ", ";
  }

  // member: camera_ready
  {
    out << "camera_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.camera_ready, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AutopilotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: autopilot_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "autopilot_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.autopilot_ready, out);
    out << "\n";
  }

  // member: lidar_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lidar_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.lidar_ready, out);
    out << "\n";
  }

  // member: camera_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "camera_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.camera_ready, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AutopilotStatus & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::AutopilotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::AutopilotStatus & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::AutopilotStatus>()
{
  return "vehicle_core::msg::AutopilotStatus";
}

template<>
inline const char * name<vehicle_core::msg::AutopilotStatus>()
{
  return "vehicle_core/msg/AutopilotStatus";
}

template<>
struct has_fixed_size<vehicle_core::msg::AutopilotStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_core::msg::AutopilotStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_core::msg::AutopilotStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__TRAITS_HPP_
