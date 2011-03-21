using System;
using System.Collections.Generic;
using System.Reflection;

namespace FireBreath
{
    public static class Convert
    {
        // todo: refactor this into one function
        public static FBXResult ConvertToNet(this fbxvariant value,  out Object result)
        {
            try
            {
                result = ConvertToNet2(value);
            }
            catch (InvalidCastException e)
            {
                result = null;
                return new FBXResult(false, "Cannot cast object of type '" + value + "' " + e);
            }
            return FBXResult.successful;
        }

        public static Object ConvertToNet2(this fbxvariant value)
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
                    {
                        Double v = value.get_double();
                        if (v == (int)v) return (int)v;
                        return v;
                    }
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
            }

            throw new InvalidCastException("Cannot cast object of type '" + value.get_type() + "'");
        }

        public static FBXResult ConvertFromNet(this Object value, fbxvariant result)
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
                return new FBXResult(false, "Cannot cast '" + value.ToString() + "' to an fbx type");
            }
            return FBXResult.successful;
        }
    }


}
