// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:msg/IMUStatus.idl
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
#include "vehicle_core/msg/detail/imu_status__struct.h"
#include "vehicle_core/msg/detail/imu_status__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__msg__imu_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[39];
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
    assert(strncmp("vehicle_core.msg._imu_status.IMUStatus", full_classname_dest, 38) == 0);
  }
  vehicle_core__msg__IMUStatus * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // imu_data_ok
    PyObject * field = PyObject_GetAttrString(_pymsg, "imu_data_ok");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->imu_data_ok = (Py_True == field);
    Py_DECREF(field);
  }
  {  // calib_sys
    PyObject * field = PyObject_GetAttrString(_pymsg, "calib_sys");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->calib_sys = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // calib_gyro
    PyObject * field = PyObject_GetAttrString(_pymsg, "calib_gyro");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->calib_gyro = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // calib_accel
    PyObject * field = PyObject_GetAttrString(_pymsg, "calib_accel");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->calib_accel = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // calib_mag
    PyObject * field = PyObject_GetAttrString(_pymsg, "calib_mag");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->calib_mag = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // op_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "op_mode");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->op_mode = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // err_code
    PyObject * field = PyObject_GetAttrString(_pymsg, "err_code");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->err_code = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__msg__imu_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of IMUStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.msg._imu_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "IMUStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__msg__IMUStatus * ros_message = (vehicle_core__msg__IMUStatus *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // imu_data_ok
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->imu_data_ok ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "imu_data_ok", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // calib_sys
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->calib_sys);
    {
      int rc = PyObject_SetAttrString(_pymessage, "calib_sys", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // calib_gyro
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->calib_gyro);
    {
      int rc = PyObject_SetAttrString(_pymessage, "calib_gyro", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // calib_accel
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->calib_accel);
    {
      int rc = PyObject_SetAttrString(_pymessage, "calib_accel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // calib_mag
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->calib_mag);
    {
      int rc = PyObject_SetAttrString(_pymessage, "calib_mag", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // op_mode
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->op_mode);
    {
      int rc = PyObject_SetAttrString(_pymessage, "op_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // err_code
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->err_code);
    {
      int rc = PyObject_SetAttrString(_pymessage, "err_code", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
