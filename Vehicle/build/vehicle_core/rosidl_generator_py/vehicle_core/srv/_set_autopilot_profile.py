# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:srv/SetAutopilotProfile.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'values'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetAutopilotProfile_Request(type):
    """Metaclass of message 'SetAutopilotProfile_Request'."""

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
                'vehicle_core.srv.SetAutopilotProfile_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_autopilot_profile__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_autopilot_profile__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_autopilot_profile__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_autopilot_profile__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_autopilot_profile__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetAutopilotProfile_Request(metaclass=Metaclass_SetAutopilotProfile_Request):
    """Message class 'SetAutopilotProfile_Request'."""

    __slots__ = [
        '_set_profile_id',
        '_profile_id',
        '_set_features_mask',
        '_features_mask',
        '_set_params',
        '_keys',
        '_values',
    ]

    _fields_and_field_types = {
        'set_profile_id': 'boolean',
        'profile_id': 'uint8',
        'set_features_mask': 'boolean',
        'features_mask': 'uint8',
        'set_params': 'boolean',
        'keys': 'sequence<string>',
        'values': 'sequence<double>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.set_profile_id = kwargs.get('set_profile_id', bool())
        self.profile_id = kwargs.get('profile_id', int())
        self.set_features_mask = kwargs.get('set_features_mask', bool())
        self.features_mask = kwargs.get('features_mask', int())
        self.set_params = kwargs.get('set_params', bool())
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
        if self.set_profile_id != other.set_profile_id:
            return False
        if self.profile_id != other.profile_id:
            return False
        if self.set_features_mask != other.set_features_mask:
            return False
        if self.features_mask != other.features_mask:
            return False
        if self.set_params != other.set_params:
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
    def set_profile_id(self):
        """Message field 'set_profile_id'."""
        return self._set_profile_id

    @set_profile_id.setter
    def set_profile_id(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'set_profile_id' field must be of type 'bool'"
        self._set_profile_id = value

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
    def set_features_mask(self):
        """Message field 'set_features_mask'."""
        return self._set_features_mask

    @set_features_mask.setter
    def set_features_mask(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'set_features_mask' field must be of type 'bool'"
        self._set_features_mask = value

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
    def set_params(self):
        """Message field 'set_params'."""
        return self._set_params

    @set_params.setter
    def set_params(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'set_params' field must be of type 'bool'"
        self._set_params = value

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetAutopilotProfile_Response(type):
    """Metaclass of message 'SetAutopilotProfile_Response'."""

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
                'vehicle_core.srv.SetAutopilotProfile_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_autopilot_profile__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_autopilot_profile__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_autopilot_profile__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_autopilot_profile__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_autopilot_profile__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetAutopilotProfile_Response(metaclass=Metaclass_SetAutopilotProfile_Response):
    """Message class 'SetAutopilotProfile_Response'."""

    __slots__ = [
        '_success',
        '_message',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())

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
        if self.success != other.success:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


class Metaclass_SetAutopilotProfile(type):
    """Metaclass of service 'SetAutopilotProfile'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vehicle_core')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vehicle_core.srv.SetAutopilotProfile')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_autopilot_profile

            from vehicle_core.srv import _set_autopilot_profile
            if _set_autopilot_profile.Metaclass_SetAutopilotProfile_Request._TYPE_SUPPORT is None:
                _set_autopilot_profile.Metaclass_SetAutopilotProfile_Request.__import_type_support__()
            if _set_autopilot_profile.Metaclass_SetAutopilotProfile_Response._TYPE_SUPPORT is None:
                _set_autopilot_profile.Metaclass_SetAutopilotProfile_Response.__import_type_support__()


class SetAutopilotProfile(metaclass=Metaclass_SetAutopilotProfile):
    from vehicle_core.srv._set_autopilot_profile import SetAutopilotProfile_Request as Request
    from vehicle_core.srv._set_autopilot_profile import SetAutopilotProfile_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
