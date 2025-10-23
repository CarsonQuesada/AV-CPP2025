// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/TelemetryData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/telemetry_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const TelemetryData & msg,
  std::ostream & out)
{
  out << "{";
  // member: gps_online
  {
    out << "gps_online: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_online, out);
    out << ", ";
  }

  // member: lat
  {
    out << "lat: ";
    rosidl_generator_traits::value_to_yaml(msg.lat, out);
    out << ", ";
  }

  // member: lon
  {
    out << "lon: ";
    rosidl_generator_traits::value_to_yaml(msg.lon, out);
    out << ", ";
  }

  // member: heading
  {
    out << "heading: ";
    rosidl_generator_traits::value_to_yaml(msg.heading, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << ", ";
  }

  // member: distance_delta
  {
    out << "distance_delta: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_delta, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TelemetryData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: gps_online
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_online: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_online, out);
    out << "\n";
  }

  // member: lat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lat: ";
    rosidl_generator_traits::value_to_yaml(msg.lat, out);
    out << "\n";
  }

  // member: lon
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lon: ";
    rosidl_generator_traits::value_to_yaml(msg.lon, out);
    out << "\n";
  }

  // member: heading
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading: ";
    rosidl_generator_traits::value_to_yaml(msg.heading, out);
    out << "\n";
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }

  // member: distance_delta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance_delta: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_delta, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TelemetryData & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::TelemetryData & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::TelemetryData & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::TelemetryData>()
{
  return "vehicle_core::msg::TelemetryData";
}

template<>
inline const char * name<vehicle_core::msg::TelemetryData>()
{
  return "vehicle_core/msg/TelemetryData";
}

template<>
struct has_fixed_size<vehicle_core::msg::TelemetryData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_core::msg::TelemetryData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_core::msg::TelemetryData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__TRAITS_HPP_
