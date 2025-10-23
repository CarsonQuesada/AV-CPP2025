// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/GeneralStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/general_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const GeneralStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << ", ";
  }

  // member: battery_percent
  {
    out << "battery_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_percent, out);
    out << ", ";
  }

  // member: gps_online
  {
    out << "gps_online: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_online, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GeneralStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }

  // member: battery_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_percent, out);
    out << "\n";
  }

  // member: gps_online
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_online: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_online, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GeneralStatus & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::GeneralStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::GeneralStatus & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::GeneralStatus>()
{
  return "vehicle_core::msg::GeneralStatus";
}

template<>
inline const char * name<vehicle_core::msg::GeneralStatus>()
{
  return "vehicle_core/msg/GeneralStatus";
}

template<>
struct has_fixed_size<vehicle_core::msg::GeneralStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_core::msg::GeneralStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_core::msg::GeneralStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__TRAITS_HPP_
