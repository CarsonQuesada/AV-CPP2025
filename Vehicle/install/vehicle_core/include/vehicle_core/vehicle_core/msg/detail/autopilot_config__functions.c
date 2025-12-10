// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_core:msg/AutopilotConfig.idl
// generated code does not contain a copyright notice
#include "vehicle_core/msg/detail/autopilot_config__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `keys`
#include "rosidl_runtime_c/string_functions.h"
// Member `values`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
vehicle_core__msg__AutopilotConfig__init(vehicle_core__msg__AutopilotConfig * msg)
{
  if (!msg) {
    return false;
  }
  // profile_id
  // features_mask
  // keys
  if (!rosidl_runtime_c__String__Sequence__init(&msg->keys, 0)) {
    vehicle_core__msg__AutopilotConfig__fini(msg);
    return false;
  }
  // values
  if (!rosidl_runtime_c__double__Sequence__init(&msg->values, 0)) {
    vehicle_core__msg__AutopilotConfig__fini(msg);
    return false;
  }
  return true;
}

void
vehicle_core__msg__AutopilotConfig__fini(vehicle_core__msg__AutopilotConfig * msg)
{
  if (!msg) {
    return;
  }
  // profile_id
  // features_mask
  // keys
  rosidl_runtime_c__String__Sequence__fini(&msg->keys);
  // values
  rosidl_runtime_c__double__Sequence__fini(&msg->values);
}

bool
vehicle_core__msg__AutopilotConfig__are_equal(const vehicle_core__msg__AutopilotConfig * lhs, const vehicle_core__msg__AutopilotConfig * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // profile_id
  if (lhs->profile_id != rhs->profile_id) {
    return false;
  }
  // features_mask
  if (lhs->features_mask != rhs->features_mask) {
    return false;
  }
  // keys
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->keys), &(rhs->keys)))
  {
    return false;
  }
  // values
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->values), &(rhs->values)))
  {
    return false;
  }
  return true;
}

bool
vehicle_core__msg__AutopilotConfig__copy(
  const vehicle_core__msg__AutopilotConfig * input,
  vehicle_core__msg__AutopilotConfig * output)
{
  if (!input || !output) {
    return false;
  }
  // profile_id
  output->profile_id = input->profile_id;
  // features_mask
  output->features_mask = input->features_mask;
  // keys
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->keys), &(output->keys)))
  {
    return false;
  }
  // values
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->values), &(output->values)))
  {
    return false;
  }
  return true;
}

vehicle_core__msg__AutopilotConfig *
vehicle_core__msg__AutopilotConfig__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotConfig * msg = (vehicle_core__msg__AutopilotConfig *)allocator.allocate(sizeof(vehicle_core__msg__AutopilotConfig), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_core__msg__AutopilotConfig));
  bool success = vehicle_core__msg__AutopilotConfig__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_core__msg__AutopilotConfig__destroy(vehicle_core__msg__AutopilotConfig * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_core__msg__AutopilotConfig__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_core__msg__AutopilotConfig__Sequence__init(vehicle_core__msg__AutopilotConfig__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotConfig * data = NULL;

  if (size) {
    data = (vehicle_core__msg__AutopilotConfig *)allocator.zero_allocate(size, sizeof(vehicle_core__msg__AutopilotConfig), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_core__msg__AutopilotConfig__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_core__msg__AutopilotConfig__fini(&data[i - 1]);
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
vehicle_core__msg__AutopilotConfig__Sequence__fini(vehicle_core__msg__AutopilotConfig__Sequence * array)
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
      vehicle_core__msg__AutopilotConfig__fini(&array->data[i]);
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

vehicle_core__msg__AutopilotConfig__Sequence *
vehicle_core__msg__AutopilotConfig__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_core__msg__AutopilotConfig__Sequence * array = (vehicle_core__msg__AutopilotConfig__Sequence *)allocator.allocate(sizeof(vehicle_core__msg__AutopilotConfig__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_core__msg__AutopilotConfig__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_core__msg__AutopilotConfig__Sequence__destroy(vehicle_core__msg__AutopilotConfig__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_core__msg__AutopilotConfig__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_core__msg__AutopilotConfig__Sequence__are_equal(const vehicle_core__msg__AutopilotConfig__Sequence * lhs, const vehicle_core__msg__AutopilotConfig__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_core__msg__AutopilotConfig__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_core__msg__AutopilotConfig__Sequence__copy(
  const vehicle_core__msg__AutopilotConfig__Sequence * input,
  vehicle_core__msg__AutopilotConfig__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_core__msg__AutopilotConfig);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_core__msg__AutopilotConfig * data =
      (vehicle_core__msg__AutopilotConfig *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_core__msg__AutopilotConfig__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_core__msg__AutopilotConfig__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_core__msg__AutopilotConfig__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
