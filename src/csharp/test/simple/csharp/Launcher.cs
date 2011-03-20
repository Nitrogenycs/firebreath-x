using System;
using System.Reflection;
using System.IO;
using System.Windows.Forms;

namespace TestApp
{
    // see http://stackoverflow.com/questions/2008691/pass-and-execute-delegate-in-separate-appdomain
    // and http://www.codeguru.com/forum/showthread.php?t=398030

    // The runtime class derives from MarshalByRefObject, so that a proxy can be returned
    // across an AppDomain boundary.
    public class Launcher : MarshalByRefObject
    {
        static Launcher()
        {
            AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(CurrentDomain_AssemblyResolve);
        }

        public void run(string entryInfo)
        {
            new TestApp(entryInfo);
        }

        public static int launch(string entryInfo)
        {
            // Sample code follows here to create the appdomain, set startup params
            // for the appdomain, create an object in it, and execute a method
            string appBase = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            var ads = new AppDomainSetup { ApplicationBase = appBase, PrivateBinPath = appBase };

            AppDomain domain = AppDomain.CreateDomain("FBCS_Domain" + new Random().Next(0, 1000000), null, ads);

            try
            {
                Launcher launcher = (Launcher)domain.CreateInstanceAndUnwrap(Assembly.GetExecutingAssembly().FullName, typeof(Launcher).FullName);
                launcher.run(entryInfo);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "C# plugin error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                // runtime has exited, finish off by unloading the runtime appdomain
                //if (domain != null)
                //    AppDomain.Unload(domain);
            }
            return 0;
        }

        private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            if (args.Name == Assembly.GetExecutingAssembly().FullName)
                return Assembly.GetExecutingAssembly();

            string appDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string shortAsmName = Path.GetFileName(args.Name);
            string fileName = Path.Combine(appDir, shortAsmName);

            if (File.Exists(fileName))
            {
                return Assembly.LoadFrom(fileName);
            }
            return Assembly.GetExecutingAssembly().FullName == args.Name ? Assembly.GetExecutingAssembly() : null;
        }
    
    }    

}