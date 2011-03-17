/**********************************************************\

  Auto-generated PyHelloWorldAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "APITypes.h"
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "PyHelloWorld.h"

#include <Python.h>

#ifndef H_PyHelloWorldAPI
#define H_PyHelloWorldAPI

class PyHelloWorldAPI : public FB::JSAPIAuto
{
public:
    PyHelloWorldAPI(const PyHelloWorldPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~PyHelloWorldAPI();

    PyHelloWorldPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Method test-event
    void testEvent(const FB::variant& s);

    FB::variant hello_py();

    FB::variant hello_py_extension();

    // Method echo
    //FB::variant eval(const FB::variant& py);

private:
    PyHelloWorldWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;

    PyObject* globals;

    FB::JSAPIPtr hello_py_ext_instance;

};

#endif // H_PyHelloWorldAPI

