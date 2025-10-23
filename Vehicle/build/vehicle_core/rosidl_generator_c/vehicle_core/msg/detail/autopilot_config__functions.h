// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vehicle_core:msg/AutopilotConfig.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__FUNCTIONS_H_
#define VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vehicle_core/msg/rosidl_generator_c__visibility_control.h"

#include "vehicle_core/msg/detail/autopilot_config__struct.h"

/// Initialize msg/AutopilotConfig message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vehicle_core__msg__AutopilotConfig
 * )) before or use
 * vehicle_core__msg__AutopilotConfig__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__AutopilotConfig__init(vehicle_core__msg__AutopilotConfig * msg);

/// Finalize msg/AutopilotConfig message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__AutopilotConfig__fini(vehicle_core__msg__AutopilotConfig * msg);

/// Create msg/AutopilotConfig message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vehicle_core__msg__AutopilotConfig__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__msg__AutopilotConfig *
vehicle_core__msg__AutopilotConfig__create();

/// Destroy msg/AutopilotConfig message.
/**
 * It calls
 * vehicle_core__msg__AutopilotConfig__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__AutopilotConfig__destroy(vehicle_core__msg__AutopilotConfig * msg);

/// Check for msg/AutopilotConfig message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__AutopilotConfig__are_equal(const vehicle_core__msg__AutopilotConfig * lhs, const vehicle_core__msg__AutopilotConfig * rhs);

/// Copy a msg/AutopilotConfig message.
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
vehicle_core__msg__AutopilotConfig__copy(
  const vehicle_core__msg__AutopilotConfig * input,
  vehicle_core__msg__AutopilotConfig * output);

/// Initialize array of msg/AutopilotConfig messages.
/**
 * It allocates the memory for the number of elements and calls
 * vehicle_core__msg__AutopilotConfig__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__AutopilotConfig__Sequence__init(vehicle_core__msg__AutopilotConfig__Sequence * array, size_t size);

/// Finalize array of msg/AutopilotConfig messages.
/**
 * It calls
 * vehicle_core__msg__AutopilotConfig__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__AutopilotConfig__Sequence__fini(vehicle_core__msg__AutopilotConfig__Sequence * array);

/// Create array of msg/AutopilotConfig messages.
/**
 * It allocates the memory for the array and calls
 * vehicle_core__msg__AutopilotConfig__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__msg__AutopilotConfig__Sequence *
vehicle_core__msg__AutopilotConfig__Sequence__create(size_t size);

/// Destroy array of msg/AutopilotConfig messages.
/**
 * It calls
 * vehicle_core__msg__AutopilotConfig__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__msg__AutopilotConfig__Sequence__destroy(vehicle_core__msg__AutopilotConfig__Sequence * array);

/// Check for msg/AutopilotConfig message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__msg__AutopilotConfig__Sequence__are_equal(const vehicle_core__msg__AutopilotConfig__Sequence * lhs, const vehicle_core__msg__AutopilotConfig__Sequence * rhs);

/// Copy an array of msg/AutopilotConfig messages.
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
vehicle_core__msg__AutopilotConfig__Sequence__copy(
  const vehicle_core__msg__AutopilotConfig__Sequence * input,
  vehicle_core__msg__AutopilotConfig__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__MSG__DETAIL__AUTOPILOT_CONFIG__FUNCTIONS_H_
