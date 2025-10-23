# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/LightsStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LightsStatus(type):
    """Metaclass of message 'LightsStatus'."""

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
                'vehicle_core.msg.LightsStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__lights_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__lights_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__lights_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__lights_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__lights_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class LightsStatus(metaclass=Metaclass_LightsStatus):
    """Message class 'LightsStatus'."""

    __slots__ = [
        '_brake_lights',
        '_reverse_lights',
        '_right_sig',
        '_left_sig',
        '_headlights',
        '_hazards',
    ]

    _fields_and_field_types = {
        'brake_lights': 'uint8',
        'reverse_lights': 'uint8',
        'right_sig': 'uint8',
        'left_sig': 'uint8',
        'headlights': 'uint8',
        'hazards': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.brake_lights = kwargs.get('brake_lights', int())
        self.reverse_lights = kwargs.get('reverse_lights', int())
        self.right_sig = kwargs.get('right_sig', int())
        self.left_sig = kwargs.get('left_sig', int())
        self.headlights = kwargs.get('headlights', int())
        self.hazards = kwargs.get('hazards', int())

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
        if self.brake_lights != other.brake_lights:
            return False
        if self.reverse_lights != other.reverse_lights:
            return False
        if self.right_sig != other.right_sig:
            return False
        if self.left_sig != other.left_sig:
            return False
        if self.headlights != other.headlights:
            return False
        if self.hazards != other.hazards:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def brake_lights(self):
        """Message field 'brake_lights'."""
        return self._brake_lights

    @brake_lights.setter
    def brake_lights(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'brake_lights' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'brake_lights' field must be an unsigned integer in [0, 255]"
        self._brake_lights = value

    @builtins.property
    def reverse_lights(self):
        """Message field 'reverse_lights'."""
        return self._reverse_lights

    @reverse_lights.setter
    def reverse_lights(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'reverse_lights' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'reverse_lights' field must be an unsigned integer in [0, 255]"
        self._reverse_lights = value

    @builtins.property
    def right_sig(self):
        """Message field 'right_sig'."""
        return self._right_sig

    @right_sig.setter
    def right_sig(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'right_sig' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'right_sig' field must be an unsigned integer in [0, 255]"
        self._right_sig = value

    @builtins.property
    def left_sig(self):
        """Message field 'left_sig'."""
        return self._left_sig

    @left_sig.setter
    def left_sig(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'left_sig' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'left_sig' field must be an unsigned integer in [0, 255]"
        self._left_sig = value

    @builtins.property
    def headlights(self):
        """Message field 'headlights'."""
        return self._headlights

    @headlights.setter
    def headlights(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'headlights' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'headlights' field must be an unsigned integer in [0, 255]"
        self._headlights = value

    @builtins.property
    def hazards(self):
        """Message field 'hazards'."""
        return self._hazards

    @hazards.setter
    def hazards(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'hazards' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'hazards' field must be an unsigned integer in [0, 255]"
        self._hazards = value
