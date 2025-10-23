// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/AutopilotStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/autopilot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_AutopilotStatus_camera_ready
{
public:
  explicit Init_AutopilotStatus_camera_ready(::vehicle_core::msg::AutopilotStatus & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::AutopilotStatus camera_ready(::vehicle_core::msg::AutopilotStatus::_camera_ready_type arg)
  {
    msg_.camera_ready = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotStatus msg_;
};

class Init_AutopilotStatus_lidar_ready
{
public:
  explicit Init_AutopilotStatus_lidar_ready(::vehicle_core::msg::AutopilotStatus & msg)
  : msg_(msg)
  {}
  Init_AutopilotStatus_camera_ready lidar_ready(::vehicle_core::msg::AutopilotStatus::_lidar_ready_type arg)
  {
    msg_.lidar_ready = std::move(arg);
    return Init_AutopilotStatus_camera_ready(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotStatus msg_;
};

class Init_AutopilotStatus_autopilot_ready
{
public:
  Init_AutopilotStatus_autopilot_ready()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AutopilotStatus_lidar_ready autopilot_ready(::vehicle_core::msg::AutopilotStatus::_autopilot_ready_type arg)
  {
    msg_.autopilot_ready = std::move(arg);
    return Init_AutopilotStatus_lidar_ready(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::AutopilotStatus>()
{
  return vehicle_core::msg::builder::Init_AutopilotStatus_autopilot_ready();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__BUILDER_HPP_
