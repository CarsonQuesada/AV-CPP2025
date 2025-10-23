// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/DriveStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/drive_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const DriveStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: gear
  {
    out << "gear: ";
    rosidl_generator_traits::value_to_yaml(msg.gear, out);
    out << ", ";
  }

  // member: braking
  {
    out << "braking: ";
    rosidl_generator_traits::value_to_yaml(msg.braking, out);
    out << ", ";
  }

  // member: fault_bits
  {
    out << "fault_bits: ";
    rosidl_generator_traits::value_to_yaml(msg.fault_bits, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DriveStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: gear
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gear: ";
    rosidl_generator_traits::value_to_yaml(msg.gear, out);
    out << "\n";
  }

  // member: braking
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "braking: ";
    rosidl_generator_traits::value_to_yaml(msg.braking, out);
    out << "\n";
  }

  // member: fault_bits
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fault_bits: ";
    rosidl_generator_traits::value_to_yaml(msg.fault_bits, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DriveStatus & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::DriveStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::DriveStatus & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::DriveStatus>()
{
  return "vehicle_core::msg::DriveStatus";
}

template<>
inline const char * name<vehicle_core::msg::DriveStatus>()
{
  return "vehicle_core/msg/DriveStatus";
}

template<>
struct has_fixed_size<vehicle_core::msg::DriveStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_core::msg::DriveStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_core::msg::DriveStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__TRAITS_HPP_
