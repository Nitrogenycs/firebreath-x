using System;
using System.Runtime.InteropServices;

namespace FireBreath
{
    public class Startup
    {
        public static void initialize(string entryInfo, FBXJSAPI jsapi, out FBXJSAPI context, out string options)
        {
            string[] args = entryInfo.Split(new char[] { '|' }, 3);
            // args = [0] IntPtr to FBXJSAPI* result, [1] IntPtr to FBXJSAPI* context, [2] passed options

            IntPtr result = (IntPtr)System.Convert.ToInt64(args[0], 16);
            Marshal.WriteIntPtr(result, FBXJSAPI.getCPtr(jsapi).Handle);

            IntPtr contextPtrPtr = (IntPtr)System.Convert.ToInt64(args[1], 16);
            IntPtr contextPtr = Marshal.ReadIntPtr(contextPtrPtr);
            context = new FBXJSAPI(contextPtr, false);

            options = args[2];
        }

    }

}
