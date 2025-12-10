// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:srv/ReleaseInternalControl.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__BUILDER_HPP_
#define VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/srv/detail/release_internal_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace srv
{

namespace builder
{

class Init_ReleaseInternalControl_Request_controller
{
public:
  Init_ReleaseInternalControl_Request_controller()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_core::srv::ReleaseInternalControl_Request controller(::vehicle_core::srv::ReleaseInternalControl_Request::_controller_type arg)
  {
    msg_.controller = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::srv::ReleaseInternalControl_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::srv::ReleaseInternalControl_Request>()
{
  return vehicle_core::srv::builder::Init_ReleaseInternalControl_Request_controller();
}

}  // namespace vehicle_core


namespace vehicle_core
{

namespace srv
{

namespace builder
{

class Init_ReleaseInternalControl_Response_message
{
public:
  explicit Init_ReleaseInternalControl_Response_message(::vehicle_core::srv::ReleaseInternalControl_Response & msg)
  : msg_(msg)
  {}
  ::vehicle_core::srv::ReleaseInternalControl_Response message(::vehicle_core::srv::ReleaseInternalControl_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::srv::ReleaseInternalControl_Response msg_;
};

class Init_ReleaseInternalControl_Response_success
{
public:
  Init_ReleaseInternalControl_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReleaseInternalControl_Response_message success(::vehicle_core::srv::ReleaseInternalControl_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ReleaseInternalControl_Response_message(msg_);
  }

private:
  ::vehicle_core::srv::ReleaseInternalControl_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::srv::ReleaseInternalControl_Response>()
{
  return vehicle_core::srv::builder::Init_ReleaseInternalControl_Response_success();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__BUILDER_HPP_
