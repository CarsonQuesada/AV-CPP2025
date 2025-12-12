# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/ServerInit.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ServerInit(type):
    """Metaclass of message 'ServerInit'."""

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
                'vehicle_core.msg.ServerInit')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__server_init
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__server_init
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__server_init
            cls._TYPE_SUPPORT = module.type_support_msg__msg__server_init
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__server_init

            from vehicle_core.msg import AutopilotStatus
            if AutopilotStatus.__class__._TYPE_SUPPORT is None:
                AutopilotStatus.__class__.__import_type_support__()

            from vehicle_core.msg import DriveStatus
            if DriveStatus.__class__._TYPE_SUPPORT is None:
                DriveStatus.__class__.__import_type_support__()

            from vehicle_core.msg import GeneralStatus
            if GeneralStatus.__class__._TYPE_SUPPORT is None:
                GeneralStatus.__class__.__import_type_support__()

            from vehicle_core.msg import LightsStatus
            if LightsStatus.__class__._TYPE_SUPPORT is None:
                LightsStatus.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ServerInit(metaclass=Metaclass_ServerInit):
    """Message class 'ServerInit'."""

    __slots__ = [
        '_general_status',
        '_lights_status',
        '_drive_status',
        '_autopilot_status',
    ]

    _fields_and_field_types = {
        'general_status': 'vehicle_core/GeneralStatus',
        'lights_status': 'vehicle_core/LightsStatus',
        'drive_status': 'vehicle_core/DriveStatus',
        'autopilot_status': 'vehicle_core/AutopilotStatus',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['vehicle_core', 'msg'], 'GeneralStatus'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vehicle_core', 'msg'], 'LightsStatus'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vehicle_core', 'msg'], 'DriveStatus'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vehicle_core', 'msg'], 'AutopilotStatus'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from vehicle_core.msg import GeneralStatus
        self.general_status = kwargs.get('general_status', GeneralStatus())
        from vehicle_core.msg import LightsStatus
        self.lights_status = kwargs.get('lights_status', LightsStatus())
        from vehicle_core.msg import DriveStatus
        self.drive_status = kwargs.get('drive_status', DriveStatus())
        from vehicle_core.msg import AutopilotStatus
        self.autopilot_status = kwargs.get('autopilot_status', AutopilotStatus())

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
        if self.general_status != other.general_status:
            return False
        if self.lights_status != other.lights_status:
            return False
        if self.drive_status != other.drive_status:
            return False
        if self.autopilot_status != other.autopilot_status:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def general_status(self):
        """Message field 'general_status'."""
        return self._general_status

    @general_status.setter
    def general_status(self, value):
        if __debug__:
            from vehicle_core.msg import GeneralStatus
            assert \
                isinstance(value, GeneralStatus), \
                "The 'general_status' field must be a sub message of type 'GeneralStatus'"
        self._general_status = value

    @builtins.property
    def lights_status(self):
        """Message field 'lights_status'."""
        return self._lights_status

    @lights_status.setter
    def lights_status(self, value):
        if __debug__:
            from vehicle_core.msg import LightsStatus
            assert \
                isinstance(value, LightsStatus), \
                "The 'lights_status' field must be a sub message of type 'LightsStatus'"
        self._lights_status = value

    @builtins.property
    def drive_status(self):
        """Message field 'drive_status'."""
        return self._drive_status

    @drive_status.setter
    def drive_status(self, value):
        if __debug__:
            from vehicle_core.msg import DriveStatus
            assert \
                isinstance(value, DriveStatus), \
                "The 'drive_status' field must be a sub message of type 'DriveStatus'"
        self._drive_status = value

    @builtins.property
    def autopilot_status(self):
        """Message field 'autopilot_status'."""
        return self._autopilot_status

    @autopilot_status.setter
    def autopilot_status(self, value):
        if __debug__:
            from vehicle_core.msg import AutopilotStatus
            assert \
                isinstance(value, AutopilotStatus), \
                "The 'autopilot_status' field must be a sub message of type 'AutopilotStatus'"
        self._autopilot_status = value
