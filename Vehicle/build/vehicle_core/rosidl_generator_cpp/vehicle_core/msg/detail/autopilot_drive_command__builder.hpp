// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/AutopilotDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_DRIVE_COMMAND__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_DRIVE_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/autopilot_drive_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_AutopilotDriveCommand_steer_rad
{
public:
  explicit Init_AutopilotDriveCommand_steer_rad(::vehicle_core::msg::AutopilotDriveCommand & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::AutopilotDriveCommand steer_rad(::vehicle_core::msg::AutopilotDriveCommand::_steer_rad_type arg)
  {
    msg_.steer_rad = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotDriveCommand msg_;
};

class Init_AutopilotDriveCommand_speed_mps
{
public:
  explicit Init_AutopilotDriveCommand_speed_mps(::vehicle_core::msg::AutopilotDriveCommand & msg)
  : msg_(msg)
  {}
  Init_AutopilotDriveCommand_steer_rad speed_mps(::vehicle_core::msg::AutopilotDriveCommand::_speed_mps_type arg)
  {
    msg_.speed_mps = std::move(arg);
    return Init_AutopilotDriveCommand_steer_rad(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotDriveCommand msg_;
};

class Init_AutopilotDriveCommand_gear
{
public:
  explicit Init_AutopilotDriveCommand_gear(::vehicle_core::msg::AutopilotDriveCommand & msg)
  : msg_(msg)
  {}
  Init_AutopilotDriveCommand_speed_mps gear(::vehicle_core::msg::AutopilotDriveCommand::_gear_type arg)
  {
    msg_.gear = std::move(arg);
    return Init_AutopilotDriveCommand_speed_mps(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotDriveCommand msg_;
};

class Init_AutopilotDriveCommand_brake
{
public:
  Init_AutopilotDriveCommand_brake()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AutopilotDriveCommand_gear brake(::vehicle_core::msg::AutopilotDriveCommand::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_AutopilotDriveCommand_gear(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotDriveCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::AutopilotDriveCommand>()
{
  return vehicle_core::msg::builder::Init_AutopilotDriveCommand_brake();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_DRIVE_COMMAND__BUILDER_HPP_
