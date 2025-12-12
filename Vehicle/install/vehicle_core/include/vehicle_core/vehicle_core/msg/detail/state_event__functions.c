// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_core:msg/StateEvent.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/state_event__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `reason`
#include "rosidl_runtime_c/string_functions.h"

bool
vehicle_core__msg__StateEvent__init(vehicle_core__msg__StateEvent * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    vehicle_core__msg__StateEvent__fini(msg);
    return false;
  }
  // from_mode
  // to_mode
  // reason
  if (!rosidl_runtime_c__String__init(&msg->reason)) {
    vehicle_core__msg__StateEvent__fini(msg);
    return false;
  }
  return true;
}

void
vehicle_core__msg__StateEvent__fini(vehicle_core__msg__StateEvent * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // from_mode
  // to_mode
  // reason
  rosidl_runtime_c__String__fini(&msg->reason);
}

bool
vehicle_core__msg__StateEvent__are_equal(const vehicle_core__msg__StateEvent * lhs, const vehicle_core__msg__StateEvent * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // from_mode
  if (lhs->from_mode != rhs->from_mode) {
    return false;
  }
  // to_mode
  if (lhs->to_mode != rhs->to_mode) {
    return false;
  }
  // reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->reason), &(rhs->reason)))
  {
    return false;
  }
  return true;
}

bool
vehicle_core__msg__StateEvent__copy(
  const vehicle_core__msg__StateEvent * input,
  vehicle_core__msg__StateEvent * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // from_mode
  output->from_mode = input->from_mode;
  // to_mode
  output->to_mode = input->to_mode;
  // reason
  if (!rosidl_runtime_c__String__copy(
      &(input->reason), &(output->reason)))
  {
    return false;
  }
  return true;
}

vehicle_core__msg__StateEvent *
vehicle_core__msg__StateEvent__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__StateEvent * msg = (vehicle_core__msg__StateEvent *)allocator.allocate(sizeof(vehicle_core__msg__StateEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_core__msg__StateEvent));
  bool success = vehicle_core__msg__StateEvent__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_core__msg__StateEvent__destroy(vehicle_core__msg__StateEvent * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_core__msg__StateEvent__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_core__msg__StateEvent__Sequence__init(vehicle_core__msg__StateEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__StateEvent * data = NULL;

  if (size) {
    data = (vehicle_core__msg__StateEvent *)allocator.zero_allocate(size, sizeof(vehicle_core__msg__StateEvent), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_core__msg__StateEvent__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_core__msg__StateEvent__fini(&data[i - 1]);
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
vehicle_core__msg__StateEvent__Sequence__fini(vehicle_core__msg__StateEvent__Sequence * array)
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
      vehicle_core__msg__StateEvent__fini(&array->data[i]);
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

vehicle_core__msg__StateEvent__Sequence *
vehicle_core__msg__StateEvent__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__StateEvent__Sequence * array = (vehicle_core__msg__StateEvent__Sequence *)allocator.allocate(sizeof(vehicle_core__msg__StateEvent__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_core__msg__StateEvent__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_core__msg__StateEvent__Sequence__destroy(vehicle_core__msg__StateEvent__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_core__msg__StateEvent__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_core__msg__StateEvent__Sequence__are_equal(const vehicle_core__msg__StateEvent__Sequence * lhs, const vehicle_core__msg__StateEvent__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_core__msg__StateEvent__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_core__msg__StateEvent__Sequence__copy(
  const vehicle_core__msg__StateEvent__Sequence * input,
  vehicle_core__msg__StateEvent__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_core__msg__StateEvent);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_core__msg__StateEvent * data =
      (vehicle_core__msg__StateEvent *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_core__msg__StateEvent__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_core__msg__StateEvent__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_core__msg__StateEvent__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
