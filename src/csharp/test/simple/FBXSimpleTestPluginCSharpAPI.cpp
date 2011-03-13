/**********************************************************\

  Auto-generated FBXSimpleTestPluginCSharpAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "FBXSimpleTestPluginCSharpAPI.h"

#include <metahost.h>

///////////////////////////////////////////////////////////////////////////////
/// @fn FBXSimpleTestPluginCSharpAPI::FBXSimpleTestPluginCSharpAPI(const FBXSimpleTestPluginCSharpPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
FBXSimpleTestPluginCSharpAPI::FBXSimpleTestPluginCSharpAPI(const FBXSimpleTestPluginCSharpPtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host)
{
    registerMethod("loadExtension", make_method(this, &FBXSimpleTestPluginCSharpAPI::loadExtension));

    // Read-only property
    registerProperty("version", make_property(this, &FBXSimpleTestPluginCSharpAPI::get_version));
}

///////////////////////////////////////////////////////////////////////////////
/// @fn FBXSimpleTestPluginCSharpAPI::~FBXSimpleTestPluginCSharpAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
FBXSimpleTestPluginCSharpAPI::~FBXSimpleTestPluginCSharpAPI()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @fn FBXSimpleTestPluginCSharpPtr FBXSimpleTestPluginCSharpAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
FBXSimpleTestPluginCSharpPtr FBXSimpleTestPluginCSharpAPI::getPlugin()
{
    FBXSimpleTestPluginCSharpPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read-only property version
std::string FBXSimpleTestPluginCSharpAPI::get_version()
{
    return "1.0";
}


// Method loadExtension, from http://blogs.msdn.com/b/msdnforum/archive/2010/07/09/use-clr4-hosting-api-to-invoke-net-assembly-from-native-c.aspx
FB::JSAPIPtr FBXSimpleTestPluginCSharpAPI::loadExtension(const std::wstring& name)
{
    // todo: check signature of extension .dll/.so here for security measures!
    // CheckSecurity();

    // Bind to the runtime.
    FB::JSAPIPtr result;

    PCWSTR pszVersion = L"v4.0.30319";
    PCWSTR pszAssemblyPath = name.c_str();
    PCWSTR pszClassName = name.c_str();

    HRESULT hr;
    ICLRMetaHost *pMetaHost = NULL;
    ICLRRuntimeInfo *pRuntimeInfo = NULL;
    // ICorRuntimeHost and ICLRRuntimeHost are the two CLR hosting interfaces
    // supported by CLR 4.0. Here we demo the ICLRRuntimeHost interface that 
    // was provided in .NET v2.0 to support CLR 2.0 new features. 
    // ICLRRuntimeHost does not support loading the .NET v1.x runtimes.
    ICLRRuntimeHost *pClrRuntimeHost = NULL;
    // The static method in the .NET class to invoke.
    PCWSTR pszStaticMethodName = L"GetStringLength";
    PCWSTR pszStringArg = L"HelloWorld";
    DWORD dwLengthRet;

    try
    {
        // 
        // Load and start the .NET runtime.
        // 
        //wprintf(L"Load and start the .NET runtime %s \n", pszVersion);
        hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&pMetaHost));
        if (FAILED(hr))
            throw FB::script_error("CLRCreateInstance failed. Error code: " + boost::lexical_cast<std::string>(hr));

        // Get the ICLRRuntimeInfo corresponding to a particular CLR version. It 
        // supersedes CorBindToRuntimeEx with STARTUP_LOADER_SAFEMODE.
        hr = pMetaHost->GetRuntime(pszVersion, IID_PPV_ARGS(&pRuntimeInfo));
        if (FAILED(hr))
            throw FB::script_error("ICLRMetaHost::GetRuntime failed. Error code: " + boost::lexical_cast<std::string>(hr));

        // Check if the specified runtime can be loaded into the process. This 
        // method will take into account other runtimes that may already be 
        // loaded into the process and set pbLoadable to TRUE if this runtime can 
        // be loaded in an in-process side-by-side fashion. 
        BOOL fLoadable;
        hr = pRuntimeInfo->IsLoadable(&fLoadable);
        if (FAILED(hr))
            throw FB::script_error("ICLRRuntimeInfo::IsLoadable failed. Error code: " + boost::lexical_cast<std::string>(hr));

        if (!fLoadable)
            throw FB::script_error(".NET runtime cannot be loaded. Version: " + FB::wstring_to_utf8(pszVersion));

        // Load the CLR into the current process and return a runtime interface 
        // pointer. ICorRuntimeHost and ICLRRuntimeHost are the two CLR hosting  
        // interfaces supported by CLR 4.0. Here we demo the ICLRRuntimeHost 
        // interface that was provided in .NET v2.0 to support CLR 2.0 new 
        // features. ICLRRuntimeHost does not support loading the .NET v1.x 
        // runtimes.
        hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, 
            IID_PPV_ARGS(&pClrRuntimeHost));
        if (FAILED(hr))
            throw FB::script_error("IICLRRuntimeInfo::GetInterface failed. Error code: " + boost::lexical_cast<std::string>(hr));

            // Start the CLR.
        hr = pClrRuntimeHost->Start();
        if (FAILED(hr))
            throw FB::script_error("CLR failed to start. Error code: " + boost::lexical_cast<std::string>(hr));
        // 
        // Load the NET assembly and call the static method GetStringLength of 
        // the type CSSimpleObject in the assembly.
        // 
        // wprintf(L"Load the assembly %s\n", pszAssemblyPath);
        // The invoked method of ExecuteInDefaultAppDomain must have the 
        // following signature: static int pwzMethodName (String pwzArgument)
        // where pwzMethodName represents the name of the invoked method, and 
        // pwzArgument represents the string value passed as a parameter to that 
        // method. If the HRESULT return value of ExecuteInDefaultAppDomain is 
        // set to S_OK, pReturnValue is set to the integer value returned by the 
        // invoked method. Otherwise, pReturnValue is not set.
        hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(pszAssemblyPath, 
            pszClassName, pszStaticMethodName, pszStringArg, &dwLengthRet);
        if (FAILED(hr))
            throw FB::script_error("Failed to call GetStringLength. Error code: " + boost::lexical_cast<std::string>(hr));

         // Print the call result of the static method.
        wprintf(L"Call %s.%s(\"%s\") => %d\n", pszClassName, pszStaticMethodName, pszStringArg, dwLengthRet);
    }
    catch(...)
    {
        if (pMetaHost)
        {
            pMetaHost->Release();
            pMetaHost = NULL;
        }
        if (pRuntimeInfo)
        {
            pRuntimeInfo->Release();
            pRuntimeInfo = NULL;
        }
        if (pClrRuntimeHost)
        {
            // Please note that after a call to Stop, the CLR cannot be 
            // reinitialized into the same process. This step is usually not 
            // necessary. You can leave the .NET runtime loaded in your process.
            //wprintf(L"Stop the .NET runtime\n");
            //pClrRuntimeHost->Stop();
            pClrRuntimeHost->Release();
            pClrRuntimeHost = NULL;
        }
        throw;
    }

    return result;
}



FBXContext::FBXContext(const FB::BrowserHostPtr& host) : m_host(host)
{
    registerProperty("document", make_property(this, &FBXContext::get_document));
    registerProperty("window", make_property(this, &FBXContext::get_window));
    registerProperty("element", make_property(this, &FBXContext::get_element));
    registerMethod("eval", make_method(this, &FBXContext::eval));
}

FBXContext::~FBXContext()
{
}

FB::JSAPIPtr FBXContext::get_document() const
{
    return m_host->getDOMDocument()->getJSObject();
}

FB::JSAPIPtr FBXContext::get_window() const
{
    return m_host->getDOMWindow()->getJSObject();
}

FB::JSAPIPtr FBXContext::get_element() const
{
    return m_host->getDOMElement()->getJSObject();
}

FB::JSAPIPtr FBXContext::eval(const std::wstring& script) const
{
    std::vector<FB::variant> arguments;
    arguments.push_back( script );
    return get_window()->Invoke(L"eval", arguments);
}
