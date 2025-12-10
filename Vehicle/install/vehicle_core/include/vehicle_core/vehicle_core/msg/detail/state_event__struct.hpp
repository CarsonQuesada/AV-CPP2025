// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/StateEvent.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__StateEvent __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__StateEvent __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StateEvent_
{
  using Type = StateEvent_<ContainerAllocator>;

  explicit StateEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->from_mode = 0;
      this->to_mode = 0;
      this->reason = "";
    }
  }

  explicit StateEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->from_mode = 0;
      this->to_mode = 0;
      this->reason = "";
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _from_mode_type =
    uint8_t;
  _from_mode_type from_mode;
  using _to_mode_type =
    uint8_t;
  _to_mode_type to_mode;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__from_mode(
    const uint8_t & _arg)
  {
    this->from_mode = _arg;
    return *this;
  }
  Type & set__to_mode(
    const uint8_t & _arg)
  {
    this->to_mode = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::StateEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::StateEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::StateEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::StateEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__StateEvent
    std::shared_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__StateEvent
    std::shared_ptr<vehicle_core::msg::StateEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StateEvent_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->from_mode != other.from_mode) {
      return false;
    }
    if (this->to_mode != other.to_mode) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const StateEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StateEvent_

// alias to use template instance with default allocator
using StateEvent =
  vehicle_core::msg::StateEvent_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__STATE_EVENT__STRUCT_HPP_
