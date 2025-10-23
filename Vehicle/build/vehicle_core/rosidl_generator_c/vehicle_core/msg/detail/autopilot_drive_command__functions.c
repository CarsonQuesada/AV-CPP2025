// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_core:msg/AutopilotDriveCommand.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/autopilot_drive_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vehicle_core__msg__AutopilotDriveCommand__init(vehicle_core__msg__AutopilotDriveCommand * msg)
{
  if (!msg) {
    return false;
  }
  // brake
  // gear
  // speed_mps
  // steer_rad
  return true;
}

void
vehicle_core__msg__AutopilotDriveCommand__fini(vehicle_core__msg__AutopilotDriveCommand * msg)
{
  if (!msg) {
    return;
  }
  // brake
  // gear
  // speed_mps
  // steer_rad
}

bool
vehicle_core__msg__AutopilotDriveCommand__are_equal(const vehicle_core__msg__AutopilotDriveCommand * lhs, const vehicle_core__msg__AutopilotDriveCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // brake
  if (lhs->brake != rhs->brake) {
    return false;
  }
  // gear
  if (lhs->gear != rhs->gear) {
    return false;
  }
  // speed_mps
  if (lhs->speed_mps != rhs->speed_mps) {
    return false;
  }
  // steer_rad
  if (lhs->steer_rad != rhs->steer_rad) {
    return false;
  }
  return true;
}

bool
vehicle_core__msg__AutopilotDriveCommand__copy(
  const vehicle_core__msg__AutopilotDriveCommand * input,
  vehicle_core__msg__AutopilotDriveCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // brake
  output->brake = input->brake;
  // gear
  output->gear = input->gear;
  // speed_mps
  output->speed_mps = input->speed_mps;
  // steer_rad
  output->steer_rad = input->steer_rad;
  return true;
}

vehicle_core__msg__AutopilotDriveCommand *
vehicle_core__msg__AutopilotDriveCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotDriveCommand * msg = (vehicle_core__msg__AutopilotDriveCommand *)allocator.allocate(sizeof(vehicle_core__msg__AutopilotDriveCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_core__msg__AutopilotDriveCommand));
  bool success = vehicle_core__msg__AutopilotDriveCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_core__msg__AutopilotDriveCommand__destroy(vehicle_core__msg__AutopilotDriveCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_core__msg__AutopilotDriveCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_core__msg__AutopilotDriveCommand__Sequence__init(vehicle_core__msg__AutopilotDriveCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotDriveCommand * data = NULL;

  if (size) {
    data = (vehicle_core__msg__AutopilotDriveCommand *)allocator.zero_allocate(size, sizeof(vehicle_core__msg__AutopilotDriveCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_core__msg__AutopilotDriveCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_core__msg__AutopilotDriveCommand__fini(&data[i - 1]);
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
vehicle_core__msg__AutopilotDriveCommand__Sequence__fini(vehicle_core__msg__AutopilotDriveCommand__Sequence * array)
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
      vehicle_core__msg__AutopilotDriveCommand__fini(&array->data[i]);
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

vehicle_core__msg__AutopilotDriveCommand__Sequence *
vehicle_core__msg__AutopilotDriveCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotDriveCommand__Sequence * array = (vehicle_core__msg__AutopilotDriveCommand__Sequence *)allocator.allocate(sizeof(vehicle_core__msg__AutopilotDriveCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_core__msg__AutopilotDriveCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_core__msg__AutopilotDriveCommand__Sequence__destroy(vehicle_core__msg__AutopilotDriveCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_core__msg__AutopilotDriveCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_core__msg__AutopilotDriveCommand__Sequence__are_equal(const vehicle_core__msg__AutopilotDriveCommand__Sequence * lhs, const vehicle_core__msg__AutopilotDriveCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_core__msg__AutopilotDriveCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_core__msg__AutopilotDriveCommand__Sequence__copy(
  const vehicle_core__msg__AutopilotDriveCommand__Sequence * input,
  vehicle_core__msg__AutopilotDriveCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_core__msg__AutopilotDriveCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_core__msg__AutopilotDriveCommand * data =
      (vehicle_core__msg__AutopilotDriveCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_core__msg__AutopilotDriveCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_core__msg__AutopilotDriveCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_core__msg__AutopilotDriveCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
