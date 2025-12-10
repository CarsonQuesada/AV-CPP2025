// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_core:msg/IMUStatus.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/imu_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
vehicle_core__msg__IMUStatus__init(vehicle_core__msg__IMUStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vehicle_core__msg__IMUStatus__fini(msg);
    return false;
  }
  // imu_data_ok
  // calib_sys
  // calib_gyro
  // calib_accel
  // calib_mag
  // op_mode
  // err_code
  return true;
}

void
vehicle_core__msg__IMUStatus__fini(vehicle_core__msg__IMUStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // imu_data_ok
  // calib_sys
  // calib_gyro
  // calib_accel
  // calib_mag
  // op_mode
  // err_code
}

bool
vehicle_core__msg__IMUStatus__are_equal(const vehicle_core__msg__IMUStatus * lhs, const vehicle_core__msg__IMUStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // imu_data_ok
  if (lhs->imu_data_ok != rhs->imu_data_ok) {
    return false;
  }
  // calib_sys
  if (lhs->calib_sys != rhs->calib_sys) {
    return false;
  }
  // calib_gyro
  if (lhs->calib_gyro != rhs->calib_gyro) {
    return false;
  }
  // calib_accel
  if (lhs->calib_accel != rhs->calib_accel) {
    return false;
  }
  // calib_mag
  if (lhs->calib_mag != rhs->calib_mag) {
    return false;
  }
  // op_mode
  if (lhs->op_mode != rhs->op_mode) {
    return false;
  }
  // err_code
  if (lhs->err_code != rhs->err_code) {
    return false;
  }
  return true;
}

bool
vehicle_core__msg__IMUStatus__copy(
  const vehicle_core__msg__IMUStatus * input,
  vehicle_core__msg__IMUStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // imu_data_ok
  output->imu_data_ok = input->imu_data_ok;
  // calib_sys
  output->calib_sys = input->calib_sys;
  // calib_gyro
  output->calib_gyro = input->calib_gyro;
  // calib_accel
  output->calib_accel = input->calib_accel;
  // calib_mag
  output->calib_mag = input->calib_mag;
  // op_mode
  output->op_mode = input->op_mode;
  // err_code
  output->err_code = input->err_code;
  return true;
}

vehicle_core__msg__IMUStatus *
vehicle_core__msg__IMUStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__IMUStatus * msg = (vehicle_core__msg__IMUStatus *)allocator.allocate(sizeof(vehicle_core__msg__IMUStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_core__msg__IMUStatus));
  bool success = vehicle_core__msg__IMUStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_core__msg__IMUStatus__destroy(vehicle_core__msg__IMUStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_core__msg__IMUStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_core__msg__IMUStatus__Sequence__init(vehicle_core__msg__IMUStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__IMUStatus * data = NULL;

  if (size) {
    data = (vehicle_core__msg__IMUStatus *)allocator.zero_allocate(size, sizeof(vehicle_core__msg__IMUStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_core__msg__IMUStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_core__msg__IMUStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vehicle_core__msg__IMUStatus__Sequence__fini(vehicle_core__msg__IMUStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vehicle_core__msg__IMUStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vehicle_core__msg__IMUStatus__Sequence *
vehicle_core__msg__IMUStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__IMUStatus__Sequence * array = (vehicle_core__msg__IMUStatus__Sequence *)allocator.allocate(sizeof(vehicle_core__msg__IMUStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_core__msg__IMUStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_core__msg__IMUStatus__Sequence__destroy(vehicle_core__msg__IMUStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_core__msg__IMUStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_core__msg__IMUStatus__Sequence__are_equal(const vehicle_core__msg__IMUStatus__Sequence * lhs, const vehicle_core__msg__IMUStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_core__msg__IMUStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_core__msg__IMUStatus__Sequence__copy(
  const vehicle_core__msg__IMUStatus__Sequence * input,
  vehicle_core__msg__IMUStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_core__msg__IMUStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_core__msg__IMUStatus * data =
      (vehicle_core__msg__IMUStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_core__msg__IMUStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_core__msg__IMUStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_core__msg__IMUStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
