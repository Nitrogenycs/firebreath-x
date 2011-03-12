using System;
using System.Reflection;
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
            StringVector result = new StringVector();
            Type type = wrappedObject.GetType();
            foreach (MemberInfo memberInfo in type.GetMembers())
            {
                result.Add(memberInfo.Name);
            }
            return result;
        }

        public override uint getMemberCount()
        {
            Type type = wrappedObject.GetType();
            return (uint)type.GetMembers().Length;
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