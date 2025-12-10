// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/DriveStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/drive_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_DriveStatus_fault_bits
{
public:
  explicit Init_DriveStatus_fault_bits(::vehicle_core::msg::DriveStatus & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::DriveStatus fault_bits(::vehicle_core::msg::DriveStatus::_fault_bits_type arg)
  {
    msg_.fault_bits = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::DriveStatus msg_;
};

class Init_DriveStatus_braking
{
public:
  explicit Init_DriveStatus_braking(::vehicle_core::msg::DriveStatus & msg)
  : msg_(msg)
  {}
  Init_DriveStatus_fault_bits braking(::vehicle_core::msg::DriveStatus::_braking_type arg)
  {
    msg_.braking = std::move(arg);
    return Init_DriveStatus_fault_bits(msg_);
  }

private:
  ::vehicle_core::msg::DriveStatus msg_;
};

class Init_DriveStatus_gear
{
public:
  Init_DriveStatus_gear()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveStatus_braking gear(::vehicle_core::msg::DriveStatus::_gear_type arg)
  {
    msg_.gear = std::move(arg);
    return Init_DriveStatus_braking(msg_);
  }

private:
  ::vehicle_core::msg::DriveStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::DriveStatus>()
{
  return vehicle_core::msg::builder::Init_DriveStatus_gear();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__BUILDER_HPP_
