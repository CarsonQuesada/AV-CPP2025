# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/AutopilotStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AutopilotStatus(type):
    """Metaclass of message 'AutopilotStatus'."""

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
                'vehicle_core.msg.AutopilotStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__autopilot_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__autopilot_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__autopilot_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__autopilot_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__autopilot_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AutopilotStatus(metaclass=Metaclass_AutopilotStatus):
    """Message class 'AutopilotStatus'."""

    __slots__ = [
        '_autopilot_ready',
        '_lidar_ready',
        '_camera_ready',
    ]

    _fields_and_field_types = {
        'autopilot_ready': 'boolean',
        'lidar_ready': 'boolean',
        'camera_ready': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.autopilot_ready = kwargs.get('autopilot_ready', bool())
        self.lidar_ready = kwargs.get('lidar_ready', bool())
        self.camera_ready = kwargs.get('camera_ready', bool())

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
        if self.autopilot_ready != other.autopilot_ready:
            return False
        if self.lidar_ready != other.lidar_ready:
            return False
        if self.camera_ready != other.camera_ready:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def autopilot_ready(self):
        """Message field 'autopilot_ready'."""
        return self._autopilot_ready

    @autopilot_ready.setter
    def autopilot_ready(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'autopilot_ready' field must be of type 'bool'"
        self._autopilot_ready = value

    @builtins.property
    def lidar_ready(self):
        """Message field 'lidar_ready'."""
        return self._lidar_ready

    @lidar_ready.setter
    def lidar_ready(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'lidar_ready' field must be of type 'bool'"
        self._lidar_ready = value

    @builtins.property
    def camera_ready(self):
        """Message field 'camera_ready'."""
        return self._camera_ready

    @camera_ready.setter
    def camera_ready(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'camera_ready' field must be of type 'bool'"
        self._camera_ready = value
