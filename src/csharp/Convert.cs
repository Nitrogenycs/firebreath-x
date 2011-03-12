using System;
using System.Collections.Generic;

namespace FireBreath
{
    public static class Convert
    {
        public static Object ConvertToNet(this fbnetvariant value)
        {
            switch (value.get_type())
            {
                case "bool":
                    return value.get_bool();
                case "int":
                    return value.get_int();
                case "uint":
                    return value.get_uint();
                case "double":
                    return value.get_double();
                case "float":
                    return value.get_float();
                case "wstring":
                    return value.get_wstring();
                case "short":
                    return value.get_short();
                case "ushort":
                    return value.get_ushort();
                case "char":
                    return value.get_char();
                case "uchar":
                    return value.get_uchar();
                case "int64":
                    return value.get_int64();
                case "uint64":
                    return value.get_uint64();
                default:
                    // throw bad cast exception here?
                    return null;
            }
        }

        public static fbnetvariant ConvertFromNet(this Object value)
        {
            fbnetvariant result = new fbnetvariant();
            if (value is bool)
                result.set((bool)value);
            else if (value is int)
                result.set((int)value);
            else if (value is uint)
                result.set((uint)value);
            else if (value is double)
                result.set((double)value);
            else if (value is float)
                result.set((float)value);
            else if (value is string)
                result.set((string)value);
            else if (value is short)
                result.set((short)value);
            else if (value is ushort)
                result.set((ushort)value);
            else if (value is char)
                result.set((char)value);
            else if (value is byte)
                result.set((byte)value);
            else if (value is Int64)
                result.set((Int64)value);
            else if (value is UInt64)
                result.set((UInt64)value);
            else
            {
                // throw bad cast exception here?
            }
            return result;
        }
    }   
}
