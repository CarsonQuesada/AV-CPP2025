// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/server_init__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `general_status`
#include "vehicle_core/msg/detail/general_status__functions.h"
// Member `lights_status`
#include "vehicle_core/msg/detail/lights_status__functions.h"
// Member `drive_status`
#include "vehicle_core/msg/detail/drive_status__functions.h"
// Member `autopilot_status`
#include "vehicle_core/msg/detail/autopilot_status__functions.h"

bool
vehicle_core__msg__ServerInit__init(vehicle_core__msg__ServerInit * msg)
{
  if (!msg) {
    return false;
  }
  // general_status
  if (!vehicle_core__msg__GeneralStatus__init(&msg->general_status)) {
    vehicle_core__msg__ServerInit__fini(msg);
    return false;
  }
  // lights_status
  if (!vehicle_core__msg__LightsStatus__init(&msg->lights_status)) {
    vehicle_core__msg__ServerInit__fini(msg);
    return false;
  }
  // drive_status
  if (!vehicle_core__msg__DriveStatus__init(&msg->drive_status)) {
    vehicle_core__msg__ServerInit__fini(msg);
    return false;
  }
  // autopilot_status
  if (!vehicle_core__msg__AutopilotStatus__init(&msg->autopilot_status)) {
    vehicle_core__msg__ServerInit__fini(msg);
    return false;
  }
  return true;
}

void
vehicle_core__msg__ServerInit__fini(vehicle_core__msg__ServerInit * msg)
{
  if (!msg) {
    return;
  }
  // general_status
  vehicle_core__msg__GeneralStatus__fini(&msg->general_status);
  // lights_status
  vehicle_core__msg__LightsStatus__fini(&msg->lights_status);
  // drive_status
  vehicle_core__msg__DriveStatus__fini(&msg->drive_status);
  // autopilot_status
  vehicle_core__msg__AutopilotStatus__fini(&msg->autopilot_status);
}

bool
vehicle_core__msg__ServerInit__are_equal(const vehicle_core__msg__ServerInit * lhs, const vehicle_core__msg__ServerInit * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // general_status
  if (!vehicle_core__msg__GeneralStatus__are_equal(
      &(lhs->general_status), &(rhs->general_status)))
  {
    return false;
  }
  // lights_status
  if (!vehicle_core__msg__LightsStatus__are_equal(
      &(lhs->lights_status), &(rhs->lights_status)))
  {
    return false;
  }
  // drive_status
  if (!vehicle_core__msg__DriveStatus__are_equal(
      &(lhs->drive_status), &(rhs->drive_status)))
  {
    return false;
  }
  // autopilot_status
  if (!vehicle_core__msg__AutopilotStatus__are_equal(
      &(lhs->autopilot_status), &(rhs->autopilot_status)))
  {
    return false;
  }
  return true;
}

bool
vehicle_core__msg__ServerInit__copy(
  const vehicle_core__msg__ServerInit * input,
  vehicle_core__msg__ServerInit * output)
{
  if (!input || !output) {
    return false;
  }
  // general_status
  if (!vehicle_core__msg__GeneralStatus__copy(
      &(input->general_status), &(output->general_status)))
  {
    return false;
  }
  // lights_status
  if (!vehicle_core__msg__LightsStatus__copy(
      &(input->lights_status), &(output->lights_status)))
  {
    return false;
  }
  // drive_status
  if (!vehicle_core__msg__DriveStatus__copy(
      &(input->drive_status), &(output->drive_status)))
  {
    return false;
  }
  // autopilot_status
  if (!vehicle_core__msg__AutopilotStatus__copy(
      &(input->autopilot_status), &(output->autopilot_status)))
  {
    return false;
  }
  return true;
}

vehicle_core__msg__ServerInit *
vehicle_core__msg__ServerInit__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__ServerInit * msg = (vehicle_core__msg__ServerInit *)allocator.allocate(sizeof(vehicle_core__msg__ServerInit), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_core__msg__ServerInit));
  bool success = vehicle_core__msg__ServerInit__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_core__msg__ServerInit__destroy(vehicle_core__msg__ServerInit * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_core__msg__ServerInit__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_core__msg__ServerInit__Sequence__init(vehicle_core__msg__ServerInit__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__ServerInit * data = NULL;

  if (size) {
    data = (vehicle_core__msg__ServerInit *)allocator.zero_allocate(size, sizeof(vehicle_core__msg__ServerInit), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_core__msg__ServerInit__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_core__msg__ServerInit__fini(&data[i - 1]);
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
vehicle_core__msg__ServerInit__Sequence__fini(vehicle_core__msg__ServerInit__Sequence * array)
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
      vehicle_core__msg__ServerInit__fini(&array->data[i]);
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

vehicle_core__msg__ServerInit__Sequence *
vehicle_core__msg__ServerInit__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__ServerInit__Sequence * array = (vehicle_core__msg__ServerInit__Sequence *)allocator.allocate(sizeof(vehicle_core__msg__ServerInit__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_core__msg__ServerInit__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_core__msg__ServerInit__Sequence__destroy(vehicle_core__msg__ServerInit__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_core__msg__ServerInit__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_core__msg__ServerInit__Sequence__are_equal(const vehicle_core__msg__ServerInit__Sequence * lhs, const vehicle_core__msg__ServerInit__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_core__msg__ServerInit__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_core__msg__ServerInit__Sequence__copy(
  const vehicle_core__msg__ServerInit__Sequence * input,
  vehicle_core__msg__ServerInit__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_core__msg__ServerInit);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_core__msg__ServerInit * data =
      (vehicle_core__msg__ServerInit *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_core__msg__ServerInit__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_core__msg__ServerInit__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_core__msg__ServerInit__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
