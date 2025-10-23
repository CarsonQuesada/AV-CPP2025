// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/DriveTarget.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/drive_target__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const DriveTarget & msg,
  std::ostream & out)
{
  out << "{";
  // member: brake_percent
  {
    out << "brake_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.brake_percent, out);
    out << ", ";
  }

  // member: target_speed_mmps
  {
    out << "target_speed_mmps: ";
    rosidl_generator_traits::value_to_yaml(msg.target_speed_mmps, out);
    out << ", ";
  }

  // member: target_steer_millirad
  {
    out << "target_steer_millirad: ";
    rosidl_generator_traits::value_to_yaml(msg.target_steer_millirad, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DriveTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: brake_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brake_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.brake_percent, out);
    out << "\n";
  }

  // member: target_speed_mmps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_speed_mmps: ";
    rosidl_generator_traits::value_to_yaml(msg.target_speed_mmps, out);
    out << "\n";
  }

  // member: target_steer_millirad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_steer_millirad: ";
    rosidl_generator_traits::value_to_yaml(msg.target_steer_millirad, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DriveTarget & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::DriveTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::DriveTarget & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::DriveTarget>()
{
  return "vehicle_core::msg::DriveTarget";
}

template<>
inline const char * name<vehicle_core::msg::DriveTarget>()
{
  return "vehicle_core/msg/DriveTarget";
}

template<>
struct has_fixed_size<vehicle_core::msg::DriveTarget>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_core::msg::DriveTarget>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_core::msg::DriveTarget>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__TRAITS_HPP_
