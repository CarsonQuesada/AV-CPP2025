// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:msg/AutopilotDriveCommand.idl
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
#include "vehicle_core/msg/detail/autopilot_drive_command__struct.h"
#include "vehicle_core/msg/detail/autopilot_drive_command__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__msg__autopilot_drive_command__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[64];
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
    assert(strncmp("vehicle_core.msg._autopilot_drive_command.AutopilotDriveCommand", full_classname_dest, 63) == 0);
  }
  vehicle_core__msg__AutopilotDriveCommand * ros_message = _ros_message;
  {  // brake
    PyObject * field = PyObject_GetAttrString(_pymsg, "brake");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->brake = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // gear
    PyObject * field = PyObject_GetAttrString(_pymsg, "gear");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->gear = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // speed_mps
    PyObject * field = PyObject_GetAttrString(_pymsg, "speed_mps");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->speed_mps = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // steer_rad
    PyObject * field = PyObject_GetAttrString(_pymsg, "steer_rad");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->steer_rad = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__msg__autopilot_drive_command__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of AutopilotDriveCommand */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.msg._autopilot_drive_command");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "AutopilotDriveCommand");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__msg__AutopilotDriveCommand * ros_message = (vehicle_core__msg__AutopilotDriveCommand *)raw_ros_message;
  {  // brake
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->brake);
    {
      int rc = PyObject_SetAttrString(_pymessage, "brake", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
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
  {  // speed_mps
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->speed_mps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "speed_mps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // steer_rad
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->steer_rad);
    {
      int rc = PyObject_SetAttrString(_pymessage, "steer_rad", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
