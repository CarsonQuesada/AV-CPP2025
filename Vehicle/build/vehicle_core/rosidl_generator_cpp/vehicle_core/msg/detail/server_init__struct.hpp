// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'general_status'
#include "vehicle_core/msg/detail/general_status__struct.hpp"
// Member 'lights_status'
#include "vehicle_core/msg/detail/lights_status__struct.hpp"
// Member 'drive_status'
#include "vehicle_core/msg/detail/drive_status__struct.hpp"
// Member 'autopilot_status'
#include "vehicle_core/msg/detail/autopilot_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__ServerInit __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__ServerInit __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServerInit_
{
  using Type = ServerInit_<ContainerAllocator>;

  explicit ServerInit_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : general_status(_init),
    lights_status(_init),
    drive_status(_init),
    autopilot_status(_init)
  {
    (void)_init;
  }

  explicit ServerInit_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : general_status(_alloc, _init),
    lights_status(_alloc, _init),
    drive_status(_alloc, _init),
    autopilot_status(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _general_status_type =
    vehicle_core::msg::GeneralStatus_<ContainerAllocator>;
  _general_status_type general_status;
  using _lights_status_type =
    vehicle_core::msg::LightsStatus_<ContainerAllocator>;
  _lights_status_type lights_status;
  using _drive_status_type =
    vehicle_core::msg::DriveStatus_<ContainerAllocator>;
  _drive_status_type drive_status;
  using _autopilot_status_type =
    vehicle_core::msg::AutopilotStatus_<ContainerAllocator>;
  _autopilot_status_type autopilot_status;

  // setters for named parameter idiom
  Type & set__general_status(
    const vehicle_core::msg::GeneralStatus_<ContainerAllocator> & _arg)
  {
    this->general_status = _arg;
    return *this;
  }
  Type & set__lights_status(
    const vehicle_core::msg::LightsStatus_<ContainerAllocator> & _arg)
  {
    this->lights_status = _arg;
    return *this;
  }
  Type & set__drive_status(
    const vehicle_core::msg::DriveStatus_<ContainerAllocator> & _arg)
  {
    this->drive_status = _arg;
    return *this;
  }
  Type & set__autopilot_status(
    const vehicle_core::msg::AutopilotStatus_<ContainerAllocator> & _arg)
  {
    this->autopilot_status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::ServerInit_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::ServerInit_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::ServerInit_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::ServerInit_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__ServerInit
    std::shared_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__ServerInit
    std::shared_ptr<vehicle_core::msg::ServerInit_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServerInit_ & other) const
  {
    if (this->general_status != other.general_status) {
      return false;
    }
    if (this->lights_status != other.lights_status) {
      return false;
    }
    if (this->drive_status != other.drive_status) {
      return false;
    }
    if (this->autopilot_status != other.autopilot_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServerInit_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServerInit_

// alias to use template instance with default allocator
using ServerInit =
  vehicle_core::msg::ServerInit_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__SERVER_INIT__STRUCT_HPP_
