# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/TelemetryData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TelemetryData(type):
    """Metaclass of message 'TelemetryData'."""

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
                'vehicle_core.msg.TelemetryData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__telemetry_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__telemetry_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__telemetry_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__telemetry_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__telemetry_data

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TelemetryData(metaclass=Metaclass_TelemetryData):
    """Message class 'TelemetryData'."""

    __slots__ = [
        '_gps_online',
        '_lat',
        '_lon',
        '_heading',
        '_speed',
        '_distance_delta',
    ]

    _fields_and_field_types = {
        'gps_online': 'boolean',
        'lat': 'float',
        'lon': 'float',
        'heading': 'float',
        'speed': 'float',
        'distance_delta': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.gps_online = kwargs.get('gps_online', bool())
        self.lat = kwargs.get('lat', float())
        self.lon = kwargs.get('lon', float())
        self.heading = kwargs.get('heading', float())
        self.speed = kwargs.get('speed', float())
        self.distance_delta = kwargs.get('distance_delta', float())

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
        if self.gps_online != other.gps_online:
            return False
        if self.lat != other.lat:
            return False
        if self.lon != other.lon:
            return False
        if self.heading != other.heading:
            return False
        if self.speed != other.speed:
            return False
        if self.distance_delta != other.distance_delta:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def gps_online(self):
        """Message field 'gps_online'."""
        return self._gps_online

    @gps_online.setter
    def gps_online(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gps_online' field must be of type 'bool'"
        self._gps_online = value

    @builtins.property
    def lat(self):
        """Message field 'lat'."""
        return self._lat

    @lat.setter
    def lat(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'lat' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'lat' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._lat = value

    @builtins.property
    def lon(self):
        """Message field 'lon'."""
        return self._lon

    @lon.setter
    def lon(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'lon' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'lon' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._lon = value

    @builtins.property
    def heading(self):
        """Message field 'heading'."""
        return self._heading

    @heading.setter
    def heading(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'heading' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'heading' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._heading = value

    @builtins.property
    def speed(self):
        """Message field 'speed'."""
        return self._speed

    @speed.setter
    def speed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'speed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'speed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._speed = value

    @builtins.property
    def distance_delta(self):
        """Message field 'distance_delta'."""
        return self._distance_delta

    @distance_delta.setter
    def distance_delta(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'distance_delta' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'distance_delta' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._distance_delta = value
