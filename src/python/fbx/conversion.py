from FireBreath import *

def ConvertToPy(value):
	val = value.get_type()
	
	if value == "bool":
		return value.get_bool()
    elif value == "int":
        return value.get_int()
    elif value == "uint":
        return value.get_uint()
	elif value == "double":
		return value.get_double()
	elif value == "float":
		return value.get_float()
	elif value == case "wstring":
		return value.get_wstring()
	elif value ==  "short":
		return value.get_short()
	elif value ==  "ushort":
		return value.get_ushort()
	elif value ==  "char":
		return value.get_char()
	elif value ==  "uchar":
		return value.get_uchar()
	elif value ==  "int64":
		return value.get_int64()
	elif value ==  "uint64":
		return value.get_uint64()
	else :
		// throw bad cast exception here?
		return None

    def ConvertFromPy(value):
        result = fbxvariant()
		# automatic converted by proxy?
		result.set(value)
		return result
