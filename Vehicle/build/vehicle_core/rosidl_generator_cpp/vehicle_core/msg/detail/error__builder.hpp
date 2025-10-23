// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/Error.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__ERROR__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/error__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_Error_code
{
public:
  Init_Error_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vehicle_core::msg::Error code(::vehicle_core::msg::Error::_code_type arg)
  {
    msg_.code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::Error msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::Error>()
{
  return vehicle_core::msg::builder::Init_Error_code();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__ERROR__BUILDER_HPP_
