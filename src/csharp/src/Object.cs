using System;
using System.Reflection;
using FireBreath;

namespace FireBreath
{
    public class JSAPI : FBXJSAPI
    {
        object wrappedObject;
        Type type;

        public JSAPI(object WrappedObject)
        {
            wrappedObject = WrappedObject;
            type = wrappedObject.GetType();
        }

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

        public override bool HasProperty(string propertyName)
        {
            return type.GetMember(propertyName).Length != 0;
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
            MemberInfo info = type.GetMember(propertyName)[0];
            return info.GetConvertFromNet(value);
        }

        public override bool SetProperty(int idx, fbxvariant value)
        {
            return true;
        }
        public override bool SetProperty(string propertyName, fbxvariant value)
        {
            return type.GetMember(propertyName).ConvertFromNet(value);
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