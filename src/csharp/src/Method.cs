using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using FireBreath;

namespace FireBreath
{
    public class MethodJSAPI : ObjectJSAPI
    {
        public MethodObject methodObject;

        public MethodJSAPI(object WrappedObject) : base(WrappedObject)
        {
            methodObject = (MethodObject)this.wrappedObject;
        }

        public override FBXResult Invoke(string methodName, VariantVector args, fbxvariant result)
        {
            if (methodName == "")
            {
                IEnumerable<MethodInfo> methods = from method in this.methodObject.obj.GetType().GetMethods() where method.Name == this.methodObject.name select method;
                return Converter.InvokeOverload(this.methodObject.obj, methods, this.methodObject.name, args, result);
            }
            else
            {
                throw new Exception("Internal error - execution should never reach here");
            }
        }
    }

    public class MethodObject
    {
        public object obj;
        public string name;

        public MethodObject(object Obj, string Name)
        {
            obj = Obj;
            name = Name;
        }
    }
}