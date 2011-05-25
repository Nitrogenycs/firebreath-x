using System;
using System.Reflection;
using FireBreath;

namespace FireBreath
{
    public class TypeJSAPI : ObjectJSAPI
    {
        public Type typeObject;

        public TypeJSAPI(object WrappedObject) : base(WrappedObject)
        {
            typeObject = (Type)this.wrappedObject;
        }

        public override FBXResult Construct(VariantVector args, fbxvariant returnValue)
        {
            FBXResult result = Converter.InvokeOverload(this.typeObject, this.typeObject.GetConstructors(), "*ctor*", args, returnValue);
            if (!result.success)
                return result;

            /*dynamic newInstance = new JSObject(returnValue.get_object());
            newInstance._cs_prototype = this.typeObject;*/
            return result;
        }
    }
}
