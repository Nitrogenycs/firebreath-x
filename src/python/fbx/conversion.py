from FireBreath import *

def ConvertToPy(value):
    _type_ = value.get_type()
    
    if _type_ == "bool":
        return value.get_bool()
    elif _type_ == "int":
        return value.get_int()
    elif _type_ == "uint":
        return value.get_uint()
    elif _type_ == "double":
        return value.get_double()
    elif _type_ == "float":
        return value.get_float()
    elif _type_ == "wstring":
        return value.get_wstring()
    elif _type_ ==  "short":
        return value.get_short()
    elif _type_ ==  "ushort":
        return value.get_ushort()
    elif _type_ ==  "char":
        return value.get_char()
    elif _type_ ==  "uchar":
        return value.get_uchar()
    elif _type_ ==  "int64":
        return value.get_int64()
    elif _type_ ==  "uint64":
        return value.get_uint64()
    else:
        # throw bad cast exception here?
        raise RuntimeError("Unknown type")


def ConvertFromPy(value):
    result = fbxvariant()
    # automatic converted by proxy?
    result.set(value)
    return result
