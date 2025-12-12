// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_core:msg/AutopilotStatus.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/autopilot_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vehicle_core__msg__AutopilotStatus__init(vehicle_core__msg__AutopilotStatus * msg)
{
  if (!msg) {
    return false;
  }
  // autopilot_ready
  // lidar_ready
  // camera_ready
  return true;
}

void
vehicle_core__msg__AutopilotStatus__fini(vehicle_core__msg__AutopilotStatus * msg)
{
  if (!msg) {
    return;
  }
  // autopilot_ready
  // lidar_ready
  // camera_ready
}

bool
vehicle_core__msg__AutopilotStatus__are_equal(const vehicle_core__msg__AutopilotStatus * lhs, const vehicle_core__msg__AutopilotStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // autopilot_ready
  if (lhs->autopilot_ready != rhs->autopilot_ready) {
    return false;
  }
  // lidar_ready
  if (lhs->lidar_ready != rhs->lidar_ready) {
    return false;
  }
  // camera_ready
  if (lhs->camera_ready != rhs->camera_ready) {
    return false;
  }
  return true;
}

bool
vehicle_core__msg__AutopilotStatus__copy(
  const vehicle_core__msg__AutopilotStatus * input,
  vehicle_core__msg__AutopilotStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // autopilot_ready
  output->autopilot_ready = input->autopilot_ready;
  // lidar_ready
  output->lidar_ready = input->lidar_ready;
  // camera_ready
  output->camera_ready = input->camera_ready;
  return true;
}

vehicle_core__msg__AutopilotStatus *
vehicle_core__msg__AutopilotStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotStatus * msg = (vehicle_core__msg__AutopilotStatus *)allocator.allocate(sizeof(vehicle_core__msg__AutopilotStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_core__msg__AutopilotStatus));
  bool success = vehicle_core__msg__AutopilotStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_core__msg__AutopilotStatus__destroy(vehicle_core__msg__AutopilotStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_core__msg__AutopilotStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_core__msg__AutopilotStatus__Sequence__init(vehicle_core__msg__AutopilotStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotStatus * data = NULL;

  if (size) {
    data = (vehicle_core__msg__AutopilotStatus *)allocator.zero_allocate(size, sizeof(vehicle_core__msg__AutopilotStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_core__msg__AutopilotStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_core__msg__AutopilotStatus__fini(&data[i - 1]);
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
vehicle_core__msg__AutopilotStatus__Sequence__fini(vehicle_core__msg__AutopilotStatus__Sequence * array)
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
      vehicle_core__msg__AutopilotStatus__fini(&array->data[i]);
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

vehicle_core__msg__AutopilotStatus__Sequence *
vehicle_core__msg__AutopilotStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotStatus__Sequence * array = (vehicle_core__msg__AutopilotStatus__Sequence *)allocator.allocate(sizeof(vehicle_core__msg__AutopilotStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_core__msg__AutopilotStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_core__msg__AutopilotStatus__Sequence__destroy(vehicle_core__msg__AutopilotStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_core__msg__AutopilotStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_core__msg__AutopilotStatus__Sequence__are_equal(const vehicle_core__msg__AutopilotStatus__Sequence * lhs, const vehicle_core__msg__AutopilotStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_core__msg__AutopilotStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_core__msg__AutopilotStatus__Sequence__copy(
  const vehicle_core__msg__AutopilotStatus__Sequence * input,
  vehicle_core__msg__AutopilotStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_core__msg__AutopilotStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_core__msg__AutopilotStatus * data =
      (vehicle_core__msg__AutopilotStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_core__msg__AutopilotStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_core__msg__AutopilotStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_core__msg__AutopilotStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
