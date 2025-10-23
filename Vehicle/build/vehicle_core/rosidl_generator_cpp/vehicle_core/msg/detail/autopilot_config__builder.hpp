// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/AutopilotConfig.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/autopilot_config__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_AutopilotConfig_values
{
public:
  explicit Init_AutopilotConfig_values(::vehicle_core::msg::AutopilotConfig & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::AutopilotConfig values(::vehicle_core::msg::AutopilotConfig::_values_type arg)
  {
    msg_.values = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotConfig msg_;
};

class Init_AutopilotConfig_keys
{
public:
  explicit Init_AutopilotConfig_keys(::vehicle_core::msg::AutopilotConfig & msg)
  : msg_(msg)
  {}
  Init_AutopilotConfig_values keys(::vehicle_core::msg::AutopilotConfig::_keys_type arg)
  {
    msg_.keys = std::move(arg);
    return Init_AutopilotConfig_values(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotConfig msg_;
};

class Init_AutopilotConfig_features_mask
{
public:
  explicit Init_AutopilotConfig_features_mask(::vehicle_core::msg::AutopilotConfig & msg)
  : msg_(msg)
  {}
  Init_AutopilotConfig_keys features_mask(::vehicle_core::msg::AutopilotConfig::_features_mask_type arg)
  {
    msg_.features_mask = std::move(arg);
    return Init_AutopilotConfig_keys(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotConfig msg_;
};

class Init_AutopilotConfig_profile_id
{
public:
  Init_AutopilotConfig_profile_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AutopilotConfig_features_mask profile_id(::vehicle_core::msg::AutopilotConfig::_profile_id_type arg)
  {
    msg_.profile_id = std::move(arg);
    return Init_AutopilotConfig_features_mask(msg_);
  }

private:
  ::vehicle_core::msg::AutopilotConfig msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::AutopilotConfig>()
{
  return vehicle_core::msg::builder::Init_AutopilotConfig_profile_id();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__BUILDER_HPP_
