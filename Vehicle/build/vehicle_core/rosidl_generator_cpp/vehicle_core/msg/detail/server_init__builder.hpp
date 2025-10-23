// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/server_init__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_ServerInit_autopilot_status
{
public:
  explicit Init_ServerInit_autopilot_status(::vehicle_core::msg::ServerInit & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::ServerInit autopilot_status(::vehicle_core::msg::ServerInit::_autopilot_status_type arg)
  {
    msg_.autopilot_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::ServerInit msg_;
};

class Init_ServerInit_drive_status
{
public:
  explicit Init_ServerInit_drive_status(::vehicle_core::msg::ServerInit & msg)
  : msg_(msg)
  {}
  Init_ServerInit_autopilot_status drive_status(::vehicle_core::msg::ServerInit::_drive_status_type arg)
  {
    msg_.drive_status = std::move(arg);
    return Init_ServerInit_autopilot_status(msg_);
  }

private:
  ::vehicle_core::msg::ServerInit msg_;
};

class Init_ServerInit_lights_status
{
public:
  explicit Init_ServerInit_lights_status(::vehicle_core::msg::ServerInit & msg)
  : msg_(msg)
  {}
  Init_ServerInit_drive_status lights_status(::vehicle_core::msg::ServerInit::_lights_status_type arg)
  {
    msg_.lights_status = std::move(arg);
    return Init_ServerInit_drive_status(msg_);
  }

private:
  ::vehicle_core::msg::ServerInit msg_;
};

class Init_ServerInit_general_status
{
public:
  Init_ServerInit_general_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServerInit_lights_status general_status(::vehicle_core::msg::ServerInit::_general_status_type arg)
  {
    msg_.general_status = std::move(arg);
    return Init_ServerInit_lights_status(msg_);
  }

private:
  ::vehicle_core::msg::ServerInit msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::ServerInit>()
{
  return vehicle_core::msg::builder::Init_ServerInit_general_status();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__BUILDER_HPP_
