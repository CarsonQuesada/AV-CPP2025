// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/AutopilotConfig.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__AutopilotConfig __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__AutopilotConfig __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AutopilotConfig_
{
  using Type = AutopilotConfig_<ContainerAllocator>;

  explicit AutopilotConfig_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->profile_id = 0;
      this->features_mask = 0;
    }
  }

  explicit AutopilotConfig_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->profile_id = 0;
      this->features_mask = 0;
    }
  }

  // field types and members
  using _profile_id_type =
    uint8_t;
  _profile_id_type profile_id;
  using _features_mask_type =
    uint8_t;
  _features_mask_type features_mask;
  using _keys_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _keys_type keys;
  using _values_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _values_type values;

  // setters for named parameter idiom
  Type & set__profile_id(
    const uint8_t & _arg)
  {
    this->profile_id = _arg;
    return *this;
  }
  Type & set__features_mask(
    const uint8_t & _arg)
  {
    this->features_mask = _arg;
    return *this;
  }
  Type & set__keys(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->keys = _arg;
    return *this;
  }
  Type & set__values(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->values = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::AutopilotConfig_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::AutopilotConfig_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::AutopilotConfig_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::AutopilotConfig_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__AutopilotConfig
    std::shared_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__AutopilotConfig
    std::shared_ptr<vehicle_core::msg::AutopilotConfig_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AutopilotConfig_ & other) const
  {
    if (this->profile_id != other.profile_id) {
      return false;
    }
    if (this->features_mask != other.features_mask) {
      return false;
    }
    if (this->keys != other.keys) {
      return false;
    }
    if (this->values != other.values) {
      return false;
    }
    return true;
  }
  bool operator!=(const AutopilotConfig_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AutopilotConfig_

// alias to use template instance with default allocator
using AutopilotConfig =
  vehicle_core::msg::AutopilotConfig_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__STRUCT_HPP_
