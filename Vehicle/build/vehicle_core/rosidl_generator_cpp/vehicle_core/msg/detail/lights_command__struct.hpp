// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/LightsCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__LightsCommand __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__LightsCommand __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LightsCommand_
{
  using Type = LightsCommand_<ContainerAllocator>;

  explicit LightsCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->light_id = 0;
    }
  }

  explicit LightsCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->light_id = 0;
    }
  }

  // field types and members
  using _light_id_type =
    uint8_t;
  _light_id_type light_id;

  // setters for named parameter idiom
  Type & set__light_id(
    const uint8_t & _arg)
  {
    this->light_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::LightsCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::LightsCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::LightsCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::LightsCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__LightsCommand
    std::shared_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__LightsCommand
    std::shared_ptr<vehicle_core::msg::LightsCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LightsCommand_ & other) const
  {
    if (this->light_id != other.light_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const LightsCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LightsCommand_

// alias to use template instance with default allocator
using LightsCommand =
  vehicle_core::msg::LightsCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__LIGHTS_COMMAND__STRUCT_HPP_
