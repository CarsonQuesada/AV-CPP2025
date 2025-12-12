// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:msg/AutopilotStatus.idl
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
#include "vehicle_core/msg/detail/autopilot_status__struct.h"
#include "vehicle_core/msg/detail/autopilot_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__msg__autopilot_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[51];
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
    assert(strncmp("vehicle_core.msg._autopilot_status.AutopilotStatus", full_classname_dest, 50) == 0);
  }
  vehicle_core__msg__AutopilotStatus * ros_message = _ros_message;
  {  // autopilot_ready
    PyObject * field = PyObject_GetAttrString(_pymsg, "autopilot_ready");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->autopilot_ready = (Py_True == field);
    Py_DECREF(field);
  }
  {  // lidar_ready
    PyObject * field = PyObject_GetAttrString(_pymsg, "lidar_ready");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->lidar_ready = (Py_True == field);
    Py_DECREF(field);
  }
  {  // camera_ready
    PyObject * field = PyObject_GetAttrString(_pymsg, "camera_ready");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->camera_ready = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__msg__autopilot_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of AutopilotStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.msg._autopilot_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "AutopilotStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__msg__AutopilotStatus * ros_message = (vehicle_core__msg__AutopilotStatus *)raw_ros_message;
  {  // autopilot_ready
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->autopilot_ready ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "autopilot_ready", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // lidar_ready
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->lidar_ready ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "lidar_ready", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // camera_ready
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->camera_ready ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "camera_ready", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
