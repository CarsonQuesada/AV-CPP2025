// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/StateEvent.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/state_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_StateEvent_reason
{
public:
  explicit Init_StateEvent_reason(::vehicle_core::msg::StateEvent & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::StateEvent reason(::vehicle_core::msg::StateEvent::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::StateEvent msg_;
};

class Init_StateEvent_to_mode
{
public:
  explicit Init_StateEvent_to_mode(::vehicle_core::msg::StateEvent & msg)
  : msg_(msg)
  {}
  Init_StateEvent_reason to_mode(::vehicle_core::msg::StateEvent::_to_mode_type arg)
  {
    msg_.to_mode = std::move(arg);
    return Init_StateEvent_reason(msg_);
  }

private:
  ::vehicle_core::msg::StateEvent msg_;
};

class Init_StateEvent_from_mode
{
public:
  explicit Init_StateEvent_from_mode(::vehicle_core::msg::StateEvent & msg)
  : msg_(msg)
  {}
  Init_StateEvent_to_mode from_mode(::vehicle_core::msg::StateEvent::_from_mode_type arg)
  {
    msg_.from_mode = std::move(arg);
    return Init_StateEvent_to_mode(msg_);
  }

private:
  ::vehicle_core::msg::StateEvent msg_;
};

class Init_StateEvent_stamp
{
public:
  Init_StateEvent_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StateEvent_from_mode stamp(::vehicle_core::msg::StateEvent::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_StateEvent_from_mode(msg_);
  }

private:
  ::vehicle_core::msg::StateEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::StateEvent>()
{
  return vehicle_core::msg::builder::Init_StateEvent_stamp();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__BUILDER_HPP_
