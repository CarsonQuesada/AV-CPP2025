// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/DriveTarget.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__DriveTarget __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__DriveTarget __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DriveTarget_
{
  using Type = DriveTarget_<ContainerAllocator>;

  explicit DriveTarget_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake_percent = 0;
      this->target_speed_mmps = 0;
      this->target_steer_millirad = 0;
    }
  }

  explicit DriveTarget_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake_percent = 0;
      this->target_speed_mmps = 0;
      this->target_steer_millirad = 0;
    }
  }

  // field types and members
  using _brake_percent_type =
    uint8_t;
  _brake_percent_type brake_percent;
  using _target_speed_mmps_type =
    int16_t;
  _target_speed_mmps_type target_speed_mmps;
  using _target_steer_millirad_type =
    int16_t;
  _target_steer_millirad_type target_steer_millirad;

  // setters for named parameter idiom
  Type & set__brake_percent(
    const uint8_t & _arg)
  {
    this->brake_percent = _arg;
    return *this;
  }
  Type & set__target_speed_mmps(
    const int16_t & _arg)
  {
    this->target_speed_mmps = _arg;
    return *this;
  }
  Type & set__target_steer_millirad(
    const int16_t & _arg)
  {
    this->target_steer_millirad = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::DriveTarget_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::DriveTarget_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::DriveTarget_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::DriveTarget_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__DriveTarget
    std::shared_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__DriveTarget
    std::shared_ptr<vehicle_core::msg::DriveTarget_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DriveTarget_ & other) const
  {
    if (this->brake_percent != other.brake_percent) {
      return false;
    }
    if (this->target_speed_mmps != other.target_speed_mmps) {
      return false;
    }
    if (this->target_steer_millirad != other.target_steer_millirad) {
      return false;
    }
    return true;
  }
  bool operator!=(const DriveTarget_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DriveTarget_

// alias to use template instance with default allocator
using DriveTarget =
  vehicle_core::msg::DriveTarget_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_TARGET__STRUCT_HPP_
