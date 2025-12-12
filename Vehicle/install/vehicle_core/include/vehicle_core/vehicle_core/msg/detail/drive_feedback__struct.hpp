// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/DriveFeedback.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__DriveFeedback __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__DriveFeedback __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DriveFeedback_
{
  using Type = DriveFeedback_<ContainerAllocator>;

  explicit DriveFeedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed_mmps = 0;
      this->steer_millirad = 0;
    }
  }

  explicit DriveFeedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed_mmps = 0;
      this->steer_millirad = 0;
    }
  }

  // field types and members
  using _speed_mmps_type =
    int16_t;
  _speed_mmps_type speed_mmps;
  using _steer_millirad_type =
    int16_t;
  _steer_millirad_type steer_millirad;

  // setters for named parameter idiom
  Type & set__speed_mmps(
    const int16_t & _arg)
  {
    this->speed_mmps = _arg;
    return *this;
  }
  Type & set__steer_millirad(
    const int16_t & _arg)
  {
    this->steer_millirad = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::DriveFeedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::DriveFeedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::DriveFeedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::DriveFeedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__DriveFeedback
    std::shared_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__DriveFeedback
    std::shared_ptr<vehicle_core::msg::DriveFeedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DriveFeedback_ & other) const
  {
    if (this->speed_mmps != other.speed_mmps) {
      return false;
    }
    if (this->steer_millirad != other.steer_millirad) {
      return false;
    }
    return true;
  }
  bool operator!=(const DriveFeedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DriveFeedback_

// alias to use template instance with default allocator
using DriveFeedback =
  vehicle_core::msg::DriveFeedback_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_FEEDBACK__STRUCT_HPP_
