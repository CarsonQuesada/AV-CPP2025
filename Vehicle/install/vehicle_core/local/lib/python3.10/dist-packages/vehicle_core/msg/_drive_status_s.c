// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:msg/DriveStatus.idl
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
#include "vehicle_core/msg/detail/drive_status__struct.h"
#include "vehicle_core/msg/detail/drive_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__msg__drive_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[43];
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
    assert(strncmp("vehicle_core.msg._drive_status.DriveStatus", full_classname_dest, 42) == 0);
  }
  vehicle_core__msg__DriveStatus * ros_message = _ros_message;
  {  // gear
    PyObject * field = PyObject_GetAttrString(_pymsg, "gear");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->gear = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // braking
    PyObject * field = PyObject_GetAttrString(_pymsg, "braking");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->braking = (Py_True == field);
    Py_DECREF(field);
  }
  {  // fault_bits
    PyObject * field = PyObject_GetAttrString(_pymsg, "fault_bits");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fault_bits = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__msg__drive_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of DriveStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.msg._drive_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "DriveStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__msg__DriveStatus * ros_message = (vehicle_core__msg__DriveStatus *)raw_ros_message;
  {  // gear
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->gear);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gear", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // braking
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->braking ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "braking", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fault_bits
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fault_bits);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fault_bits", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
