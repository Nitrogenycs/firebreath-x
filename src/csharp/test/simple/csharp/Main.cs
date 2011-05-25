using System;
using System.Windows.Forms;
using System.Collections.Generic;
using FireBreath;

namespace TestApp
{
    public class MyClass
    {
        string _value;
        public static int staticInt = 123;

        public MyClass()
        {
            _value = "123";
        }

        public void ShowMessage(string msg)
        {
             MessageBox.Show(msg, "C# Message Box");
        }
    
        public string data
        {
            get { return "123"; }
        }

        public string changeThis
        {
            get { return this._value; }
            set { this._value = value;  }
        }

        public string testOutParameter(out int result)
        {
            result = 456;
            return "123";
        }

        public string testMethodObject()
        {
            return changeThis;
        }

        public string testComplexObject(ImplementMe obj)
        {
            return obj.message;
        }

        public string testOverload(int x, double y)
        {
            return "double";
        }

        public string testOverload(int x, string z)
        {
            return "string";
        }

        public object passThrough(object obj)
        {
            return obj;
        }
    }

    public class ImplementMe
    {
        public string message = "This is a C# string";
    }

    public class Globals
    {
        public bool someBool = true;
        public int someInt = 42;
        public uint someUInt = 42;
        public double someDouble = 42.1;
        public float someFloat = 42.2f;
        public string someString = "this is a c# string";
        public short someShort = 42;
        public ushort someUShort = 42;
        public char someChar = '*';
        public byte someByte = 42;
        public Int64 someInt64 = 42;
        public UInt64 someUInt64 = 42;
        public object someNull = null;
        public object someEmpty = null;
        public object someObject = new MyClass();
        public System.Type someType = typeof(MyClass);
        public List<object> someList = new List<object>() { new MyClass(), "Hello", new MyClass() };
        public Dictionary<string, object> someDict = new Dictionary<string, object>() { { "item1", new MyClass() }, { "item2", "value2" } };
        public System.Type ImplementMe = typeof(ImplementMe);
        public object Object = typeof(object);

        public FBXJSAPI context;

        public void showTitle()
        {
            //context.document.title = "Hello, this is the browser/js window";
            string title = context.js().window.eval("document.title");
            MessageBox.Show(title, "document.title is...");

            /*context.js().window.eval(@"
                var obj = new MyClass();
                alert( obj.data );
                obj.ShowMessage('Hello from JS');
            ");*/
        }
    }

    public class TestApp
    {
        public Globals globals;
        public ObjectJSAPI rootApi;
        public FBXJSAPI context;
        public string options;

        public TestApp(string entryInfo)
        {
            AppDomain.CurrentDomain.UnhandledException += new UnhandledExceptionEventHandler(UnhandledExceptionHandler);

            globals = new Globals();
            rootApi = new ObjectJSAPI(globals);

            FireBreath.Startup.initialize(entryInfo, rootApi, out context, out options);

            globals.context = context;
        }

        static void UnhandledExceptionHandler(object sender, UnhandledExceptionEventArgs args)
        {
            Exception e = (Exception)args.ExceptionObject;
            MessageBox.Show(e.ToString(), "C# plugin error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }

}