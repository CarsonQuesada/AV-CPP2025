// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:srv/ReleaseInternalControl.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__STRUCT_HPP_
#define VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Request __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Request __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ReleaseInternalControl_Request_
{
  using Type = ReleaseInternalControl_Request_<ContainerAllocator>;

  explicit ReleaseInternalControl_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->controller = "";
    }
  }

  explicit ReleaseInternalControl_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : controller(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->controller = "";
    }
  }

  // field types and members
  using _controller_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _controller_type controller;

  // setters for named parameter idiom
  Type & set__controller(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->controller = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Request
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Request
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReleaseInternalControl_Request_ & other) const
  {
    if (this->controller != other.controller) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReleaseInternalControl_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReleaseInternalControl_Request_

// alias to use template instance with default allocator
using ReleaseInternalControl_Request =
  vehicle_core::srv::ReleaseInternalControl_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_core


#ifndef _WIN32
# define DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Response __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Response __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ReleaseInternalControl_Response_
{
  using Type = ReleaseInternalControl_Response_<ContainerAllocator>;

  explicit ReleaseInternalControl_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit ReleaseInternalControl_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Response
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__srv__ReleaseInternalControl_Response
    std::shared_ptr<vehicle_core::srv::ReleaseInternalControl_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReleaseInternalControl_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReleaseInternalControl_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReleaseInternalControl_Response_

// alias to use template instance with default allocator
using ReleaseInternalControl_Response =
  vehicle_core::srv::ReleaseInternalControl_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_core

namespace vehicle_core
{

namespace srv
{

struct ReleaseInternalControl
{
  using Request = vehicle_core::srv::ReleaseInternalControl_Request;
  using Response = vehicle_core::srv::ReleaseInternalControl_Response;
};

}  // namespace srv

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__SRV__DETAIL__RELEASE_INTERNAL_CONTROL__STRUCT_HPP_
