/**********************************************************\

  Auto-generated PyHelloWorldAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "APITypes.h"
#include "PyHelloWorldAPI.h"

#include <Python.h>

void __JSAPI_no_delete(FB::JSAPI* ptr) {}

std::string __convert_py_to_string(PyObject* py_str) {
    Py_ssize_t str_len = PyString_Size(py_str);

    char* c_str = new char[str_len+1];
    memset(c_str, 0, str_len+1);
    strcpy_s(c_str, str_len+1, PyString_AsString(py_str));
    std::string result_str(c_str);

    return result_str;
}

std::string __get_python_error() {
        PyObject *type = 0;
        PyObject *value = 0;
        PyObject *traceback = 0;
        PyErr_Fetch(&type, &value, &traceback);

        if (value) {
            char *tmp;
            PyObject *str_obj = PyObject_Str(value);
            Py_XINCREF(type);
            PyErr_Clear();
            PyObject* msg = PyErr_Format(type, "%s", tmp = PyString_AsString(str_obj));
            std::string result_str = __convert_py_to_string(msg);
            Py_DECREF(msg);
            Py_DECREF(str_obj);

            return result_str;

        } else {
            return "Unknown error";
        }
}

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

    registerMethod("getHelloPyExtension", make_method(this, &PyHelloWorldAPI::hello_py_extension));

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

        result_str = __convert_py_to_string(py_str);

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

FB::variant PyHelloWorldAPI::hello_py_extension() {

    if ( hello_py_ext_instance.get() != 0) {
        return FB::variant(hello_py_ext_instance);
    }

    FB::variant result;

    PyObject *pName = 0; 
    PyObject *pModule = 0;
    PyObject *pExtClass = 0;
    PyObject *pCreateJSAPI = 0;
    PyObject *pArgs = 0;
    PyObject *pJsApi = 0;
    PyObject *pSwigObj = 0;
    PyObject *pSwigObjLongFunc = 0;
    PyObject *pSwigObjDisOwnFunc = 0;
    PyObject *pSwigObjPtr = 0;

    pName = PyString_FromString("fbx.example.hello_world");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule == NULL) {
        result = FB::variant("Could not load module 'fbx.example.hello_world'.");
        goto return_result;
    }

    pExtClass = PyObject_GetAttrString(pModule, "HelloWorldExtension");

    if (pExtClass == NULL) {
        result = FB::variant("Could not access 'HelloWorldExtension'.");
        goto return_result;
    }

    pCreateJSAPI = PyObject_GetAttrString(pExtClass, "createJSAPI");

    if (pCreateJSAPI == NULL) {
        result = FB::variant("Could not access 'HelloWorldExtension.createJSAPI()'.");
        goto return_result;
    }

    // ATTENTION: i believe somewhere here is some problem with ownership
    //       causing a crash in NPJavascriptObject
    //       (at end of Enumerate)
    // what i've tried - but didn't help:
    //  - drag ownership from python proxy 
    //          for the case that proxy destroys a PyObj that py wants to ref-kill too
    //  - not to decrease any of the python refs
    //          for the case that proxy tries to destroy an already destructed ref-counted pyobj
    //  - use a getMemberName(idx) instead of getMemberNames()
    //          for the case that std::vector-wrapper causes problems
    //  - copy returned strings
    //          for the case of some char* deletion  problem
    //
    pArgs = PyTuple_New(0);
    pJsApi = PyObject_CallObject(pCreateJSAPI, pArgs);
    Py_DECREF(pArgs);

    // maybe error is due to refcounted derstuction of pJsApi?
    Py_INCREF(pJsApi);

    if (pJsApi == NULL) {
        result = FB::variant("'HelloWorldExtension.createJSAPI() failed'.");
        goto return_result;
    }

    pSwigObj = PyObject_GetAttrString(pJsApi, "this");

    if (pSwigObj == NULL) {
        result = FB::variant("Could not access SwigObject.");
        goto return_result;
    }

    pSwigObjLongFunc = PyObject_GetAttrString(pSwigObj, "__long__");
    pSwigObjDisOwnFunc = PyObject_GetAttrString(pSwigObj, "disown");

    if (pSwigObjLongFunc == NULL) {
        result = FB::variant("no method '__long__()'");
        goto return_result;
    }

    pArgs = PyTuple_New(0);
    pSwigObjPtr = PyObject_CallObject(pSwigObjLongFunc, pArgs);
//    PyObject_CallObject(pSwigObjDisOwnFunc, pArgs);
    Py_DECREF(pArgs);

    if (pSwigObjPtr == NULL) {
        result = FB::variant("could not call method '__long__()'");
        goto return_result;
    }

    long ptr = PyLong_AsLong(pSwigObjPtr);

    JSAPI* jsapi = reinterpret_cast<JSAPI*>(ptr);

    hello_py_ext_instance = FB::JSAPIPtr(jsapi, __JSAPI_no_delete);

    result = FB::variant(hello_py_ext_instance);

return_result:
    Py_XDECREF(pSwigObjPtr);
    Py_XDECREF(pSwigObjDisOwnFunc);
    Py_XDECREF(pSwigObjLongFunc);
    Py_XDECREF(pSwigObj);
    Py_XDECREF(pCreateJSAPI);
    Py_XDECREF(pExtClass);
    Py_XDECREF(pModule);

    return result;

}

