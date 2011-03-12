using System;
using FireBreath;

namespace FireBreath
{
    public class JSAPI : FBXJSAPI
    {
        object wrappedObject;

        public JSAPI(object WrappedObject)
        {
            wrappedObject = WrappedObject;
        }

        public override StringVector getMemberNames()
        {
            Type type = wrappedObject.GetType();
            if (type == typeof(Type))
            {
            }
            type.GetMembers();
            StringVector result = new StringVector();
            result.Add("xxx");
            return result;
        }

        public override uint getMemberCount()
        {
            return 1;
        }

        public override bool HasProperty(string propertyName)
        {
            return false;
        }
        public override bool HasProperty(int idx)
        {
            return true;
        }

        public override bool GetProperty(int idx, fbxvariant value)
        {
            return true;
        }
        public override bool GetProperty(string propertyName, fbxvariant value)
        {
            return true;
        }

        public override bool SetProperty(int idx, fbxvariant value)
        {
            return true;
        }
        public override bool SetProperty(string propertyName, fbxvariant value)
        {
            return true;
        }

        public override bool HasMethod(string methodName)
        {
            return false;
        }

        public override bool Invoke(string methodName, VariantVector args, fbxvariant result)
        {
            return true;
        }
    }
    
}