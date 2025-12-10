# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_core:msg/IMUStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_IMUStatus(type):
    """Metaclass of message 'IMUStatus'."""

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
                'vehicle_core.msg.IMUStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__imu_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__imu_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__imu_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__imu_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__imu_status

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class IMUStatus(metaclass=Metaclass_IMUStatus):
    """Message class 'IMUStatus'."""

    __slots__ = [
        '_header',
        '_imu_data_ok',
        '_calib_sys',
        '_calib_gyro',
        '_calib_accel',
        '_calib_mag',
        '_op_mode',
        '_err_code',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'imu_data_ok': 'boolean',
        'calib_sys': 'uint8',
        'calib_gyro': 'uint8',
        'calib_accel': 'uint8',
        'calib_mag': 'uint8',
        'op_mode': 'uint8',
        'err_code': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
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
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.imu_data_ok = kwargs.get('imu_data_ok', bool())
        self.calib_sys = kwargs.get('calib_sys', int())
        self.calib_gyro = kwargs.get('calib_gyro', int())
        self.calib_accel = kwargs.get('calib_accel', int())
        self.calib_mag = kwargs.get('calib_mag', int())
        self.op_mode = kwargs.get('op_mode', int())
        self.err_code = kwargs.get('err_code', int())

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
        if self.header != other.header:
            return False
        if self.imu_data_ok != other.imu_data_ok:
            return False
        if self.calib_sys != other.calib_sys:
            return False
        if self.calib_gyro != other.calib_gyro:
            return False
        if self.calib_accel != other.calib_accel:
            return False
        if self.calib_mag != other.calib_mag:
            return False
        if self.op_mode != other.op_mode:
            return False
        if self.err_code != other.err_code:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def imu_data_ok(self):
        """Message field 'imu_data_ok'."""
        return self._imu_data_ok

    @imu_data_ok.setter
    def imu_data_ok(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'imu_data_ok' field must be of type 'bool'"
        self._imu_data_ok = value

    @builtins.property
    def calib_sys(self):
        """Message field 'calib_sys'."""
        return self._calib_sys

    @calib_sys.setter
    def calib_sys(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'calib_sys' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'calib_sys' field must be an unsigned integer in [0, 255]"
        self._calib_sys = value

    @builtins.property
    def calib_gyro(self):
        """Message field 'calib_gyro'."""
        return self._calib_gyro

    @calib_gyro.setter
    def calib_gyro(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'calib_gyro' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'calib_gyro' field must be an unsigned integer in [0, 255]"
        self._calib_gyro = value

    @builtins.property
    def calib_accel(self):
        """Message field 'calib_accel'."""
        return self._calib_accel

    @calib_accel.setter
    def calib_accel(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'calib_accel' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'calib_accel' field must be an unsigned integer in [0, 255]"
        self._calib_accel = value

    @builtins.property
    def calib_mag(self):
        """Message field 'calib_mag'."""
        return self._calib_mag

    @calib_mag.setter
    def calib_mag(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'calib_mag' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'calib_mag' field must be an unsigned integer in [0, 255]"
        self._calib_mag = value

    @builtins.property
    def op_mode(self):
        """Message field 'op_mode'."""
        return self._op_mode

    @op_mode.setter
    def op_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'op_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'op_mode' field must be an unsigned integer in [0, 255]"
        self._op_mode = value

    @builtins.property
    def err_code(self):
        """Message field 'err_code'."""
        return self._err_code

    @err_code.setter
    def err_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'err_code' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'err_code' field must be an unsigned integer in [0, 255]"
        self._err_code = value
