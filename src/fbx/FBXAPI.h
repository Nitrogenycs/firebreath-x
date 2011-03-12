#include "JSAPI.h"
#include "FBXVariant.h"

class FBXJSAPI : public FB::JSAPI
{
public:
    FBXJSAPI()
    {}
    
    FBXJSAPI( const FB::SecurityZone& securityLevel ) : FB::JSAPI(securityLevel)
    {}
        
    virtual
    ~FBXJSAPI()
    {}

public:
    virtual std::vector<std::string> getMemberNames() const = 0;
    virtual void getMemberNames(std::vector<std::string>& nameVector) const
    {
        nameVector = getMemberNames();
    }

    virtual bool SetProperty(int idx, const fbxvariant& value) = 0;
    virtual void SetProperty(int idx, const FB::variant& value) {
        fbxvariant var;
        var.set( value );
        bool success = SetProperty( idx, var );
    }

    virtual bool SetProperty(const std::string& propertyName, const fbxvariant& value) = 0;
    virtual void SetProperty(const std::string& propertyName, const FB::variant& value) {
        fbxvariant var;
        var.set( value );
        bool success = SetProperty( propertyName, var );
    }
    
    virtual bool GetProperty(const std::string& propertyName, fbxvariant& value) = 0;
    virtual FB::variant GetProperty(const std::string& propertyName)
    {
        fbxvariant result;
        bool success = GetProperty(propertyName, result);
        return result.get_variant();
    }
    
    virtual bool GetProperty(int idx, fbxvariant& value) = 0;
    virtual FB::variant GetProperty(int idx)
    {
        fbxvariant result;
        bool success = GetProperty(idx, result);
        return result.get_variant();
    }

    virtual bool Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& result) = 0;
    virtual FB::variant Invoke(const std::string& methodName, const std::vector<FB::variant>& args)
    {
        fbxvariant result;
        std::vector<fbxvariant> fbxArgs(args.size());
        for ( size_t i = 0; i < args.size(); i++ ) {
            fbxArgs[i].set( args[i] );
        }
        bool success = Invoke(methodName, fbxArgs, result);
        return result.get_variant();
    }
};