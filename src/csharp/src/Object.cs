using System;
using System.Reflection;
using System.Collections;
using System.Linq;
using FireBreath;

using System.Dynamic;

//using System.Windows.Forms; // remember to remove the assembly

namespace FireBreath
{
    public class ObjectJSAPI : FBXJSAPI
    {
        public object wrappedObject { get; set; }
        public Type type { get; set; }

        public ObjectJSAPI(object WrappedObject)
        {
            wrappedObject = WrappedObject;
            type = wrappedObject.GetType();
        }

        // ----- member enumeration ------

        public override StringVector getMemberNames()
        {
            StringVector result = new StringVector();
            foreach (MemberInfo memberInfo in type.GetMembers())
            {
                result.Add(memberInfo.Name);
            }
            return result;
        }

        public override uint getMemberCount()
        {
            return (uint)type.GetMembers().Length;
        }


        // ----- HasProperty methods ------

        public override bool HasProperty(string propertyName)
        {
            fbxvariant temp = new fbxvariant();
            return GetProperty(propertyName, temp).success;
        }
        public override bool HasProperty(int idx)
        {
            fbxvariant temp = new fbxvariant();
            return GetProperty(idx, temp).success;
        }


        PropertyInfo getProp(string propertyName)
        {
            return (from prop in type.GetProperties() 
                    where prop.Name == propertyName 
                    select prop).FirstOrDefault();
        }

        // ----- GetProperty methods ------

        FBXResult GetIndexedProperty(object idx, fbxvariant value)
        {
            object obj;
            DefaultMemberAttribute defaultMember = (DefaultMemberAttribute)Attribute.GetCustomAttribute(type, typeof(DefaultMemberAttribute));

            var property = (defaultMember != null) ? getProp(defaultMember.MemberName) : null;
            if (property != null)
            {
                try
                {
                    obj = property.GetValue(this.wrappedObject, new object[] { idx });
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return Converter.FromNet(obj, value);
            }
            // need to check if this.wrappedObject can be indexed directly?
            return new FBXResult(false, "Property '" + idx + "' not found");
        }

        public override FBXResult GetProperty(int idx, fbxvariant value)
        {
            return GetIndexedProperty(idx, value);
        }

        public override FBXResult GetProperty(string propertyName, fbxvariant value)
        {
            if (propertyName == "toString") propertyName = "ToString";

            // possible types: all, constructor, custom, event, field, method, nested type, property, typeinfo
            object obj;
            FieldInfo field = type.GetField(propertyName);
            if (field != null)
            {
                try
                {
                    obj = field.GetValue(this.wrappedObject);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return Converter.FromNet(obj, value);
            }

            var property = getProp(propertyName);
            if (property != null)
            {
                try
                {
                    obj = property.GetValue(this.wrappedObject, null);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return Converter.FromNet(obj, value);
            }

            // todo: why not use Delegate.CreateDelegate() here? Because we need to convert parameters explicitly to the desired target types?
            //       maybe we should get rid of variants and replace them with DynamicObjects instead.
            if ( type.GetMethods().Any( method => method.Name == propertyName ) )
                return Converter.FromNet(new MethodObject(this.wrappedObject, propertyName), value);

            FBXResult result = GetIndexedProperty(propertyName, value);
            if (!result.success)
            {
                int idx;
                if (Int32.TryParse(propertyName, out idx))
                {
                    return GetIndexedProperty(idx, value);
                }
            }
            return result;
        }


        // ----- SetProperty methods ------

        FBXResult SetIndexedProperty(object idx, fbxvariant value)
        {
            object convertedValue;

            DefaultMemberAttribute defaultMember = (DefaultMemberAttribute)Attribute.GetCustomAttribute(type, typeof(DefaultMemberAttribute));

            var property = (defaultMember != null) ? getProp(defaultMember.MemberName) : null;
            if (property != null)
            {
                FBXResult returnValue = Converter.ToNet(value, property.PropertyType.GetElementType(), out convertedValue);
                if (!returnValue.success)
                    return returnValue;

                try
                {
                    property.SetValue(this.wrappedObject, value, new object[] { idx });
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return FBXResult.successful;
            }

            return new FBXResult(false, "Property '" + idx + "' not found");
        }


        public override FBXResult SetProperty(int idx, fbxvariant value)
        {
            return SetIndexedProperty(idx, value);
        }

        public override FBXResult SetProperty(string propertyName, fbxvariant value)
        {
            object convertedValue;

            FieldInfo field = type.GetField(propertyName);
            if (field != null)
            {
                FBXResult returnValue = Converter.ToNet(value, field.FieldType, out convertedValue);
                if (!returnValue.success)
                    return returnValue;

                try
                {
                    field.SetValue(this.wrappedObject, convertedValue);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return returnValue;
            }

            PropertyInfo property = getProp(propertyName);
            if (property != null)
            {
                FBXResult returnValue = Converter.ToNet(value, property.PropertyType, out convertedValue);
                if (!returnValue.success)
                    return returnValue;

                try
                {
                    property.SetValue(this.wrappedObject, convertedValue, null);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }

                return returnValue;
            }

            FBXResult result = SetIndexedProperty(propertyName, value);
            if (!result.success)
            {
                int idx;
                if (Int32.TryParse(propertyName, out idx))
                {
                    return SetIndexedProperty(idx, value);
                }
            }
            return result;
        }


        // ------- Method related -------

        public override bool HasMethod(string methodName)
        {
            return false;
            //return type.GetMethod(methodName) != null;
        }

        public override FBXResult Invoke(string methodName, VariantVector args, fbxvariant result)
        {
            // Invoke default member here if methodName == ""?
            return new FBXResult(false, "Method '" + methodName + "' not found");
        }

        public override FBXResult Construct(VariantVector args, fbxvariant returnValue)
        {
            return new FBXResult(false, "Object has no constructor");
        }

    }
}