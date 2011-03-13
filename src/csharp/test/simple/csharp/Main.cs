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

        public void run()
        {
            //context.document.title = "Hello, this is the browser/js window";
            string title = TestApp.context.eval("document.title");
            MessageBox.Show(title, "document.title is...");

            TestApp.context.eval(@"
                var obj = new MyClass();
                alert( obj.data );
                obj.ShowMessage('Hello from JS');
            ");
        }
    }

    public static class TestApp
    {
        public static Globals globals = new Globals();
        public static ObjectJSAPI rootApi = new ObjectJSAPI(globals);
        public static FBXContext context;

        public static JSAPI createJSAPI(FBXContext Context)
        {
            context = Context;
            return rootApi;
        }
    }

}