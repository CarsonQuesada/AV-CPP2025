// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_core:srv/SetAutopilotProfile.idl
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
#include "vehicle_core/srv/detail/set_autopilot_profile__struct.h"
#include "vehicle_core/srv/detail/set_autopilot_profile__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__srv__set_autopilot_profile__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[68];
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
    assert(strncmp("vehicle_core.srv._set_autopilot_profile.SetAutopilotProfile_Request", full_classname_dest, 67) == 0);
  }
  vehicle_core__srv__SetAutopilotProfile_Request * ros_message = _ros_message;
  {  // set_profile_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "set_profile_id");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->set_profile_id = (Py_True == field);
    Py_DECREF(field);
  }
  {  // profile_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "profile_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->profile_id = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // set_features_mask
    PyObject * field = PyObject_GetAttrString(_pymsg, "set_features_mask");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->set_features_mask = (Py_True == field);
    Py_DECREF(field);
  }
  {  // features_mask
    PyObject * field = PyObject_GetAttrString(_pymsg, "features_mask");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->features_mask = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // set_params
    PyObject * field = PyObject_GetAttrString(_pymsg, "set_params");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->set_params = (Py_True == field);
    Py_DECREF(field);
  }
  {  // keys
    PyObject * field = PyObject_GetAttrString(_pymsg, "keys");
    if (!field) {
      return false;
    }
    {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'keys'");
      if (!seq_field) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = PySequence_Size(field);
      if (-1 == size) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      if (!rosidl_runtime_c__String__Sequence__init(&(ros_message->keys), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create String__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      rosidl_runtime_c__String * dest = ros_message->keys.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyUnicode_Check(item));
        PyObject * encoded_item = PyUnicode_AsUTF8String(item);
        if (!encoded_item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        rosidl_runtime_c__String__assign(&dest[i], PyBytes_AS_STRING(encoded_item));
        Py_DECREF(encoded_item);
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }
  {  // values
    PyObject * field = PyObject_GetAttrString(_pymsg, "values");
    if (!field) {
      return false;
    }
    if (PyObject_CheckBuffer(field)) {
      // Optimization for converting arrays of primitives
      Py_buffer view;
      int rc = PyObject_GetBuffer(field, &view, PyBUF_SIMPLE);
      if (rc < 0) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = view.len / sizeof(double);
      if (!rosidl_runtime_c__double__Sequence__init(&(ros_message->values), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create double__Sequence ros_message");
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      double * dest = ros_message->values.data;
      rc = PyBuffer_ToContiguous(dest, &view, view.len, 'C');
      if (rc < 0) {
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      PyBuffer_Release(&view);
    } else {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'values'");
      if (!seq_field) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = PySequence_Size(field);
      if (-1 == size) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      if (!rosidl_runtime_c__double__Sequence__init(&(ros_message->values), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create double__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      double * dest = ros_message->values.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyFloat_Check(item));
        double tmp = PyFloat_AS_DOUBLE(item);
        memcpy(&dest[i], &tmp, sizeof(double));
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__srv__set_autopilot_profile__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SetAutopilotProfile_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.srv._set_autopilot_profile");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SetAutopilotProfile_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__srv__SetAutopilotProfile_Request * ros_message = (vehicle_core__srv__SetAutopilotProfile_Request *)raw_ros_message;
  {  // set_profile_id
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->set_profile_id ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "set_profile_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // profile_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->profile_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "profile_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // set_features_mask
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->set_features_mask ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "set_features_mask", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // features_mask
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->features_mask);
    {
      int rc = PyObject_SetAttrString(_pymessage, "features_mask", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // set_params
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->set_params ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "set_params", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // keys
    PyObject * field = NULL;
    size_t size = ros_message->keys.size;
    rosidl_runtime_c__String * src = ros_message->keys.data;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
      PyObject * decoded_item = PyUnicode_DecodeUTF8(src[i].data, strlen(src[i].data), "replace");
      if (!decoded_item) {
        return NULL;
      }
      int rc = PyList_SetItem(field, i, decoded_item);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "keys", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // values
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "values");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "array.array") == 0);
    // ensure that itemsize matches the sizeof of the ROS message field
    PyObject * itemsize_attr = PyObject_GetAttrString(field, "itemsize");
    assert(itemsize_attr != NULL);
    size_t itemsize = PyLong_AsSize_t(itemsize_attr);
    Py_DECREF(itemsize_attr);
    if (itemsize != sizeof(double)) {
      PyErr_SetString(PyExc_RuntimeError, "itemsize doesn't match expectation");
      Py_DECREF(field);
      return NULL;
    }
    // clear the array, poor approach to remove potential default values
    Py_ssize_t length = PyObject_Length(field);
    if (-1 == length) {
      Py_DECREF(field);
      return NULL;
    }
    if (length > 0) {
      PyObject * pop = PyObject_GetAttrString(field, "pop");
      assert(pop != NULL);
      for (Py_ssize_t i = 0; i < length; ++i) {
        PyObject * ret = PyObject_CallFunctionObjArgs(pop, NULL);
        if (!ret) {
          Py_DECREF(pop);
          Py_DECREF(field);
          return NULL;
        }
        Py_DECREF(ret);
      }
      Py_DECREF(pop);
    }
    if (ros_message->values.size > 0) {
      // populating the array.array using the frombytes method
      PyObject * frombytes = PyObject_GetAttrString(field, "frombytes");
      assert(frombytes != NULL);
      double * src = &(ros_message->values.data[0]);
      PyObject * data = PyBytes_FromStringAndSize((const char *)src, ros_message->values.size * sizeof(double));
      assert(data != NULL);
      PyObject * ret = PyObject_CallFunctionObjArgs(frombytes, data, NULL);
      Py_DECREF(data);
      Py_DECREF(frombytes);
      if (!ret) {
        Py_DECREF(field);
        return NULL;
      }
      Py_DECREF(ret);
    }
    Py_DECREF(field);
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__struct.h"
// already included above
// #include "vehicle_core/srv/detail/set_autopilot_profile__functions.h"

// already included above
// #include "rosidl_runtime_c/string.h"
// already included above
// #include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_core__srv__set_autopilot_profile__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[69];
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
    assert(strncmp("vehicle_core.srv._set_autopilot_profile.SetAutopilotProfile_Response", full_classname_dest, 68) == 0);
  }
  vehicle_core__srv__SetAutopilotProfile_Response * ros_message = _ros_message;
  {  // success
    PyObject * field = PyObject_GetAttrString(_pymsg, "success");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->success = (Py_True == field);
    Py_DECREF(field);
  }
  {  // message
    PyObject * field = PyObject_GetAttrString(_pymsg, "message");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->message, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_core__srv__set_autopilot_profile__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SetAutopilotProfile_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_core.srv._set_autopilot_profile");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SetAutopilotProfile_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_core__srv__SetAutopilotProfile_Response * ros_message = (vehicle_core__srv__SetAutopilotProfile_Response *)raw_ros_message;
  {  // success
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->success ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "success", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // message
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->message.data,
      strlen(ros_message->message.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "message", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
