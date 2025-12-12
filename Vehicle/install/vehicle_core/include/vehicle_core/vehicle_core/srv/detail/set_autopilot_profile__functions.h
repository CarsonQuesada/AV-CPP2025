// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__FUNCTIONS_H_
#define VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vehicle_core/msg/rosidl_generator_c__visibility_control.h"

#include "vehicle_core/srv/detail/set_autopilot_profile__struct.h"

/// Initialize srv/SetAutopilotProfile message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vehicle_core__srv__SetAutopilotProfile_Request
 * )) before or use
 * vehicle_core__srv__SetAutopilotProfile_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Request__init(vehicle_core__srv__SetAutopilotProfile_Request * msg);

/// Finalize srv/SetAutopilotProfile message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Request__fini(vehicle_core__srv__SetAutopilotProfile_Request * msg);

/// Create srv/SetAutopilotProfile message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vehicle_core__srv__SetAutopilotProfile_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__srv__SetAutopilotProfile_Request *
vehicle_core__srv__SetAutopilotProfile_Request__create();

/// Destroy srv/SetAutopilotProfile message.
/**
 * It calls
 * vehicle_core__srv__SetAutopilotProfile_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Request__destroy(vehicle_core__srv__SetAutopilotProfile_Request * msg);

/// Check for srv/SetAutopilotProfile message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Request__are_equal(const vehicle_core__srv__SetAutopilotProfile_Request * lhs, const vehicle_core__srv__SetAutopilotProfile_Request * rhs);

/// Copy a srv/SetAutopilotProfile message.
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
vehicle_core__srv__SetAutopilotProfile_Request__copy(
  const vehicle_core__srv__SetAutopilotProfile_Request * input,
  vehicle_core__srv__SetAutopilotProfile_Request * output);

/// Initialize array of srv/SetAutopilotProfile messages.
/**
 * It allocates the memory for the number of elements and calls
 * vehicle_core__srv__SetAutopilotProfile_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Request__Sequence__init(vehicle_core__srv__SetAutopilotProfile_Request__Sequence * array, size_t size);

/// Finalize array of srv/SetAutopilotProfile messages.
/**
 * It calls
 * vehicle_core__srv__SetAutopilotProfile_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Request__Sequence__fini(vehicle_core__srv__SetAutopilotProfile_Request__Sequence * array);

/// Create array of srv/SetAutopilotProfile messages.
/**
 * It allocates the memory for the array and calls
 * vehicle_core__srv__SetAutopilotProfile_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__srv__SetAutopilotProfile_Request__Sequence *
vehicle_core__srv__SetAutopilotProfile_Request__Sequence__create(size_t size);

/// Destroy array of srv/SetAutopilotProfile messages.
/**
 * It calls
 * vehicle_core__srv__SetAutopilotProfile_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Request__Sequence__destroy(vehicle_core__srv__SetAutopilotProfile_Request__Sequence * array);

/// Check for srv/SetAutopilotProfile message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Request__Sequence__are_equal(const vehicle_core__srv__SetAutopilotProfile_Request__Sequence * lhs, const vehicle_core__srv__SetAutopilotProfile_Request__Sequence * rhs);

/// Copy an array of srv/SetAutopilotProfile messages.
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
vehicle_core__srv__SetAutopilotProfile_Request__Sequence__copy(
  const vehicle_core__srv__SetAutopilotProfile_Request__Sequence * input,
  vehicle_core__srv__SetAutopilotProfile_Request__Sequence * output);

/// Initialize srv/SetAutopilotProfile message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vehicle_core__srv__SetAutopilotProfile_Response
 * )) before or use
 * vehicle_core__srv__SetAutopilotProfile_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Response__init(vehicle_core__srv__SetAutopilotProfile_Response * msg);

/// Finalize srv/SetAutopilotProfile message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Response__fini(vehicle_core__srv__SetAutopilotProfile_Response * msg);

/// Create srv/SetAutopilotProfile message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vehicle_core__srv__SetAutopilotProfile_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__srv__SetAutopilotProfile_Response *
vehicle_core__srv__SetAutopilotProfile_Response__create();

/// Destroy srv/SetAutopilotProfile message.
/**
 * It calls
 * vehicle_core__srv__SetAutopilotProfile_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Response__destroy(vehicle_core__srv__SetAutopilotProfile_Response * msg);

/// Check for srv/SetAutopilotProfile message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Response__are_equal(const vehicle_core__srv__SetAutopilotProfile_Response * lhs, const vehicle_core__srv__SetAutopilotProfile_Response * rhs);

/// Copy a srv/SetAutopilotProfile message.
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
vehicle_core__srv__SetAutopilotProfile_Response__copy(
  const vehicle_core__srv__SetAutopilotProfile_Response * input,
  vehicle_core__srv__SetAutopilotProfile_Response * output);

/// Initialize array of srv/SetAutopilotProfile messages.
/**
 * It allocates the memory for the number of elements and calls
 * vehicle_core__srv__SetAutopilotProfile_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Response__Sequence__init(vehicle_core__srv__SetAutopilotProfile_Response__Sequence * array, size_t size);

/// Finalize array of srv/SetAutopilotProfile messages.
/**
 * It calls
 * vehicle_core__srv__SetAutopilotProfile_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Response__Sequence__fini(vehicle_core__srv__SetAutopilotProfile_Response__Sequence * array);

/// Create array of srv/SetAutopilotProfile messages.
/**
 * It allocates the memory for the array and calls
 * vehicle_core__srv__SetAutopilotProfile_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
vehicle_core__srv__SetAutopilotProfile_Response__Sequence *
vehicle_core__srv__SetAutopilotProfile_Response__Sequence__create(size_t size);

/// Destroy array of srv/SetAutopilotProfile messages.
/**
 * It calls
 * vehicle_core__srv__SetAutopilotProfile_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
void
vehicle_core__srv__SetAutopilotProfile_Response__Sequence__destroy(vehicle_core__srv__SetAutopilotProfile_Response__Sequence * array);

/// Check for srv/SetAutopilotProfile message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vehicle_core
bool
vehicle_core__srv__SetAutopilotProfile_Response__Sequence__are_equal(const vehicle_core__srv__SetAutopilotProfile_Response__Sequence * lhs, const vehicle_core__srv__SetAutopilotProfile_Response__Sequence * rhs);

/// Copy an array of srv/SetAutopilotProfile messages.
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
vehicle_core__srv__SetAutopilotProfile_Response__Sequence__copy(
  const vehicle_core__srv__SetAutopilotProfile_Response__Sequence * input,
  vehicle_core__srv__SetAutopilotProfile_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CORE__SRV__DETAIL__SET_AUTOPILOT_PROFILE__FUNCTIONS_H_
