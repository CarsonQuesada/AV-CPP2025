// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/LightsStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/lights_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_LightsStatus_hazards
{
public:
  explicit Init_LightsStatus_hazards(::vehicle_core::msg::LightsStatus & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::LightsStatus hazards(::vehicle_core::msg::LightsStatus::_hazards_type arg)
  {
    msg_.hazards = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::LightsStatus msg_;
};

class Init_LightsStatus_headlights
{
public:
  explicit Init_LightsStatus_headlights(::vehicle_core::msg::LightsStatus & msg)
  : msg_(msg)
  {}
  Init_LightsStatus_hazards headlights(::vehicle_core::msg::LightsStatus::_headlights_type arg)
  {
    msg_.headlights = std::move(arg);
    return Init_LightsStatus_hazards(msg_);
  }

private:
  ::vehicle_core::msg::LightsStatus msg_;
};

class Init_LightsStatus_left_sig
{
public:
  explicit Init_LightsStatus_left_sig(::vehicle_core::msg::LightsStatus & msg)
  : msg_(msg)
  {}
  Init_LightsStatus_headlights left_sig(::vehicle_core::msg::LightsStatus::_left_sig_type arg)
  {
    msg_.left_sig = std::move(arg);
    return Init_LightsStatus_headlights(msg_);
  }

private:
  ::vehicle_core::msg::LightsStatus msg_;
};

class Init_LightsStatus_right_sig
{
public:
  explicit Init_LightsStatus_right_sig(::vehicle_core::msg::LightsStatus & msg)
  : msg_(msg)
  {}
  Init_LightsStatus_left_sig right_sig(::vehicle_core::msg::LightsStatus::_right_sig_type arg)
  {
    msg_.right_sig = std::move(arg);
    return Init_LightsStatus_left_sig(msg_);
  }

private:
  ::vehicle_core::msg::LightsStatus msg_;
};

class Init_LightsStatus_reverse_lights
{
public:
  explicit Init_LightsStatus_reverse_lights(::vehicle_core::msg::LightsStatus & msg)
  : msg_(msg)
  {}
  Init_LightsStatus_right_sig reverse_lights(::vehicle_core::msg::LightsStatus::_reverse_lights_type arg)
  {
    msg_.reverse_lights = std::move(arg);
    return Init_LightsStatus_right_sig(msg_);
  }

private:
  ::vehicle_core::msg::LightsStatus msg_;
};

class Init_LightsStatus_brake_lights
{
public:
  Init_LightsStatus_brake_lights()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LightsStatus_reverse_lights brake_lights(::vehicle_core::msg::LightsStatus::_brake_lights_type arg)
  {
    msg_.brake_lights = std::move(arg);
    return Init_LightsStatus_reverse_lights(msg_);
  }

private:
  ::vehicle_core::msg::LightsStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::LightsStatus>()
{
  return vehicle_core::msg::builder::Init_LightsStatus_brake_lights();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__BUILDER_HPP_
