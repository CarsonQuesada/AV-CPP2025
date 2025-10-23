// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/GeneralStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/general_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_GeneralStatus_gps_online
{
public:
  explicit Init_GeneralStatus_gps_online(::vehicle_core::msg::GeneralStatus & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::GeneralStatus gps_online(::vehicle_core::msg::GeneralStatus::_gps_online_type arg)
  {
    msg_.gps_online = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::GeneralStatus msg_;
};

class Init_GeneralStatus_battery_percent
{
public:
  explicit Init_GeneralStatus_battery_percent(::vehicle_core::msg::GeneralStatus & msg)
  : msg_(msg)
  {}
  Init_GeneralStatus_gps_online battery_percent(::vehicle_core::msg::GeneralStatus::_battery_percent_type arg)
  {
    msg_.battery_percent = std::move(arg);
    return Init_GeneralStatus_gps_online(msg_);
  }

private:
  ::vehicle_core::msg::GeneralStatus msg_;
};

class Init_GeneralStatus_speed
{
public:
  Init_GeneralStatus_speed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GeneralStatus_battery_percent speed(::vehicle_core::msg::GeneralStatus::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_GeneralStatus_battery_percent(msg_);
  }

private:
  ::vehicle_core::msg::GeneralStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::GeneralStatus>()
{
  return vehicle_core::msg::builder::Init_GeneralStatus_speed();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__BUILDER_HPP_
