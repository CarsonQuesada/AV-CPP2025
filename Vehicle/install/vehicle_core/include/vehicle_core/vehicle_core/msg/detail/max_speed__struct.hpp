// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/MaxSpeed.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__MaxSpeed __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__MaxSpeed __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MaxSpeed_
{
  using Type = MaxSpeed_<ContainerAllocator>;

  explicit MaxSpeed_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->percent = 0;
    }
  }

  explicit MaxSpeed_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->percent = 0;
    }
  }

  // field types and members
  using _percent_type =
    uint8_t;
  _percent_type percent;

  // setters for named parameter idiom
  Type & set__percent(
    const uint8_t & _arg)
  {
    this->percent = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::MaxSpeed_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::MaxSpeed_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::MaxSpeed_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::MaxSpeed_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__MaxSpeed
    std::shared_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__MaxSpeed
    std::shared_ptr<vehicle_core::msg::MaxSpeed_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MaxSpeed_ & other) const
  {
    if (this->percent != other.percent) {
      return false;
    }
    return true;
  }
  bool operator!=(const MaxSpeed_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MaxSpeed_

// alias to use template instance with default allocator
using MaxSpeed =
  vehicle_core::msg::MaxSpeed_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__STRUCT_HPP_
