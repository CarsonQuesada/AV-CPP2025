// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/ManualDriveCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__ManualDriveCommand __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__ManualDriveCommand __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ManualDriveCommand_
{
  using Type = ManualDriveCommand_<ContainerAllocator>;

  explicit ManualDriveCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake = 0;
      this->gear = 0;
      this->speed = 0;
      this->steer = 0;
    }
  }

  explicit ManualDriveCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake = 0;
      this->gear = 0;
      this->speed = 0;
      this->steer = 0;
    }
  }

  // field types and members
  using _brake_type =
    uint8_t;
  _brake_type brake;
  using _gear_type =
    uint8_t;
  _gear_type gear;
  using _speed_type =
    uint8_t;
  _speed_type speed;
  using _steer_type =
    uint8_t;
  _steer_type steer;

  // setters for named parameter idiom
  Type & set__brake(
    const uint8_t & _arg)
  {
    this->brake = _arg;
    return *this;
  }
  Type & set__gear(
    const uint8_t & _arg)
  {
    this->gear = _arg;
    return *this;
  }
  Type & set__speed(
    const uint8_t & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__steer(
    const uint8_t & _arg)
  {
    this->steer = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::ManualDriveCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::ManualDriveCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::ManualDriveCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::ManualDriveCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__ManualDriveCommand
    std::shared_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__ManualDriveCommand
    std::shared_ptr<vehicle_core::msg::ManualDriveCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ManualDriveCommand_ & other) const
  {
    if (this->brake != other.brake) {
      return false;
    }
    if (this->gear != other.gear) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    if (this->steer != other.steer) {
      return false;
    }
    return true;
  }
  bool operator!=(const ManualDriveCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ManualDriveCommand_

// alias to use template instance with default allocator
using ManualDriveCommand =
  vehicle_core::msg::ManualDriveCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__MANUAL_DRIVE_COMMAND__STRUCT_HPP_
