# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/DriveTarget.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DriveTarget(type):
    """Metaclass of message 'DriveTarget'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vehicle_core')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vehicle_core.msg.DriveTarget')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__drive_target
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__drive_target
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__drive_target
            cls._TYPE_SUPPORT = module.type_support_msg__msg__drive_target
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__drive_target

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DriveTarget(metaclass=Metaclass_DriveTarget):
    """Message class 'DriveTarget'."""

    __slots__ = [
        '_brake_percent',
        '_target_speed_mmps',
        '_target_steer_millirad',
    ]

    _fields_and_field_types = {
        'brake_percent': 'uint8',
        'target_speed_mmps': 'int16',
        'target_steer_millirad': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.brake_percent = kwargs.get('brake_percent', int())
        self.target_speed_mmps = kwargs.get('target_speed_mmps', int())
        self.target_steer_millirad = kwargs.get('target_steer_millirad', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.brake_percent != other.brake_percent:
            return False
        if self.target_speed_mmps != other.target_speed_mmps:
            return False
        if self.target_steer_millirad != other.target_steer_millirad:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def brake_percent(self):
        """Message field 'brake_percent'."""
        return self._brake_percent

    @brake_percent.setter
    def brake_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'brake_percent' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'brake_percent' field must be an unsigned integer in [0, 255]"
        self._brake_percent = value

    @builtins.property
    def target_speed_mmps(self):
        """Message field 'target_speed_mmps'."""
        return self._target_speed_mmps

    @target_speed_mmps.setter
    def target_speed_mmps(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'target_speed_mmps' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'target_speed_mmps' field must be an integer in [-32768, 32767]"
        self._target_speed_mmps = value

    @builtins.property
    def target_steer_millirad(self):
        """Message field 'target_steer_millirad'."""
        return self._target_steer_millirad

    @target_steer_millirad.setter
    def target_steer_millirad(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'target_steer_millirad' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'target_steer_millirad' field must be an integer in [-32768, 32767]"
        self._target_steer_millirad = value
