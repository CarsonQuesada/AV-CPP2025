// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/GeneralStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__GeneralStatus __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__GeneralStatus __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GeneralStatus_
{
  using Type = GeneralStatus_<ContainerAllocator>;

  explicit GeneralStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed = 0ul;
      this->battery_percent = 0ul;
      this->gps_online = false;
    }
  }

  explicit GeneralStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed = 0ul;
      this->battery_percent = 0ul;
      this->gps_online = false;
    }
  }

  // field types and members
  using _speed_type =
    uint32_t;
  _speed_type speed;
  using _battery_percent_type =
    uint32_t;
  _battery_percent_type battery_percent;
  using _gps_online_type =
    bool;
  _gps_online_type gps_online;

  // setters for named parameter idiom
  Type & set__speed(
    const uint32_t & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__battery_percent(
    const uint32_t & _arg)
  {
    this->battery_percent = _arg;
    return *this;
  }
  Type & set__gps_online(
    const bool & _arg)
  {
    this->gps_online = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::GeneralStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::GeneralStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::GeneralStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::GeneralStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__GeneralStatus
    std::shared_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__GeneralStatus
    std::shared_ptr<vehicle_core::msg::GeneralStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GeneralStatus_ & other) const
  {
    if (this->speed != other.speed) {
      return false;
    }
    if (this->battery_percent != other.battery_percent) {
      return false;
    }
    if (this->gps_online != other.gps_online) {
      return false;
    }
    return true;
  }
  bool operator!=(const GeneralStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GeneralStatus_

// alias to use template instance with default allocator
using GeneralStatus =
  vehicle_core::msg::GeneralStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__GENERAL_STATUS__STRUCT_HPP_
