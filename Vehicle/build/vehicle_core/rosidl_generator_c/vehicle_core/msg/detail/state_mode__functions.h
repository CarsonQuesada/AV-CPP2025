// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vehicle_core:msg/StateMode.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__STATE_MODE__FUNCTIONS_H_
#define VEHICLE_CORE__MSG__DETAIL__STATE_MODE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vehicle_core/msg/rosidl_generator_c__visibility_control.h"

#include "vehicle_core/msg/detail/state_mode__struct.h"

/// Initialize msg/StateMode message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vehicle_core__msg__StateMode
 * )) before or use
 * vehicle_core__msg__StateMode__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__StateMode__init(vehicle_core__msg__StateMode * msg);

/// Finalize msg/StateMode message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__StateMode__fini(vehicle_core__msg__StateMode * msg);

/// Create msg/StateMode message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vehicle_core__msg__StateMode__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__msg__StateMode *
vehicle_core__msg__StateMode__create();

/// Destroy msg/StateMode message.
/**
 * It calls
 * vehicle_core__msg__StateMode__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__StateMode__destroy(vehicle_core__msg__StateMode * msg);

/// Check for msg/StateMode message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__StateMode__are_equal(const vehicle_core__msg__StateMode * lhs, const vehicle_core__msg__StateMode * rhs);

/// Copy a msg/StateMode message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__StateMode__copy(
  const vehicle_core__msg__StateMode * input,
  vehicle_core__msg__StateMode * output);

/// Initialize array of msg/StateMode messages.
/**
 * It allocates the memory for the number of elements and calls
 * vehicle_core__msg__StateMode__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__StateMode__Sequence__init(vehicle_core__msg__StateMode__Sequence * array, size_t size);

/// Finalize array of msg/StateMode messages.
/**
 * It calls
 * vehicle_core__msg__StateMode__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__StateMode__Sequence__fini(vehicle_core__msg__StateMode__Sequence * array);

/// Create array of msg/StateMode messages.
/**
 * It allocates the memory for the array and calls
 * vehicle_core__msg__StateMode__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__msg__StateMode__Sequence *
vehicle_core__msg__StateMode__Sequence__create(size_t size);

/// Destroy array of msg/StateMode messages.
/**
 * It calls
 * vehicle_core__msg__StateMode__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__StateMode__Sequence__destroy(vehicle_core__msg__StateMode__Sequence * array);

/// Check for msg/StateMode message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__StateMode__Sequence__are_equal(const vehicle_core__msg__StateMode__Sequence * lhs, const vehicle_core__msg__StateMode__Sequence * rhs);

/// Copy an array of msg/StateMode messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__StateMode__Sequence__copy(
  const vehicle_core__msg__StateMode__Sequence * input,
  vehicle_core__msg__StateMode__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__STATE_MODE__FUNCTIONS_H_
