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

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::JSAPIPtr loadExtension(const std::wstring& name);
    
private:
    FBXSimpleTestPluginCSharpWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};


class FBXContext/* : FB::JSAPIAuto*/
{
public:
    FBXContext(const FB::BrowserHostPtr& host);
    virtual
    ~FBXContext();

    FB::JSAPIPtr get_document() const;
    FB::JSAPIPtr get_window() const;
    FB::JSAPIPtr get_element() const;
    FB::JSAPIPtr eval(const std::wstring& script);

protected:
    FB::BrowserHostPtr m_host;
};

#endif // H_FBXSimpleTestPluginCSharpAPI

