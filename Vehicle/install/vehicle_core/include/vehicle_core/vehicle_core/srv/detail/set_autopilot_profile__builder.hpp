// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__BUILDER_HPP_
#define VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/srv/detail/set_autopilot_profile__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace srv
{

namespace builder
{

class Init_SetAutopilotProfile_Request_values
{
public:
  explicit Init_SetAutopilotProfile_Request_values(::vehicle_core::srv::SetAutopilotProfile_Request & msg)
  : msg_(msg)
  {}
  ::vehicle_core::srv::SetAutopilotProfile_Request values(::vehicle_core::srv::SetAutopilotProfile_Request::_values_type arg)
  {
    msg_.values = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Request msg_;
};

class Init_SetAutopilotProfile_Request_keys
{
public:
  explicit Init_SetAutopilotProfile_Request_keys(::vehicle_core::srv::SetAutopilotProfile_Request & msg)
  : msg_(msg)
  {}
  Init_SetAutopilotProfile_Request_values keys(::vehicle_core::srv::SetAutopilotProfile_Request::_keys_type arg)
  {
    msg_.keys = std::move(arg);
    return Init_SetAutopilotProfile_Request_values(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Request msg_;
};

class Init_SetAutopilotProfile_Request_set_params
{
public:
  explicit Init_SetAutopilotProfile_Request_set_params(::vehicle_core::srv::SetAutopilotProfile_Request & msg)
  : msg_(msg)
  {}
  Init_SetAutopilotProfile_Request_keys set_params(::vehicle_core::srv::SetAutopilotProfile_Request::_set_params_type arg)
  {
    msg_.set_params = std::move(arg);
    return Init_SetAutopilotProfile_Request_keys(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Request msg_;
};

class Init_SetAutopilotProfile_Request_features_mask
{
public:
  explicit Init_SetAutopilotProfile_Request_features_mask(::vehicle_core::srv::SetAutopilotProfile_Request & msg)
  : msg_(msg)
  {}
  Init_SetAutopilotProfile_Request_set_params features_mask(::vehicle_core::srv::SetAutopilotProfile_Request::_features_mask_type arg)
  {
    msg_.features_mask = std::move(arg);
    return Init_SetAutopilotProfile_Request_set_params(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Request msg_;
};

class Init_SetAutopilotProfile_Request_set_features_mask
{
public:
  explicit Init_SetAutopilotProfile_Request_set_features_mask(::vehicle_core::srv::SetAutopilotProfile_Request & msg)
  : msg_(msg)
  {}
  Init_SetAutopilotProfile_Request_features_mask set_features_mask(::vehicle_core::srv::SetAutopilotProfile_Request::_set_features_mask_type arg)
  {
    msg_.set_features_mask = std::move(arg);
    return Init_SetAutopilotProfile_Request_features_mask(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Request msg_;
};

class Init_SetAutopilotProfile_Request_profile_id
{
public:
  explicit Init_SetAutopilotProfile_Request_profile_id(::vehicle_core::srv::SetAutopilotProfile_Request & msg)
  : msg_(msg)
  {}
  Init_SetAutopilotProfile_Request_set_features_mask profile_id(::vehicle_core::srv::SetAutopilotProfile_Request::_profile_id_type arg)
  {
    msg_.profile_id = std::move(arg);
    return Init_SetAutopilotProfile_Request_set_features_mask(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Request msg_;
};

class Init_SetAutopilotProfile_Request_set_profile_id
{
public:
  Init_SetAutopilotProfile_Request_set_profile_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAutopilotProfile_Request_profile_id set_profile_id(::vehicle_core::srv::SetAutopilotProfile_Request::_set_profile_id_type arg)
  {
    msg_.set_profile_id = std::move(arg);
    return Init_SetAutopilotProfile_Request_profile_id(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::srv::SetAutopilotProfile_Request>()
{
  return vehicle_core::srv::builder::Init_SetAutopilotProfile_Request_set_profile_id();
}

}  // namespace vehicle_core


namespace vehicle_core
{

namespace srv
{

namespace builder
{

class Init_SetAutopilotProfile_Response_message
{
public:
  explicit Init_SetAutopilotProfile_Response_message(::vehicle_core::srv::SetAutopilotProfile_Response & msg)
  : msg_(msg)
  {}
  ::vehicle_core::srv::SetAutopilotProfile_Response message(::vehicle_core::srv::SetAutopilotProfile_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Response msg_;
};

class Init_SetAutopilotProfile_Response_success
{
public:
  Init_SetAutopilotProfile_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAutopilotProfile_Response_message success(::vehicle_core::srv::SetAutopilotProfile_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetAutopilotProfile_Response_message(msg_);
  }

private:
  ::vehicle_core::srv::SetAutopilotProfile_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::srv::SetAutopilotProfile_Response>()
{
  return vehicle_core::srv::builder::Init_SetAutopilotProfile_Response_success();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__BUILDER_HPP_
