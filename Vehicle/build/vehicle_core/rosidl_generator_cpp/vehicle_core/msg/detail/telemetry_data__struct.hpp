// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/TelemetryData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__TelemetryData __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__TelemetryData __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TelemetryData_
{
  using Type = TelemetryData_<ContainerAllocator>;

  explicit TelemetryData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->gps_online = false;
      this->lat = 0.0f;
      this->lon = 0.0f;
      this->heading = 0.0f;
      this->speed = 0.0f;
      this->distance_delta = 0.0f;
    }
  }

  explicit TelemetryData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->gps_online = false;
      this->lat = 0.0f;
      this->lon = 0.0f;
      this->heading = 0.0f;
      this->speed = 0.0f;
      this->distance_delta = 0.0f;
    }
  }

  // field types and members
  using _gps_online_type =
    bool;
  _gps_online_type gps_online;
  using _lat_type =
    float;
  _lat_type lat;
  using _lon_type =
    float;
  _lon_type lon;
  using _heading_type =
    float;
  _heading_type heading;
  using _speed_type =
    float;
  _speed_type speed;
  using _distance_delta_type =
    float;
  _distance_delta_type distance_delta;

  // setters for named parameter idiom
  Type & set__gps_online(
    const bool & _arg)
  {
    this->gps_online = _arg;
    return *this;
  }
  Type & set__lat(
    const float & _arg)
  {
    this->lat = _arg;
    return *this;
  }
  Type & set__lon(
    const float & _arg)
  {
    this->lon = _arg;
    return *this;
  }
  Type & set__heading(
    const float & _arg)
  {
    this->heading = _arg;
    return *this;
  }
  Type & set__speed(
    const float & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__distance_delta(
    const float & _arg)
  {
    this->distance_delta = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::TelemetryData_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::TelemetryData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::TelemetryData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::TelemetryData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__TelemetryData
    std::shared_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__TelemetryData
    std::shared_ptr<vehicle_core::msg::TelemetryData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TelemetryData_ & other) const
  {
    if (this->gps_online != other.gps_online) {
      return false;
    }
    if (this->lat != other.lat) {
      return false;
    }
    if (this->lon != other.lon) {
      return false;
    }
    if (this->heading != other.heading) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    if (this->distance_delta != other.distance_delta) {
      return false;
    }
    return true;
  }
  bool operator!=(const TelemetryData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TelemetryData_

// alias to use template instance with default allocator
using TelemetryData =
  vehicle_core::msg::TelemetryData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__STRUCT_HPP_
