using System;
using System.Collections.Generic;
using System.Reflection;
using System.Linq;
using System.Linq.Expressions;

namespace FireBreath
{
    public class Converter
    {
        // todo: refactor this into one function
        public static FBXResult ToNet(fbxvariant value, Type targetType, out Object result)
        {
            try
            {
                result = ToNet2(value, targetType);
            }
            catch (InvalidCastException e)
            {
                result = null;
                return new FBXResult(false, "Cannot cast object of type '" + value + "' " + e);
            }
            return FBXResult.successful;
        }

        public static Object ToNet2(fbxvariant value, Type targetType)
        {
            switch (value.get_type())
            {
                case "bool":
                    if ( targetType.IsAssignableFrom(typeof(bool)) )
                        return value.get_bool();
                    break;
                case "int":
                    if (targetType.IsAssignableFrom(typeof(int)))
                        return value.get_int();
                    break;
                case "uint":
                    if (targetType.IsAssignableFrom(typeof(uint)))
                        return value.get_uint();
                    break;
                case "double":
                    {
                        Double v = value.get_double();
                        if (targetType.IsAssignableFrom(typeof(double)))
                        {
                            return v;
                        }
                        if (targetType.IsAssignableFrom(typeof(int)) && (v == (int)v))
                        {
                            return (int)v;
                        }
                    }
                    break;
                case "float":
                    if (targetType.IsAssignableFrom(typeof(float)))
                        return value.get_float();
                    break;
                case "wstring":
                    if (targetType.IsAssignableFrom(typeof(string)))
                        return value.get_wstring();
                    break;
                case "short":
                    if (targetType.IsAssignableFrom(typeof(short)))
                        return value.get_short();
                    break;
                case "ushort":
                    if (targetType.IsAssignableFrom(typeof(ushort)))
                        return value.get_ushort();
                    break;
                case "char":
                    if (targetType.IsAssignableFrom(typeof(char)))
                        return value.get_char();
                    break;
                case "uchar":
                    if (targetType.IsAssignableFrom(typeof(byte)))
                        return value.get_uchar();
                    break;
                case "int64":
                    if (targetType.IsAssignableFrom(typeof(Int64)))
                        return value.get_int64();
                    break;
                case "uint64":
                    if (targetType.IsAssignableFrom(typeof(UInt64)))
                        return value.get_uint64();
                    break;
                case "null":
                    if (targetType.IsAssignableFrom(typeof(Nullable)))
                        return null;
                    break;
                case "empty":
                    if (targetType.IsAssignableFrom(typeof(Nullable)))
                        return null;
                    break;
                case "object":
                {
                    FBXJSAPI v = value.get_object();
                    if (targetType.IsAssignableFrom(typeof(FBXJSAPI)))
                    {
                        return v;
                    }
                    else
                    {
                        dynamic jsObj = new JSObject(v);
                        int testInt = jsObj;
                        Expression conversion = Expression.Convert(Expression.Constant(jsObj), targetType);
                        Type delegateType = typeof(Func<>).MakeGenericType(targetType);
                        Delegate conversionDelegate = Expression.Lambda(delegateType, conversion).Compile();
                        var result = conversionDelegate.DynamicInvoke();
                        return result;
                    }
                }
            }

            throw new InvalidCastException("Cannot cast object of type '" + value.get_type() + "' to type '" + targetType.Name + "'" );
        }

        public static T ToNet3<T>(fbxvariant value)
        {
            object result = ToNet2(value, typeof(T));
            return (T)result;
        }
        
        public static FBXResult FromNet(Object value, fbxvariant result)
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
            else if (value is JSObject)
                result.set(((JSObject)value).wrappedObject);
            else if (value is MethodObject)
                result.set(new MethodJSAPI(value));
            else if (value is Type)
                result.set(new TypeJSAPI(value));
            else if (value is Object)
                result.set(new ObjectJSAPI(value));
            else
            {
                // throw bad cast exception here?
                return new FBXResult(false, "Cannot cast '" + value.ToString() + "' to an fbx type");
            }
            return FBXResult.successful;
        }

        public static fbxvariant FromNet2(object value)
        {
            fbxvariant result = new fbxvariant();
            FromNet(value, result);
            return result;
        }

        public static VariantVector FromNet2(object[] value)
        {
            VariantVector result = new VariantVector();
            foreach (object val in value) result.Add( FromNet2(val) );
            return result;
        }

        public static FBXResult InvokeOverload(Object obj, IEnumerable<MethodBase> candidates, string name, VariantVector args, fbxvariant result)
        {
            object resultObj;
            return InvokeOverload(obj, candidates, name, args, result, out resultObj);
        }

        public static FBXResult InvokeOverload(Object obj, IEnumerable<MethodBase> candidates, string name, VariantVector args, fbxvariant result, out object resultObj)
        {
            resultObj = null;
            System.Collections.Generic.List<object> convertedArgs = new System.Collections.Generic.List<object>();

            // todo: cache conversion results for more speed
            foreach (MethodBase candidate in candidates) 
            {
                ParameterInfo[] targetParameters = candidate.GetParameters();
                int count = Math.Min(args.Count(), targetParameters.Length);
                object[] converted = new object[count];
                bool ok = true;

                for ( int i = 0; i < count; i++)
                {
                    fbxvariant sourceValue = args[i];
                    ParameterInfo targetParameter = targetParameters[i];
                    if ( !ToNet(sourceValue, targetParameter.ParameterType, out converted[i]).success )
                    {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                {
                    try
                    {
                        // todo: this is ugly, factor out
                        if (name != "*ctor*")
                            resultObj = candidate.Invoke(obj, converted);
                        else
                            resultObj = ((ConstructorInfo)candidate).Invoke(converted);
                    }
                    catch (Exception e)
                    {
                        return new FBXResult(false, "Error invoking '" + name + "'. Details: " + e);
                    }
                    return FromNet(resultObj, result);
                }
            }

            return new FBXResult(false, "Could not find matching overload for '" + name + "'");
        }
    
    }

}
