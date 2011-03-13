/**********************************************************\

  Auto-generated PyHelloWorldAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "PyHelloWorldAPI.h"

#include <Python.h>

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
    Py_Initialize();

    globals = PyDict_New ();
    PyDict_SetItemString (globals, "__builtins__", PyEval_GetBuiltins ());

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

    registerMethod("hello_py", make_method(this, &PyHelloWorldAPI::hello_py));

//    registerMethod("eval", make_method(this, &PyHelloWorldAPI::eval));
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
    // crashes... don't know why this is not legal
//    Py_XDECREF(globals);
    Py_Finalize();
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

FB::variant PyHelloWorldAPI::hello_py()
{
    PyObject* src = Py_CompileString("result = 'hello js!'", "hello_world.py", Py_single_input);

    std::string result_str;

    if (src != 0)                         /* compiled just fine - */
    {
        PyObject* locals = PyDict_New ();

        PyObject* py_eval;
        PyObject* py_result;
        py_eval = PyEval_EvalCode((PyCodeObject *)src, globals, locals); 

        PyObject* res_key = PyString_FromString("result");
        py_result = PyDict_GetItem(locals, res_key);

        PyObject* py_str = PyObject_Str(py_result);
        Py_ssize_t str_len = PyString_Size(py_str);

        char* c_str = new char[str_len+1];
        memset(c_str, 0, str_len+1);
        strcpy_s(c_str, str_len+1, PyString_AsString(py_str));
        result_str = std::string(c_str);

        Py_XDECREF(py_str);
        Py_XDECREF(py_eval);

        // crashes... don't know why this is not legal
        //Py_XDECREF(locals);

    } else  {
        result_str = "Compilation of python src failed.";
    }

    FB::variant result(result_str);

    return result;
}

