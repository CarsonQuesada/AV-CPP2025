// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/StateMode.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__STATE_MODE__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__STATE_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__StateMode __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__StateMode __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StateMode_
{
  using Type = StateMode_<ContainerAllocator>;

  explicit StateMode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
    }
  }

  explicit StateMode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
    }
  }

  // field types and members
  using _mode_type =
    uint8_t;
  _mode_type mode;

  // setters for named parameter idiom
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::StateMode_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::StateMode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::StateMode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::StateMode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::StateMode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::StateMode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::StateMode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::StateMode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::StateMode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::StateMode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__StateMode
    std::shared_ptr<vehicle_core::msg::StateMode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__StateMode
    std::shared_ptr<vehicle_core::msg::StateMode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StateMode_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const StateMode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StateMode_

// alias to use template instance with default allocator
using StateMode =
  vehicle_core::msg::StateMode_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__STATE_MODE__STRUCT_HPP_
