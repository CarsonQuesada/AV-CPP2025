// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/PerceptionProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__PERCEPTION_PROFILE__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__PERCEPTION_PROFILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/perception_profile__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_PerceptionProfile_profile
{
public:
  Init_PerceptionProfile_profile()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_core::msg::PerceptionProfile profile(::vehicle_core::msg::PerceptionProfile::_profile_type arg)
  {
    msg_.profile = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::PerceptionProfile msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::PerceptionProfile>()
{
  return vehicle_core::msg::builder::Init_PerceptionProfile_profile();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__PERCEPTION_PROFILE__BUILDER_HPP_
