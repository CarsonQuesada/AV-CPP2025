// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/AutopilotCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_COMMAND__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/autopilot_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_AutopilotCommand_action
{
public:
  Init_AutopilotCommand_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_core::msg::AutopilotCommand action(::vehicle_core::msg::AutopilotCommand::_action_type arg)
  {
    msg_.action = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::AutopilotCommand>()
{
  return vehicle_core::msg::builder::Init_AutopilotCommand_action();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_COMMAND__BUILDER_HPP_
