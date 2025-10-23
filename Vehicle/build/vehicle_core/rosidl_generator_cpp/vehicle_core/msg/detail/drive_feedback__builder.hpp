// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/DriveFeedback.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/drive_feedback__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_DriveFeedback_steer_millirad
{
public:
  explicit Init_DriveFeedback_steer_millirad(::vehicle_core::msg::DriveFeedback & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::DriveFeedback steer_millirad(::vehicle_core::msg::DriveFeedback::_steer_millirad_type arg)
  {
    msg_.steer_millirad = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::DriveFeedback msg_;
};

class Init_DriveFeedback_speed_mmps
{
public:
  Init_DriveFeedback_speed_mmps()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveFeedback_steer_millirad speed_mmps(::vehicle_core::msg::DriveFeedback::_speed_mmps_type arg)
  {
    msg_.speed_mmps = std::move(arg);
    return Init_DriveFeedback_steer_millirad(msg_);
  }

private:
  ::vehicle_core::msg::DriveFeedback msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::DriveFeedback>()
{
  return vehicle_core::msg::builder::Init_DriveFeedback_speed_mmps();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__BUILDER_HPP_
