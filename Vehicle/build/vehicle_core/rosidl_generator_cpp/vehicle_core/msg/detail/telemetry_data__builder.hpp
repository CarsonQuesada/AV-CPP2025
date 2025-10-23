// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_core:msg/TelemetryData.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__BUILDER_HPP_
#define VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_core/msg/detail/telemetry_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_core
{

namespace msg
{

namespace builder
{

class Init_TelemetryData_distance_delta
{
public:
  explicit Init_TelemetryData_distance_delta(::vehicle_core::msg::TelemetryData & msg)
  : msg_(msg)
  {}
  ::vehicle_core::msg::TelemetryData distance_delta(::vehicle_core::msg::TelemetryData::_distance_delta_type arg)
  {
    msg_.distance_delta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_core::msg::TelemetryData msg_;
};

class Init_TelemetryData_speed
{
public:
  explicit Init_TelemetryData_speed(::vehicle_core::msg::TelemetryData & msg)
  : msg_(msg)
  {}
  Init_TelemetryData_distance_delta speed(::vehicle_core::msg::TelemetryData::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_TelemetryData_distance_delta(msg_);
  }

private:
  ::vehicle_core::msg::TelemetryData msg_;
};

class Init_TelemetryData_heading
{
public:
  explicit Init_TelemetryData_heading(::vehicle_core::msg::TelemetryData & msg)
  : msg_(msg)
  {}
  Init_TelemetryData_speed heading(::vehicle_core::msg::TelemetryData::_heading_type arg)
  {
    msg_.heading = std::move(arg);
    return Init_TelemetryData_speed(msg_);
  }

private:
  ::vehicle_core::msg::TelemetryData msg_;
};

class Init_TelemetryData_lon
{
public:
  explicit Init_TelemetryData_lon(::vehicle_core::msg::TelemetryData & msg)
  : msg_(msg)
  {}
  Init_TelemetryData_heading lon(::vehicle_core::msg::TelemetryData::_lon_type arg)
  {
    msg_.lon = std::move(arg);
    return Init_TelemetryData_heading(msg_);
  }

private:
  ::vehicle_core::msg::TelemetryData msg_;
};

class Init_TelemetryData_lat
{
public:
  explicit Init_TelemetryData_lat(::vehicle_core::msg::TelemetryData & msg)
  : msg_(msg)
  {}
  Init_TelemetryData_lon lat(::vehicle_core::msg::TelemetryData::_lat_type arg)
  {
    msg_.lat = std::move(arg);
    return Init_TelemetryData_lon(msg_);
  }

private:
  ::vehicle_core::msg::TelemetryData msg_;
};

class Init_TelemetryData_gps_online
{
public:
  Init_TelemetryData_gps_online()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TelemetryData_lat gps_online(::vehicle_core::msg::TelemetryData::_gps_online_type arg)
  {
    msg_.gps_online = std::move(arg);
    return Init_TelemetryData_lat(msg_);
  }

private:
  ::vehicle_core::msg::TelemetryData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_core::msg::TelemetryData>()
{
  return vehicle_core::msg::builder::Init_TelemetryData_gps_online();
}

}  // namespace vehicle_core

#endif  // VEHICLE_CORE__MSG__DETAIL__TELEMETRY_DATA__BUILDER_HPP_
