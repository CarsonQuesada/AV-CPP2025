// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__TRAITS_HPP_
#define VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/srv/detail/set_autopilot_profile__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_core
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetAutopilotProfile_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: set_profile_id
  {
    out << "set_profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.set_profile_id, out);
    out << ", ";
  }

  // member: profile_id
  {
    out << "profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.profile_id, out);
    out << ", ";
  }

  // member: set_features_mask
  {
    out << "set_features_mask: ";
    rosidl_generator_traits::value_to_yaml(msg.set_features_mask, out);
    out << ", ";
  }

  // member: features_mask
  {
    out << "features_mask: ";
    rosidl_generator_traits::value_to_yaml(msg.features_mask, out);
    out << ", ";
  }

  // member: set_params
  {
    out << "set_params: ";
    rosidl_generator_traits::value_to_yaml(msg.set_params, out);
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
  const SetAutopilotProfile_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: set_profile_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "set_profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.set_profile_id, out);
    out << "\n";
  }

  // member: profile_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.profile_id, out);
    out << "\n";
  }

  // member: set_features_mask
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "set_features_mask: ";
    rosidl_generator_traits::value_to_yaml(msg.set_features_mask, out);
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

  // member: set_params
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "set_params: ";
    rosidl_generator_traits::value_to_yaml(msg.set_params, out);
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

inline std::string to_yaml(const SetAutopilotProfile_Request & msg, bool use_flow_style = false)
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
  const vehicle_core::srv::SetAutopilotProfile_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::srv::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::srv::SetAutopilotProfile_Request & msg)
{
  return vehicle_core::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::srv::SetAutopilotProfile_Request>()
{
  return "vehicle_core::srv::SetAutopilotProfile_Request";
}

template<>
inline const char * name<vehicle_core::srv::SetAutopilotProfile_Request>()
{
  return "vehicle_core/srv/SetAutopilotProfile_Request";
}

template<>
struct has_fixed_size<vehicle_core::srv::SetAutopilotProfile_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_core::srv::SetAutopilotProfile_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_core::srv::SetAutopilotProfile_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vehicle_core
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetAutopilotProfile_Response & msg,
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
  const SetAutopilotProfile_Response & msg,
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

inline std::string to_yaml(const SetAutopilotProfile_Response & msg, bool use_flow_style = false)
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
  const vehicle_core::srv::SetAutopilotProfile_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::srv::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::srv::SetAutopilotProfile_Response & msg)
{
  return vehicle_core::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::srv::SetAutopilotProfile_Response>()
{
  return "vehicle_core::srv::SetAutopilotProfile_Response";
}

template<>
inline const char * name<vehicle_core::srv::SetAutopilotProfile_Response>()
{
  return "vehicle_core/srv/SetAutopilotProfile_Response";
}

template<>
struct has_fixed_size<vehicle_core::srv::SetAutopilotProfile_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_core::srv::SetAutopilotProfile_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_core::srv::SetAutopilotProfile_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vehicle_core::srv::SetAutopilotProfile>()
{
  return "vehicle_core::srv::SetAutopilotProfile";
}

template<>
inline const char * name<vehicle_core::srv::SetAutopilotProfile>()
{
  return "vehicle_core/srv/SetAutopilotProfile";
}

template<>
struct has_fixed_size<vehicle_core::srv::SetAutopilotProfile>
  : std::integral_constant<
    bool,
    has_fixed_size<vehicle_core::srv::SetAutopilotProfile_Request>::value &&
    has_fixed_size<vehicle_core::srv::SetAutopilotProfile_Response>::value
  >
{
};

template<>
struct has_bounded_size<vehicle_core::srv::SetAutopilotProfile>
  : std::integral_constant<
    bool,
    has_bounded_size<vehicle_core::srv::SetAutopilotProfile_Request>::value &&
    has_bounded_size<vehicle_core::srv::SetAutopilotProfile_Response>::value
  >
{
};

template<>
struct is_service<vehicle_core::srv::SetAutopilotProfile>
  : std::true_type
{
};

template<>
struct is_service_request<vehicle_core::srv::SetAutopilotProfile_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vehicle_core::srv::SetAutopilotProfile_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__TRAITS_HPP_
