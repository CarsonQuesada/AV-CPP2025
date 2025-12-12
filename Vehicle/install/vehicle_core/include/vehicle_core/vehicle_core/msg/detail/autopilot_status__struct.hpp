// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/AutopilotStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__AutopilotStatus __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__AutopilotStatus __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AutopilotStatus_
{
  using Type = AutopilotStatus_<ContainerAllocator>;

  explicit AutopilotStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->autopilot_ready = false;
      this->lidar_ready = false;
      this->camera_ready = false;
    }
  }

  explicit AutopilotStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->autopilot_ready = false;
      this->lidar_ready = false;
      this->camera_ready = false;
    }
  }

  // field types and members
  using _autopilot_ready_type =
    bool;
  _autopilot_ready_type autopilot_ready;
  using _lidar_ready_type =
    bool;
  _lidar_ready_type lidar_ready;
  using _camera_ready_type =
    bool;
  _camera_ready_type camera_ready;

  // setters for named parameter idiom
  Type & set__autopilot_ready(
    const bool & _arg)
  {
    this->autopilot_ready = _arg;
    return *this;
  }
  Type & set__lidar_ready(
    const bool & _arg)
  {
    this->lidar_ready = _arg;
    return *this;
  }
  Type & set__camera_ready(
    const bool & _arg)
  {
    this->camera_ready = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::AutopilotStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::AutopilotStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::AutopilotStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::AutopilotStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__AutopilotStatus
    std::shared_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__AutopilotStatus
    std::shared_ptr<vehicle_core::msg::AutopilotStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AutopilotStatus_ & other) const
  {
    if (this->autopilot_ready != other.autopilot_ready) {
      return false;
    }
    if (this->lidar_ready != other.lidar_ready) {
      return false;
    }
    if (this->camera_ready != other.camera_ready) {
      return false;
    }
    return true;
  }
  bool operator!=(const AutopilotStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AutopilotStatus_

// alias to use template instance with default allocator
using AutopilotStatus =
  vehicle_core::msg::AutopilotStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_STATUS__STRUCT_HPP_
