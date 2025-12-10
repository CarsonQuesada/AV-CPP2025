// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/DriveStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__DriveStatus __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__DriveStatus __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DriveStatus_
{
  using Type = DriveStatus_<ContainerAllocator>;

  explicit DriveStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->gear = 0;
      this->braking = false;
      this->fault_bits = 0;
    }
  }

  explicit DriveStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->gear = 0;
      this->braking = false;
      this->fault_bits = 0;
    }
  }

  // field types and members
  using _gear_type =
    uint8_t;
  _gear_type gear;
  using _braking_type =
    bool;
  _braking_type braking;
  using _fault_bits_type =
    uint16_t;
  _fault_bits_type fault_bits;

  // setters for named parameter idiom
  Type & set__gear(
    const uint8_t & _arg)
  {
    this->gear = _arg;
    return *this;
  }
  Type & set__braking(
    const bool & _arg)
  {
    this->braking = _arg;
    return *this;
  }
  Type & set__fault_bits(
    const uint16_t & _arg)
  {
    this->fault_bits = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::DriveStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::DriveStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::DriveStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::DriveStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__DriveStatus
    std::shared_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__DriveStatus
    std::shared_ptr<vehicle_core::msg::DriveStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DriveStatus_ & other) const
  {
    if (this->gear != other.gear) {
      return false;
    }
    if (this->braking != other.braking) {
      return false;
    }
    if (this->fault_bits != other.fault_bits) {
      return false;
    }
    return true;
  }
  bool operator!=(const DriveStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DriveStatus_

// alias to use template instance with default allocator
using DriveStatus =
  vehicle_core::msg::DriveStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__DRIVE_STATUS__STRUCT_HPP_
