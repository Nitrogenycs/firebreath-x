/**********************************************************\

  Auto-generated FBXSimpleTestPluginCSharpAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "FBXSimpleTestPluginCSharp.h"

#ifndef H_FBXSimpleTestPluginCSharpAPI
#define H_FBXSimpleTestPluginCSharpAPI

class FBXSimpleTestPluginCSharpAPI : public FB::JSAPIAuto
{
public:
    FBXSimpleTestPluginCSharpAPI(const FBXSimpleTestPluginCSharpPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~FBXSimpleTestPluginCSharpAPI();

    FBXSimpleTestPluginCSharpPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Method test-event
    void testEvent(const FB::variant& s);

private:
    FBXSimpleTestPluginCSharpWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_FBXSimpleTestPluginCSharpAPI

