// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/LightsStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__LightsStatus __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__LightsStatus __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LightsStatus_
{
  using Type = LightsStatus_<ContainerAllocator>;

  explicit LightsStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake_lights = 0;
      this->reverse_lights = 0;
      this->right_sig = 0;
      this->left_sig = 0;
      this->headlights = 0;
      this->hazards = 0;
    }
  }

  explicit LightsStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->brake_lights = 0;
      this->reverse_lights = 0;
      this->right_sig = 0;
      this->left_sig = 0;
      this->headlights = 0;
      this->hazards = 0;
    }
  }

  // field types and members
  using _brake_lights_type =
    uint8_t;
  _brake_lights_type brake_lights;
  using _reverse_lights_type =
    uint8_t;
  _reverse_lights_type reverse_lights;
  using _right_sig_type =
    uint8_t;
  _right_sig_type right_sig;
  using _left_sig_type =
    uint8_t;
  _left_sig_type left_sig;
  using _headlights_type =
    uint8_t;
  _headlights_type headlights;
  using _hazards_type =
    uint8_t;
  _hazards_type hazards;

  // setters for named parameter idiom
  Type & set__brake_lights(
    const uint8_t & _arg)
  {
    this->brake_lights = _arg;
    return *this;
  }
  Type & set__reverse_lights(
    const uint8_t & _arg)
  {
    this->reverse_lights = _arg;
    return *this;
  }
  Type & set__right_sig(
    const uint8_t & _arg)
  {
    this->right_sig = _arg;
    return *this;
  }
  Type & set__left_sig(
    const uint8_t & _arg)
  {
    this->left_sig = _arg;
    return *this;
  }
  Type & set__headlights(
    const uint8_t & _arg)
  {
    this->headlights = _arg;
    return *this;
  }
  Type & set__hazards(
    const uint8_t & _arg)
  {
    this->hazards = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::LightsStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::LightsStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::LightsStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::LightsStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__LightsStatus
    std::shared_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__LightsStatus
    std::shared_ptr<vehicle_core::msg::LightsStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LightsStatus_ & other) const
  {
    if (this->brake_lights != other.brake_lights) {
      return false;
    }
    if (this->reverse_lights != other.reverse_lights) {
      return false;
    }
    if (this->right_sig != other.right_sig) {
      return false;
    }
    if (this->left_sig != other.left_sig) {
      return false;
    }
    if (this->headlights != other.headlights) {
      return false;
    }
    if (this->hazards != other.hazards) {
      return false;
    }
    return true;
  }
  bool operator!=(const LightsStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LightsStatus_

// alias to use template instance with default allocator
using LightsStatus =
  vehicle_core::msg::LightsStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__LIGHTS_STATUS__STRUCT_HPP_
