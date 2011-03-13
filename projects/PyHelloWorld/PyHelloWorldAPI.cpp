/**********************************************************\

  Auto-generated PyHelloWorldAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "PyHelloWorldAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn PyHelloWorldAPI::PyHelloWorldAPI(const PyHelloWorldPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
PyHelloWorldAPI::PyHelloWorldAPI(const PyHelloWorldPtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host)
{
    registerMethod("echo",      make_method(this, &PyHelloWorldAPI::echo));
    registerMethod("testEvent", make_method(this, &PyHelloWorldAPI::testEvent));

    // Read-write property
    registerProperty("testString",
                     make_property(this,
                        &PyHelloWorldAPI::get_testString,
                        &PyHelloWorldAPI::set_testString));

    // Read-only property
    registerProperty("version",
                     make_property(this,
                        &PyHelloWorldAPI::get_version));
    
    
    registerEvent("onfired");    
}

///////////////////////////////////////////////////////////////////////////////
/// @fn PyHelloWorldAPI::~PyHelloWorldAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
PyHelloWorldAPI::~PyHelloWorldAPI()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @fn PyHelloWorldPtr PyHelloWorldAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
PyHelloWorldPtr PyHelloWorldAPI::getPlugin()
{
    PyHelloWorldPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read/Write property testString
std::string PyHelloWorldAPI::get_testString()
{
    return m_testString;
}
void PyHelloWorldAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string PyHelloWorldAPI::get_version()
{
    return "CURRENT_VERSION";
}

// Method echo
FB::variant PyHelloWorldAPI::echo(const FB::variant& msg)
{
    return msg;
}

void PyHelloWorldAPI::testEvent(const FB::variant& var)
{
    FireEvent("onfired", FB::variant_list_of(var)(true)(1));
}

