// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/MaxSpeed.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/max_speed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_MaxSpeed_percent
{
public:
  Init_MaxSpeed_percent()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_core::msg::MaxSpeed percent(::vehicle_core::msg::MaxSpeed::_percent_type arg)
  {
    msg_.percent = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::MaxSpeed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::MaxSpeed>()
{
  return vehicle_core::msg::builder::Init_MaxSpeed_percent();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__BUILDER_HPP_
