#ifndef FBXJSAPIWRAPPER_H
#define FBXJSAPIWRAPPER_H

#include "FBXJSAPI.h"
#include "JSAPI.h"

class fbxvariant;

class FBXJSAPIWrapper : public FBXJSAPI
{
public:
    FBXJSAPIWrapper(FB::JSAPIPtr Wrapped);        
    virtual
    ~FBXJSAPIWrapper();

public:
    virtual std::vector<std::string> getMemberNames() const;
    virtual size_t getMemberCount() const;

    virtual bool SetProperty(int idx, const fbxvariant& value);
    virtual bool SetProperty(const std::string& propertyName, const fbxvariant& value);

    virtual bool GetProperty(const std::string& propertyName, fbxvariant& value);  
    virtual bool GetProperty(int idx, fbxvariant& value);

    virtual bool HasProperty(const std::string& propertyName) const;
    virtual bool HasProperty(int idx) const;
    
    virtual bool HasMethod(const std::string& methodName) const;

    virtual bool Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& returnValue);

protected:
    FB::JSAPIPtr wrapped;
};

#endif