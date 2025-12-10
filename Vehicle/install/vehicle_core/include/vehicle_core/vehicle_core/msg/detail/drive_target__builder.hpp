// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/DriveTarget.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/drive_target__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_DriveTarget_target_steer_millirad
{
public:
  explicit Init_DriveTarget_target_steer_millirad(::vehicle_core::msg::DriveTarget & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::DriveTarget target_steer_millirad(::vehicle_core::msg::DriveTarget::_target_steer_millirad_type arg)
  {
    msg_.target_steer_millirad = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::DriveTarget msg_;
};

class Init_DriveTarget_target_speed_mmps
{
public:
  explicit Init_DriveTarget_target_speed_mmps(::vehicle_core::msg::DriveTarget & msg)
  : msg_(msg)
  {}
  Init_DriveTarget_target_steer_millirad target_speed_mmps(::vehicle_core::msg::DriveTarget::_target_speed_mmps_type arg)
  {
    msg_.target_speed_mmps = std::move(arg);
    return Init_DriveTarget_target_steer_millirad(msg_);
  }

private:
  ::vehicle_core::msg::DriveTarget msg_;
};

class Init_DriveTarget_brake_percent
{
public:
  Init_DriveTarget_brake_percent()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveTarget_target_speed_mmps brake_percent(::vehicle_core::msg::DriveTarget::_brake_percent_type arg)
  {
    msg_.brake_percent = std::move(arg);
    return Init_DriveTarget_target_speed_mmps(msg_);
  }

private:
  ::vehicle_core::msg::DriveTarget msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::DriveTarget>()
{
  return vehicle_core::msg::builder::Init_DriveTarget_brake_percent();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__BUILDER_HPP_
