// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_core:msg/IMUStatus.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__STRUCT_HPP_
#define VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_core__msg__IMUStatus __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_core__msg__IMUStatus __declspec(deprecated)
#endif

namespace vehicle_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct IMUStatus_
{
  using Type = IMUStatus_<ContainerAllocator>;

  explicit IMUStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->imu_data_ok = false;
      this->calib_sys = 0;
      this->calib_gyro = 0;
      this->calib_accel = 0;
      this->calib_mag = 0;
      this->op_mode = 0;
      this->err_code = 0;
    }
  }

  explicit IMUStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->imu_data_ok = false;
      this->calib_sys = 0;
      this->calib_gyro = 0;
      this->calib_accel = 0;
      this->calib_mag = 0;
      this->op_mode = 0;
      this->err_code = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _imu_data_ok_type =
    bool;
  _imu_data_ok_type imu_data_ok;
  using _calib_sys_type =
    uint8_t;
  _calib_sys_type calib_sys;
  using _calib_gyro_type =
    uint8_t;
  _calib_gyro_type calib_gyro;
  using _calib_accel_type =
    uint8_t;
  _calib_accel_type calib_accel;
  using _calib_mag_type =
    uint8_t;
  _calib_mag_type calib_mag;
  using _op_mode_type =
    uint8_t;
  _op_mode_type op_mode;
  using _err_code_type =
    uint8_t;
  _err_code_type err_code;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__imu_data_ok(
    const bool & _arg)
  {
    this->imu_data_ok = _arg;
    return *this;
  }
  Type & set__calib_sys(
    const uint8_t & _arg)
  {
    this->calib_sys = _arg;
    return *this;
  }
  Type & set__calib_gyro(
    const uint8_t & _arg)
  {
    this->calib_gyro = _arg;
    return *this;
  }
  Type & set__calib_accel(
    const uint8_t & _arg)
  {
    this->calib_accel = _arg;
    return *this;
  }
  Type & set__calib_mag(
    const uint8_t & _arg)
  {
    this->calib_mag = _arg;
    return *this;
  }
  Type & set__op_mode(
    const uint8_t & _arg)
  {
    this->op_mode = _arg;
    return *this;
  }
  Type & set__err_code(
    const uint8_t & _arg)
  {
    this->err_code = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_core::msg::IMUStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_core::msg::IMUStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::IMUStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_core::msg::IMUStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_core__msg__IMUStatus
    std::shared_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_core__msg__IMUStatus
    std::shared_ptr<vehicle_core::msg::IMUStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IMUStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->imu_data_ok != other.imu_data_ok) {
      return false;
    }
    if (this->calib_sys != other.calib_sys) {
      return false;
    }
    if (this->calib_gyro != other.calib_gyro) {
      return false;
    }
    if (this->calib_accel != other.calib_accel) {
      return false;
    }
    if (this->calib_mag != other.calib_mag) {
      return false;
    }
    if (this->op_mode != other.op_mode) {
      return false;
    }
    if (this->err_code != other.err_code) {
      return false;
    }
    return true;
  }
  bool operator!=(const IMUStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IMUStatus_

// alias to use template instance with default allocator
using IMUStatus =
  vehicle_core::msg::IMUStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__IMU_STATUS__STRUCT_HPP_
