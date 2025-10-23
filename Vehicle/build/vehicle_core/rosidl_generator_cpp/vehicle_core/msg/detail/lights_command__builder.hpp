// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/LightsCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/lights_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_LightsCommand_light_id
{
public:
  Init_LightsCommand_light_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_core::msg::LightsCommand light_id(::vehicle_core::msg::LightsCommand::_light_id_type arg)
  {
    msg_.light_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::LightsCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::LightsCommand>()
{
  return vehicle_core::msg::builder::Init_LightsCommand_light_id();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__BUILDER_HPP_
