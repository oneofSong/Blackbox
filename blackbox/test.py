from ctypes import *
import ctypes

Util = CDLL('./blackbox_Util.so')

get_time = Util.get_time
mkdir = Util.make_directory

class TimeStruct(Structure):
    _fields_ = [\
        ("tm_sec", ctypes.c_int),\
        ("tm_min", ctypes.c_int),\
        ("tm_hour", ctypes.c_int),\
        ("tm_mday", ctypes.c_int),\
        ("tm_mon", ctypes.c_int),\
        ("tm_year", ctypes.c_int),\
        ("tm_wday", ctypes.c_int),\
        ("tm_yday", ctypes.c_int),\
        ("tm_isdst", ctypes.c_int),\
    ]

get_time.restype = TimeStruct
buf = create_string_buffer(b'\000' * 64)
buf_ptr = pointer(buf)
file_type = c_char(b'd')

tm = get_time(buf_ptr, file_type)
print(tm.tm_hour , tm.tm_min , tm.tm_sec)
print(buf_ptr.contents[:11])

mkdir(buf_ptr)
