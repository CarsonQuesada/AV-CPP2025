// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/IMUStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/imu_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_IMUStatus_err_code
{
public:
  explicit Init_IMUStatus_err_code(::vehicle_core::msg::IMUStatus & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::IMUStatus err_code(::vehicle_core::msg::IMUStatus::_err_code_type arg)
  {
    msg_.err_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

class Init_IMUStatus_op_mode
{
public:
  explicit Init_IMUStatus_op_mode(::vehicle_core::msg::IMUStatus & msg)
  : msg_(msg)
  {}
  Init_IMUStatus_err_code op_mode(::vehicle_core::msg::IMUStatus::_op_mode_type arg)
  {
    msg_.op_mode = std::move(arg);
    return Init_IMUStatus_err_code(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

class Init_IMUStatus_calib_mag
{
public:
  explicit Init_IMUStatus_calib_mag(::vehicle_core::msg::IMUStatus & msg)
  : msg_(msg)
  {}
  Init_IMUStatus_op_mode calib_mag(::vehicle_core::msg::IMUStatus::_calib_mag_type arg)
  {
    msg_.calib_mag = std::move(arg);
    return Init_IMUStatus_op_mode(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

class Init_IMUStatus_calib_accel
{
public:
  explicit Init_IMUStatus_calib_accel(::vehicle_core::msg::IMUStatus & msg)
  : msg_(msg)
  {}
  Init_IMUStatus_calib_mag calib_accel(::vehicle_core::msg::IMUStatus::_calib_accel_type arg)
  {
    msg_.calib_accel = std::move(arg);
    return Init_IMUStatus_calib_mag(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

class Init_IMUStatus_calib_gyro
{
public:
  explicit Init_IMUStatus_calib_gyro(::vehicle_core::msg::IMUStatus & msg)
  : msg_(msg)
  {}
  Init_IMUStatus_calib_accel calib_gyro(::vehicle_core::msg::IMUStatus::_calib_gyro_type arg)
  {
    msg_.calib_gyro = std::move(arg);
    return Init_IMUStatus_calib_accel(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

class Init_IMUStatus_calib_sys
{
public:
  explicit Init_IMUStatus_calib_sys(::vehicle_core::msg::IMUStatus & msg)
  : msg_(msg)
  {}
  Init_IMUStatus_calib_gyro calib_sys(::vehicle_core::msg::IMUStatus::_calib_sys_type arg)
  {
    msg_.calib_sys = std::move(arg);
    return Init_IMUStatus_calib_gyro(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

class Init_IMUStatus_imu_data_ok
{
public:
  explicit Init_IMUStatus_imu_data_ok(::vehicle_core::msg::IMUStatus & msg)
  : msg_(msg)
  {}
  Init_IMUStatus_calib_sys imu_data_ok(::vehicle_core::msg::IMUStatus::_imu_data_ok_type arg)
  {
    msg_.imu_data_ok = std::move(arg);
    return Init_IMUStatus_calib_sys(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

class Init_IMUStatus_header
{
public:
  Init_IMUStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IMUStatus_imu_data_ok header(::vehicle_core::msg::IMUStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_IMUStatus_imu_data_ok(msg_);
  }

private:
  ::vehicle_core::msg::IMUStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::IMUStatus>()
{
  return vehicle_core::msg::builder::Init_IMUStatus_header();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__BUILDER_HPP_
