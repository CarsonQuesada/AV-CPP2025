// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:msg/DriveFeedback.idl
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
#include "vehicle_core/msg/detail/drive_feedback__struct.h"
#include "vehicle_core/msg/detail/drive_feedback__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__msg__drive_feedback__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[47];
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
    assert(strncmp("vehicle_core.msg._drive_feedback.DriveFeedback", full_classname_dest, 46) == 0);
  }
  vehicle_core__msg__DriveFeedback * ros_message = _ros_message;
  {  // speed_mmps
    PyObject * field = PyObject_GetAttrString(_pymsg, "speed_mmps");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->speed_mmps = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // steer_millirad
    PyObject * field = PyObject_GetAttrString(_pymsg, "steer_millirad");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->steer_millirad = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__msg__drive_feedback__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of DriveFeedback */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.msg._drive_feedback");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "DriveFeedback");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__msg__DriveFeedback * ros_message = (vehicle_core__msg__DriveFeedback *)raw_ros_message;
  {  // speed_mmps
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->speed_mmps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "speed_mmps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // steer_millirad
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->steer_millirad);
    {
      int rc = PyObject_SetAttrString(_pymessage, "steer_millirad", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
