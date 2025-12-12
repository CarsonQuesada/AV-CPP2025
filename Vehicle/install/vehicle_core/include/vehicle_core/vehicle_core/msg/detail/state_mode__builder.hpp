// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/StateMode.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__STATE_MODE__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__STATE_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/state_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_StateMode_mode
{
public:
  Init_StateMode_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_core::msg::StateMode mode(::vehicle_core::msg::StateMode::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::StateMode msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::StateMode>()
{
  return vehicle_core::msg::builder::Init_StateMode_mode();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__STATE_MODE__BUILDER_HPP_
