// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vehicle_core:msg/MaxSpeed.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__FUNCTIONS_H_
#define VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vehicle_core/msg/rosidl_generator_c__visibility_control.h"

#include "vehicle_core/msg/detail/max_speed__struct.h"

/// Initialize msg/MaxSpeed message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vehicle_core__msg__MaxSpeed
 * )) before or use
 * vehicle_core__msg__MaxSpeed__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__MaxSpeed__init(vehicle_core__msg__MaxSpeed * msg);

/// Finalize msg/MaxSpeed message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__MaxSpeed__fini(vehicle_core__msg__MaxSpeed * msg);

/// Create msg/MaxSpeed message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vehicle_core__msg__MaxSpeed__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__msg__MaxSpeed *
vehicle_core__msg__MaxSpeed__create();

/// Destroy msg/MaxSpeed message.
/**
 * It calls
 * vehicle_core__msg__MaxSpeed__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__MaxSpeed__destroy(vehicle_core__msg__MaxSpeed * msg);

/// Check for msg/MaxSpeed message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__MaxSpeed__are_equal(const vehicle_core__msg__MaxSpeed * lhs, const vehicle_core__msg__MaxSpeed * rhs);

/// Copy a msg/MaxSpeed message.
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
vehicle_core__msg__MaxSpeed__copy(
  const vehicle_core__msg__MaxSpeed * input,
  vehicle_core__msg__MaxSpeed * output);

/// Initialize array of msg/MaxSpeed messages.
/**
 * It allocates the memory for the number of elements and calls
 * vehicle_core__msg__MaxSpeed__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__MaxSpeed__Sequence__init(vehicle_core__msg__MaxSpeed__Sequence * array, size_t size);

/// Finalize array of msg/MaxSpeed messages.
/**
 * It calls
 * vehicle_core__msg__MaxSpeed__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__MaxSpeed__Sequence__fini(vehicle_core__msg__MaxSpeed__Sequence * array);

/// Create array of msg/MaxSpeed messages.
/**
 * It allocates the memory for the array and calls
 * vehicle_core__msg__MaxSpeed__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__msg__MaxSpeed__Sequence *
vehicle_core__msg__MaxSpeed__Sequence__create(size_t size);

/// Destroy array of msg/MaxSpeed messages.
/**
 * It calls
 * vehicle_core__msg__MaxSpeed__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__MaxSpeed__Sequence__destroy(vehicle_core__msg__MaxSpeed__Sequence * array);

/// Check for msg/MaxSpeed message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__MaxSpeed__Sequence__are_equal(const vehicle_core__msg__MaxSpeed__Sequence * lhs, const vehicle_core__msg__MaxSpeed__Sequence * rhs);

/// Copy an array of msg/MaxSpeed messages.
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
vehicle_core__msg__MaxSpeed__Sequence__copy(
  const vehicle_core__msg__MaxSpeed__Sequence * input,
  vehicle_core__msg__MaxSpeed__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__MAX_SPEED__FUNCTIONS_H_
