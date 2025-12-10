// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:srv/ReleaseInternalControl.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__TRAITS_HPP_
#define VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/srv/detail/release_internal_control__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace srv
{

inline void to_flow_style_yaml(
  const ReleaseInternalControl_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: controller
  {
    out << "controller: ";
    rosidl_generator_traits::value_to_yaml(msg.controller, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ReleaseInternalControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: controller
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "controller: ";
    rosidl_generator_traits::value_to_yaml(msg.controller, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ReleaseInternalControl_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace vehicle_core

namespace rosidl_generator_traits
{

[[deprecated("use vehicle_core::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vehicle_core::srv::ReleaseInternalControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::srv::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::srv::ReleaseInternalControl_Request & msg)
{
  return vehicle_core::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::srv::ReleaseInternalControl_Request>()
{
  return "vehicle_core::srv::ReleaseInternalControl_Request";
}

template<>
inline const char * name<vehicle_core::srv::ReleaseInternalControl_Request>()
{
  return "vehicle_core/srv/ReleaseInternalControl_Request";
}

template<>
struct has_fixed_size<vehicle_core::srv::ReleaseInternalControl_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_core::srv::ReleaseInternalControl_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_core::srv::ReleaseInternalControl_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vehicle_core
{

namespace srv
{

inline void to_flow_style_yaml(
  const ReleaseInternalControl_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ReleaseInternalControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ReleaseInternalControl_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace vehicle_core

namespace rosidl_generator_traits
{

[[deprecated("use vehicle_core::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vehicle_core::srv::ReleaseInternalControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::srv::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::srv::ReleaseInternalControl_Response & msg)
{
  return vehicle_core::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::srv::ReleaseInternalControl_Response>()
{
  return "vehicle_core::srv::ReleaseInternalControl_Response";
}

template<>
inline const char * name<vehicle_core::srv::ReleaseInternalControl_Response>()
{
  return "vehicle_core/srv/ReleaseInternalControl_Response";
}

template<>
struct has_fixed_size<vehicle_core::srv::ReleaseInternalControl_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_core::srv::ReleaseInternalControl_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_core::srv::ReleaseInternalControl_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_core::srv::ReleaseInternalControl>()
{
  return "vehicle_core::srv::ReleaseInternalControl";
}

template<>
inline const char * name<vehicle_core::srv::ReleaseInternalControl>()
{
  return "vehicle_core/srv/ReleaseInternalControl";
}

template<>
struct has_fixed_size<vehicle_core::srv::ReleaseInternalControl>
  : std::integral_constant<
    bool,
    has_fixed_size<vehicle_core::srv::ReleaseInternalControl_Request>::value &&
    has_fixed_size<vehicle_core::srv::ReleaseInternalControl_Response>::value
  >
{
};

template<>
struct has_bounded_size<vehicle_core::srv::ReleaseInternalControl>
  : std::integral_constant<
    bool,
    has_bounded_size<vehicle_core::srv::ReleaseInternalControl_Request>::value &&
    has_bounded_size<vehicle_core::srv::ReleaseInternalControl_Response>::value
  >
{
};

template<>
struct is_service<vehicle_core::srv::ReleaseInternalControl>
  : std::true_type
{
};

template<>
struct is_service_request<vehicle_core::srv::ReleaseInternalControl_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vehicle_core::srv::ReleaseInternalControl_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__TRAITS_HPP_
