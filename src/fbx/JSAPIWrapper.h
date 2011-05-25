#ifndef JSAPIWRAPPER_H
#define JSAPIWRAPPER_H

#include "JSAPI.h"
#include "variant.h"

class FBXJSAPI;

class JSAPIWrapper : public FB::JSAPI
{
public:
    JSAPIWrapper(FBXJSAPI* Wrapped);        
    virtual
    ~JSAPIWrapper();

public:
    virtual void getMemberNames(std::vector<std::string>& nameVector) const;
    virtual size_t getMemberCount() const;

    virtual void SetProperty(int idx, const FB::variant& value);
    virtual void SetProperty(const std::string& propertyName, const FB::variant& value);

    virtual FB::variant GetProperty(const std::string& propertyName);
    virtual FB::variant GetProperty(int idx);

    virtual bool RemoveProperty(const std::string& propertyName);
    virtual bool RemoveProperty(int idx);

    virtual bool HasProperty(const std::string& propertyName) const;
    virtual bool HasProperty(int idx) const;
    
    virtual bool HasMethod(const std::string& methodName) const;

    virtual FB::variant Invoke(const std::string& methodName, const std::vector<FB::variant>& args);
    virtual FB::variant Construct(const std::vector<FB::variant>& args);

protected:
    FBXJSAPI* wrapped;
};

#endif