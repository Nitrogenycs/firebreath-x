using System;
using System.Windows.Forms;
using FireBreath;

namespace TestApp
{
    public class MyClass
    {
        public void ShowMessage(string msg)
        {
             MessageBox.Show(msg, "C# Message Box");
        }
    
        public string data
        {
            get { return "123"; }
        }
    }

    public class JSAPI : FBNetJSAPI
    {
        object globals;

        public JSAPI(object Globals)
        {
            globals = Globals;
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

    class Globals
    {
        System.Type MyClass = typeof(MyClass);

        public void run(JSAPI context)
        {
            //context.document.title = "Hello, this is the browser/js window";
            string title = context.eval("document.title");
            MessageBox.Show(title, "document.title is...");

            context.eval(@"
                var obj = new MyClass();
                alert( obj.data );
                obj.ShowMessage('Hello from JS');
            ");
        }
    }

    public static class MyExtension
    {
        public static JSAPI createJSAPI()
        {
            Globals globals = new Globals();
            JSAPI api = new JSAPI(globals);
            return api;
        }
    }

}