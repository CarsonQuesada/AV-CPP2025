// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__STRUCT_HPP_
#define VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Request __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Request __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAutopilotProfile_Request_
{
  using Type = SetAutopilotProfile_Request_<ContainerAllocator>;

  explicit SetAutopilotProfile_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->set_profile_id = false;
      this->profile_id = 0;
      this->set_features_mask = false;
      this->features_mask = 0;
      this->set_params = false;
    }
  }

  explicit SetAutopilotProfile_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->set_profile_id = false;
      this->profile_id = 0;
      this->set_features_mask = false;
      this->features_mask = 0;
      this->set_params = false;
    }
  }

  // field types and members
  using _set_profile_id_type =
    bool;
  _set_profile_id_type set_profile_id;
  using _profile_id_type =
    uint8_t;
  _profile_id_type profile_id;
  using _set_features_mask_type =
    bool;
  _set_features_mask_type set_features_mask;
  using _features_mask_type =
    uint8_t;
  _features_mask_type features_mask;
  using _set_params_type =
    bool;
  _set_params_type set_params;
  using _keys_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _keys_type keys;
  using _values_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _values_type values;

  // setters for named parameter idiom
  Type & set__set_profile_id(
    const bool & _arg)
  {
    this->set_profile_id = _arg;
    return *this;
  }
  Type & set__profile_id(
    const uint8_t & _arg)
  {
    this->profile_id = _arg;
    return *this;
  }
  Type & set__set_features_mask(
    const bool & _arg)
  {
    this->set_features_mask = _arg;
    return *this;
  }
  Type & set__features_mask(
    const uint8_t & _arg)
  {
    this->features_mask = _arg;
    return *this;
  }
  Type & set__set_params(
    const bool & _arg)
  {
    this->set_params = _arg;
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
    vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Request
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Request
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAutopilotProfile_Request_ & other) const
  {
    if (this->set_profile_id != other.set_profile_id) {
      return false;
    }
    if (this->profile_id != other.profile_id) {
      return false;
    }
    if (this->set_features_mask != other.set_features_mask) {
      return false;
    }
    if (this->features_mask != other.features_mask) {
      return false;
    }
    if (this->set_params != other.set_params) {
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
  bool operator!=(const SetAutopilotProfile_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAutopilotProfile_Request_

// alias to use template instance with default allocator
using SetAutopilotProfile_Request =
  vehicle_core::srv::SetAutopilotProfile_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_core


#ifndef _WIN32
# define DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Response __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Response __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAutopilotProfile_Response_
{
  using Type = SetAutopilotProfile_Response_<ContainerAllocator>;

  explicit SetAutopilotProfile_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetAutopilotProfile_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Response
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__srv__SetAutopilotProfile_Response
    std::shared_ptr<vehicle_core::srv::SetAutopilotProfile_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAutopilotProfile_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAutopilotProfile_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAutopilotProfile_Response_

// alias to use template instance with default allocator
using SetAutopilotProfile_Response =
  vehicle_core::srv::SetAutopilotProfile_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vehicle_core

namespace vehicle_core
{

namespace srv
{

struct SetAutopilotProfile
{
  using Request = vehicle_core::srv::SetAutopilotProfile_Request;
  using Response = vehicle_core::srv::SetAutopilotProfile_Response;
};

}  // namespace srv

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__STRUCT_HPP_
