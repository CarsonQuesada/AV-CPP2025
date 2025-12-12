// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:msg/ServerInit.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "vehicle_core/msg/detail/server_init__struct.h"
#include "vehicle_core/msg/detail/server_init__functions.h"

bool vehicle_core__msg__general_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_core__msg__general_status__convert_to_py(void * raw_ros_message);
bool vehicle_core__msg__lights_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_core__msg__lights_status__convert_to_py(void * raw_ros_message);
bool vehicle_core__msg__drive_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_core__msg__drive_status__convert_to_py(void * raw_ros_message);
bool vehicle_core__msg__autopilot_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vehicle_core__msg__autopilot_status__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__msg__server_init__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[41];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("vehicle_core.msg._server_init.ServerInit", full_classname_dest, 40) == 0);
  }
  vehicle_core__msg__ServerInit * ros_message = _ros_message;
  {  // general_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "general_status");
    if (!field) {
      return false;
    }
    if (!vehicle_core__msg__general_status__convert_from_py(field, &ros_message->general_status)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // lights_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "lights_status");
    if (!field) {
      return false;
    }
    if (!vehicle_core__msg__lights_status__convert_from_py(field, &ros_message->lights_status)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // drive_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "drive_status");
    if (!field) {
      return false;
    }
    if (!vehicle_core__msg__drive_status__convert_from_py(field, &ros_message->drive_status)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // autopilot_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "autopilot_status");
    if (!field) {
      return false;
    }
    if (!vehicle_core__msg__autopilot_status__convert_from_py(field, &ros_message->autopilot_status)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__msg__server_init__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ServerInit */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.msg._server_init");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ServerInit");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__msg__ServerInit * ros_message = (vehicle_core__msg__ServerInit *)raw_ros_message;
  {  // general_status
    PyObject * field = NULL;
    field = vehicle_core__msg__general_status__convert_to_py(&ros_message->general_status);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "general_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // lights_status
    PyObject * field = NULL;
    field = vehicle_core__msg__lights_status__convert_to_py(&ros_message->lights_status);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "lights_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // drive_status
    PyObject * field = NULL;
    field = vehicle_core__msg__drive_status__convert_to_py(&ros_message->drive_status);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "drive_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // autopilot_status
    PyObject * field = NULL;
    field = vehicle_core__msg__autopilot_status__convert_to_py(&ros_message->autopilot_status);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "autopilot_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
