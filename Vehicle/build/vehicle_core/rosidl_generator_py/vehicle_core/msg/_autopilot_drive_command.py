# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/AutopilotDriveCommand.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AutopilotDriveCommand(type):
    """Metaclass of message 'AutopilotDriveCommand'."""

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
                'vehicle_core.msg.AutopilotDriveCommand')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__autopilot_drive_command
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__autopilot_drive_command
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__autopilot_drive_command
            cls._TYPE_SUPPORT = module.type_support_msg__msg__autopilot_drive_command
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__autopilot_drive_command

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AutopilotDriveCommand(metaclass=Metaclass_AutopilotDriveCommand):
    """Message class 'AutopilotDriveCommand'."""

    __slots__ = [
        '_brake',
        '_gear',
        '_speed_mps',
        '_steer_rad',
    ]

    _fields_and_field_types = {
        'brake': 'uint8',
        'gear': 'uint8',
        'speed_mps': 'float',
        'steer_rad': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.brake = kwargs.get('brake', int())
        self.gear = kwargs.get('gear', int())
        self.speed_mps = kwargs.get('speed_mps', float())
        self.steer_rad = kwargs.get('steer_rad', float())

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
        if self.brake != other.brake:
            return False
        if self.gear != other.gear:
            return False
        if self.speed_mps != other.speed_mps:
            return False
        if self.steer_rad != other.steer_rad:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def brake(self):
        """Message field 'brake'."""
        return self._brake

    @brake.setter
    def brake(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'brake' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'brake' field must be an unsigned integer in [0, 255]"
        self._brake = value

    @builtins.property
    def gear(self):
        """Message field 'gear'."""
        return self._gear

    @gear.setter
    def gear(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'gear' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'gear' field must be an unsigned integer in [0, 255]"
        self._gear = value

    @builtins.property
    def speed_mps(self):
        """Message field 'speed_mps'."""
        return self._speed_mps

    @speed_mps.setter
    def speed_mps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'speed_mps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'speed_mps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._speed_mps = value

    @builtins.property
    def steer_rad(self):
        """Message field 'steer_rad'."""
        return self._steer_rad

    @steer_rad.setter
    def steer_rad(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'steer_rad' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'steer_rad' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._steer_rad = value
