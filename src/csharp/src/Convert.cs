using System;
using System.Collections.Generic;
using System.Reflection;

namespace FireBreath
{
    public static class Convert
    {
        public static Object ConvertToNet(this fbxvariant value)
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
                case "null":
                    return null;
                case "empty":
                    // return Empty;
                    return null;
                case "object":
                    return value.get_object();
                default:
                    // throw bad cast exception here?
                    return null;
            }
        }

        public static bool ConvertFromNet(this Object value, fbxvariant result)
        {
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
            else if (value == null)
                result.set_null();
            //else if (value == Empty)
            //    result.set_empty();
            else if (value is FBXJSAPI)
                result.set((FBXJSAPI)value);
            else if (value is Object)
                result.set(new ObjectJSAPI(value));
            else
            {
                // throw bad cast exception here?
                return false;
            }
            return true;
        }
    }


    public class MethodCall
    {
        object obj;
        MethodInfo info;

        public MethodCall(object Obj, MethodInfo Info)
        {
            obj = Obj;
            info = Info;
        }

        public Object call(object[] parameters)
        {
            return info.Invoke(obj, parameters);
        }
    }
}
