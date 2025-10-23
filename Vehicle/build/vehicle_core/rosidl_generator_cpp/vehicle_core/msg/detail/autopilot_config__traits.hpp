// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/AutopilotConfig.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/autopilot_config__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const AutopilotConfig & msg,
  std::ostream & out)
{
  out << "{";
  // member: profile_id
  {
    out << "profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.profile_id, out);
    out << ", ";
  }

  // member: features_mask
  {
    out << "features_mask: ";
    rosidl_generator_traits::value_to_yaml(msg.features_mask, out);
    out << ", ";
  }

  // member: keys
  {
    if (msg.keys.size() == 0) {
      out << "keys: []";
    } else {
      out << "keys: [";
      size_t pending_items = msg.keys.size();
      for (auto item : msg.keys) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: values
  {
    if (msg.values.size() == 0) {
      out << "values: []";
    } else {
      out << "values: [";
      size_t pending_items = msg.values.size();
      for (auto item : msg.values) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AutopilotConfig & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: profile_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.profile_id, out);
    out << "\n";
  }

  // member: features_mask
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "features_mask: ";
    rosidl_generator_traits::value_to_yaml(msg.features_mask, out);
    out << "\n";
  }

  // member: keys
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.keys.size() == 0) {
      out << "keys: []\n";
    } else {
      out << "keys:\n";
      for (auto item : msg.keys) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: values
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.values.size() == 0) {
      out << "values: []\n";
    } else {
      out << "values:\n";
      for (auto item : msg.values) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AutopilotConfig & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::AutopilotConfig & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::AutopilotConfig & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::AutopilotConfig>()
{
  return "vehicle_core::msg::AutopilotConfig";
}

template<>
inline const char * name<vehicle_core::msg::AutopilotConfig>()
{
  return "vehicle_core/msg/AutopilotConfig";
}

template<>
struct has_fixed_size<vehicle_core::msg::AutopilotConfig>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_core::msg::AutopilotConfig>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_core::msg::AutopilotConfig>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__TRAITS_HPP_
