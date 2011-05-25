using System;
using System.Reflection;
using System.Dynamic;
using FireBreath;


namespace FireBreath
{
    public static class MakeJSDynamic
    {
        public static dynamic js(this FBXJSAPI api)
        {
            return new JSObject(api);
        }
    }


    public class JSObject : DynamicObject
    {
        public FBXJSAPI wrappedObject { get; set; }
        public Type type { get; set; }


        public JSObject(FBXJSAPI WrappedObject)
        {
            wrappedObject = WrappedObject;
            /*fbxvariant prototype = new fbxvariant();
            FBXResult jsresult = wrappedObject.GetProperty("prototype", prototype);
            if (jsresult.success && prototype.get_type() == "object")
            {
                ObjectJSAPI api = prototype.get_object() as ObjectJSAPI;
                if (api != null)
                {
                    type = api.wrappedObject as Type;
                }
            }*/
        }

        // Converting an object to a specified type.
        public override bool TryConvert(ConvertBinder binder, out object result)
        {
            //if (binder.Type.IsAssignableFrom(type))
            {
                result = this;
                return true;
            }
            /*else
            {
                result = null;
                return false;
            }*/
        }

        // Getting a property.
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            fbxvariant value = new fbxvariant();
            FBXResult jsresult = wrappedObject.GetProperty(binder.Name, value);
            if (!jsresult.success)
                throw new Exception(jsresult.message);
            Converter.ToNet(value, typeof(object), out result);
            return true;
        }

        // Setting a property.
        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            fbxvariant convertedValue = new fbxvariant();
            FBXResult jsresult = Converter.FromNet(value, convertedValue);
            if (!jsresult.success)
                throw new Exception(jsresult.message);
            jsresult = wrappedObject.SetProperty(binder.Name, convertedValue);
            if (!jsresult.success)
                throw new Exception(jsresult.message);
            return true;
        }
    }
}
