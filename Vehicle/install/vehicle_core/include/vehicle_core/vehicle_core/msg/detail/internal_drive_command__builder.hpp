// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/InternalDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/internal_drive_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_InternalDriveCommand_steer_rad
{
public:
  explicit Init_InternalDriveCommand_steer_rad(::vehicle_core::msg::InternalDriveCommand & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::InternalDriveCommand steer_rad(::vehicle_core::msg::InternalDriveCommand::_steer_rad_type arg)
  {
    msg_.steer_rad = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::InternalDriveCommand msg_;
};

class Init_InternalDriveCommand_speed_mps
{
public:
  explicit Init_InternalDriveCommand_speed_mps(::vehicle_core::msg::InternalDriveCommand & msg)
  : msg_(msg)
  {}
  Init_InternalDriveCommand_steer_rad speed_mps(::vehicle_core::msg::InternalDriveCommand::_speed_mps_type arg)
  {
    msg_.speed_mps = std::move(arg);
    return Init_InternalDriveCommand_steer_rad(msg_);
  }

private:
  ::vehicle_core::msg::InternalDriveCommand msg_;
};

class Init_InternalDriveCommand_gear
{
public:
  explicit Init_InternalDriveCommand_gear(::vehicle_core::msg::InternalDriveCommand & msg)
  : msg_(msg)
  {}
  Init_InternalDriveCommand_speed_mps gear(::vehicle_core::msg::InternalDriveCommand::_gear_type arg)
  {
    msg_.gear = std::move(arg);
    return Init_InternalDriveCommand_speed_mps(msg_);
  }

private:
  ::vehicle_core::msg::InternalDriveCommand msg_;
};

class Init_InternalDriveCommand_brake
{
public:
  explicit Init_InternalDriveCommand_brake(::vehicle_core::msg::InternalDriveCommand & msg)
  : msg_(msg)
  {}
  Init_InternalDriveCommand_gear brake(::vehicle_core::msg::InternalDriveCommand::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_InternalDriveCommand_gear(msg_);
  }

private:
  ::vehicle_core::msg::InternalDriveCommand msg_;
};

class Init_InternalDriveCommand_controller
{
public:
  explicit Init_InternalDriveCommand_controller(::vehicle_core::msg::InternalDriveCommand & msg)
  : msg_(msg)
  {}
  Init_InternalDriveCommand_brake controller(::vehicle_core::msg::InternalDriveCommand::_controller_type arg)
  {
    msg_.controller = std::move(arg);
    return Init_InternalDriveCommand_brake(msg_);
  }

private:
  ::vehicle_core::msg::InternalDriveCommand msg_;
};

class Init_InternalDriveCommand_stamp
{
public:
  Init_InternalDriveCommand_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InternalDriveCommand_controller stamp(::vehicle_core::msg::InternalDriveCommand::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_InternalDriveCommand_controller(msg_);
  }

private:
  ::vehicle_core::msg::InternalDriveCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::InternalDriveCommand>()
{
  return vehicle_core::msg::builder::Init_InternalDriveCommand_stamp();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__INTERNAL_DRIVE_COMMAND__BUILDER_HPP_
