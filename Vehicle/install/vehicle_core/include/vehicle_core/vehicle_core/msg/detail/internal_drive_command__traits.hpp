// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/InternalDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/internal_drive_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const InternalDriveCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: controller
  {
    out << "controller: ";
    rosidl_generator_traits::value_to_yaml(msg.controller, out);
    out << ", ";
  }

  // member: brake
  {
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
    out << ", ";
  }

  // member: gear
  {
    out << "gear: ";
    rosidl_generator_traits::value_to_yaml(msg.gear, out);
    out << ", ";
  }

  // member: speed_mps
  {
    out << "speed_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mps, out);
    out << ", ";
  }

  // member: steer_rad
  {
    out << "steer_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.steer_rad, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InternalDriveCommand & msg,
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

  // member: controller
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "controller: ";
    rosidl_generator_traits::value_to_yaml(msg.controller, out);
    out << "\n";
  }

  // member: brake
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
    out << "\n";
  }

  // member: gear
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gear: ";
    rosidl_generator_traits::value_to_yaml(msg.gear, out);
    out << "\n";
  }

  // member: speed_mps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mps, out);
    out << "\n";
  }

  // member: steer_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steer_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.steer_rad, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InternalDriveCommand & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::InternalDriveCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::InternalDriveCommand & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::InternalDriveCommand>()
{
  return "vehicle_core::msg::InternalDriveCommand";
}

template<>
inline const char * name<vehicle_core::msg::InternalDriveCommand>()
{
  return "vehicle_core/msg/InternalDriveCommand";
}

template<>
struct has_fixed_size<vehicle_core::msg::InternalDriveCommand>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_core::msg::InternalDriveCommand>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_core::msg::InternalDriveCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__TRAITS_HPP_
