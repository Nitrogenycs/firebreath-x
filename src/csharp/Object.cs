using System;
using System.Windows.Forms;
using FireBreath;

namespace FireBreath
{
    public class JSAPI : FBNetJSAPI
    {
        object wrappedObject;

        public JSAPI(object WrappedObject)
        {
            wrappedObject = WrappedObject;
        }

        public override StringVector getMemberNames()
        {
            Type type = typeof(Globals);
            if (type is Type)
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

        public override bool GetProperty(int idx, fbnetvariant value)
        {
            return true;
        }
        public override bool GetProperty(string propertyName, fbnetvariant value)
        {
            return true;
        }

        public override bool SetProperty(int idx, fbnetvariant value)
        {
            return true;
        }
        public override bool SetProperty(string propertyName, fbnetvariant value)
        {
            return true;
        }

        public override bool HasMethod(string methodName)
        {
            return false;
        }

        public override bool Invoke(string methodName, VariantVector args, fbnetvariant result)
        {
            return true;
        }
    }
    
}