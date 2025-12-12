// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/ManualDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/manual_drive_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_ManualDriveCommand_steer
{
public:
  explicit Init_ManualDriveCommand_steer(::vehicle_core::msg::ManualDriveCommand & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::ManualDriveCommand steer(::vehicle_core::msg::ManualDriveCommand::_steer_type arg)
  {
    msg_.steer = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::ManualDriveCommand msg_;
};

class Init_ManualDriveCommand_speed
{
public:
  explicit Init_ManualDriveCommand_speed(::vehicle_core::msg::ManualDriveCommand & msg)
  : msg_(msg)
  {}
  Init_ManualDriveCommand_steer speed(::vehicle_core::msg::ManualDriveCommand::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_ManualDriveCommand_steer(msg_);
  }

private:
  ::vehicle_core::msg::ManualDriveCommand msg_;
};

class Init_ManualDriveCommand_gear
{
public:
  explicit Init_ManualDriveCommand_gear(::vehicle_core::msg::ManualDriveCommand & msg)
  : msg_(msg)
  {}
  Init_ManualDriveCommand_speed gear(::vehicle_core::msg::ManualDriveCommand::_gear_type arg)
  {
    msg_.gear = std::move(arg);
    return Init_ManualDriveCommand_speed(msg_);
  }

private:
  ::vehicle_core::msg::ManualDriveCommand msg_;
};

class Init_ManualDriveCommand_brake
{
public:
  Init_ManualDriveCommand_brake()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManualDriveCommand_gear brake(::vehicle_core::msg::ManualDriveCommand::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_ManualDriveCommand_gear(msg_);
  }

private:
  ::vehicle_core::msg::ManualDriveCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::ManualDriveCommand>()
{
  return vehicle_core::msg::builder::Init_ManualDriveCommand_brake();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__BUILDER_HPP_
