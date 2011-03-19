﻿using System;
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

        public void run()
        {
            MessageBox.Show("running", "TestApp");
            //context.document.title = "Hello, this is the browser/js window";
            /*string title = TestApp.context.window.eval("document.title");
            MessageBox.Show(title, "document.title is...");

            TestApp.context.window.eval(@"
                var obj = new MyClass();
                alert( obj.data );
                obj.ShowMessage('Hello from JS');
            ");*/
        }
    }

    class TestApp
    {
        public static Globals globals = new Globals();
        public static ObjectJSAPI rootApi = new ObjectJSAPI(globals);
        public static FBXJSAPI context;
        public static string options;

        public static int createJSAPI(string entryInfo)
        {
            AppDomain currentDomain = AppDomain.CurrentDomain;
            currentDomain.UnhandledException += new UnhandledExceptionEventHandler(UnhandledExceptionHandler);
            FireBreath.Startup.initialize(entryInfo, rootApi, out context, out options);
            return 0;
        }

        static void UnhandledExceptionHandler(object sender, UnhandledExceptionEventArgs args)
        {
            Exception e = (Exception)args.ExceptionObject;
            MessageBox.Show(e.ToString(), "C# plugin error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }


}