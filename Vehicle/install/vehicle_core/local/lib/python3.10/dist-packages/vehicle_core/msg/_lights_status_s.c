// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:msg/LightsStatus.idl
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
#include "vehicle_core/msg/detail/lights_status__struct.h"
#include "vehicle_core/msg/detail/lights_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__msg__lights_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[45];
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
    assert(strncmp("vehicle_core.msg._lights_status.LightsStatus", full_classname_dest, 44) == 0);
  }
  vehicle_core__msg__LightsStatus * ros_message = _ros_message;
  {  // brake_lights
    PyObject * field = PyObject_GetAttrString(_pymsg, "brake_lights");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->brake_lights = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // reverse_lights
    PyObject * field = PyObject_GetAttrString(_pymsg, "reverse_lights");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->reverse_lights = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // right_sig
    PyObject * field = PyObject_GetAttrString(_pymsg, "right_sig");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->right_sig = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // left_sig
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_sig");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->left_sig = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // headlights
    PyObject * field = PyObject_GetAttrString(_pymsg, "headlights");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->headlights = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // hazards
    PyObject * field = PyObject_GetAttrString(_pymsg, "hazards");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->hazards = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__msg__lights_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of LightsStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.msg._lights_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "LightsStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__msg__LightsStatus * ros_message = (vehicle_core__msg__LightsStatus *)raw_ros_message;
  {  // brake_lights
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->brake_lights);
    {
      int rc = PyObject_SetAttrString(_pymessage, "brake_lights", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reverse_lights
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->reverse_lights);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reverse_lights", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // right_sig
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->right_sig);
    {
      int rc = PyObject_SetAttrString(_pymessage, "right_sig", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // left_sig
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->left_sig);
    {
      int rc = PyObject_SetAttrString(_pymessage, "left_sig", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // headlights
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->headlights);
    {
      int rc = PyObject_SetAttrString(_pymessage, "headlights", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // hazards
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->hazards);
    {
      int rc = PyObject_SetAttrString(_pymessage, "hazards", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
