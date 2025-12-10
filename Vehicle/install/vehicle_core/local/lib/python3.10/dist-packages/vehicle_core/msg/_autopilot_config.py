# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/AutopilotConfig.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'values'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AutopilotConfig(type):
    """Metaclass of message 'AutopilotConfig'."""

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
                'vehicle_core.msg.AutopilotConfig')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__autopilot_config
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__autopilot_config
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__autopilot_config
            cls._TYPE_SUPPORT = module.type_support_msg__msg__autopilot_config
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__autopilot_config

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AutopilotConfig(metaclass=Metaclass_AutopilotConfig):
    """Message class 'AutopilotConfig'."""

    __slots__ = [
        '_profile_id',
        '_features_mask',
        '_keys',
        '_values',
    ]

    _fields_and_field_types = {
        'profile_id': 'uint8',
        'features_mask': 'uint8',
        'keys': 'sequence<string>',
        'values': 'sequence<double>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.profile_id = kwargs.get('profile_id', int())
        self.features_mask = kwargs.get('features_mask', int())
        self.keys = kwargs.get('keys', [])
        self.values = array.array('d', kwargs.get('values', []))

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
        if self.profile_id != other.profile_id:
            return False
        if self.features_mask != other.features_mask:
            return False
        if self.keys != other.keys:
            return False
        if self.values != other.values:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def profile_id(self):
        """Message field 'profile_id'."""
        return self._profile_id

    @profile_id.setter
    def profile_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'profile_id' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'profile_id' field must be an unsigned integer in [0, 255]"
        self._profile_id = value

    @builtins.property
    def features_mask(self):
        """Message field 'features_mask'."""
        return self._features_mask

    @features_mask.setter
    def features_mask(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'features_mask' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'features_mask' field must be an unsigned integer in [0, 255]"
        self._features_mask = value

    @builtins.property
    def keys(self):
        """Message field 'keys'."""
        return self._keys

    @keys.setter
    def keys(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'keys' field must be a set or sequence and each value of type 'str'"
        self._keys = value

    @builtins.property
    def values(self):
        """Message field 'values'."""
        return self._values

    @values.setter
    def values(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'values' array.array() must have the type code of 'd'"
            self._values = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'values' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._values = array.array('d', value)
