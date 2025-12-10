// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_core:msg/IMUStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__TRAITS_HPP_
#define VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_core/msg/detail/imu_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace vehicle_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const IMUStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: imu_data_ok
  {
    out << "imu_data_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.imu_data_ok, out);
    out << ", ";
  }

  // member: calib_sys
  {
    out << "calib_sys: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_sys, out);
    out << ", ";
  }

  // member: calib_gyro
  {
    out << "calib_gyro: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_gyro, out);
    out << ", ";
  }

  // member: calib_accel
  {
    out << "calib_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_accel, out);
    out << ", ";
  }

  // member: calib_mag
  {
    out << "calib_mag: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_mag, out);
    out << ", ";
  }

  // member: op_mode
  {
    out << "op_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.op_mode, out);
    out << ", ";
  }

  // member: err_code
  {
    out << "err_code: ";
    rosidl_generator_traits::value_to_yaml(msg.err_code, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const IMUStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: imu_data_ok
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "imu_data_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.imu_data_ok, out);
    out << "\n";
  }

  // member: calib_sys
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calib_sys: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_sys, out);
    out << "\n";
  }

  // member: calib_gyro
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calib_gyro: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_gyro, out);
    out << "\n";
  }

  // member: calib_accel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calib_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_accel, out);
    out << "\n";
  }

  // member: calib_mag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calib_mag: ";
    rosidl_generator_traits::value_to_yaml(msg.calib_mag, out);
    out << "\n";
  }

  // member: op_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "op_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.op_mode, out);
    out << "\n";
  }

  // member: err_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "err_code: ";
    rosidl_generator_traits::value_to_yaml(msg.err_code, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const IMUStatus & msg, bool use_flow_style = false)
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
  const vehicle_core::msg::IMUStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_core::msg::IMUStatus & msg)
{
  return vehicle_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_core::msg::IMUStatus>()
{
  return "vehicle_core::msg::IMUStatus";
}

template<>
inline const char * name<vehicle_core::msg::IMUStatus>()
{
  return "vehicle_core/msg/IMUStatus";
}

template<>
struct has_fixed_size<vehicle_core::msg::IMUStatus>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<vehicle_core::msg::IMUStatus>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<vehicle_core::msg::IMUStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__TRAITS_HPP_
