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