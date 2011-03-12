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
    virtual void getMemberNames(std::vector<std::string>& nameVector)
    {
        nameVector = getMemberNames();
    }

    virtual bool SetProperty(int idx, const fbxvariant& value) = 0;
    virtual void SetProperty(int idx, const variant& value) {
        bool success = SetProperty( idx, fbxvariant(value) );
    }

    virtual bool SetProperty(const std::string& propertyName, const fbxvariant& value) = 0;
    virtual void SetProperty(const std::string& propertyName, const variant& value) {
        bool success = SetProperty( propertyName, fbxvariant(value) );
    }
    
    virtual bool GetProperty(const std::string& propertyName, fbxvariant& value) = 0;
    virtual variant GetProperty(const std::string& propertyName)
    {
        fbxvariant result;
        bool success = GetProperty(propertyName, result);
        return result.var;
    }
    
    virtual bool GetProperty(int idx, fbxvariant& value) = 0;
    virtual variant GetProperty(int idx)
    {
        fbxvariant result;
        bool success = GetProperty(idx, result);
        return result.var;
    }

    virtual bool Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& result) = 0;
    virtual variant Invoke(const std::string& methodName, const std::vector<variant>& args)
    {
        fbxvariant result;
        std::vector<fbxvariant> fbxArgs(args.size());
        for ( size_t i = 0; i < args.size(); i++ ) {
            fbxArgs[i] = args[i];
        }
        bool success = Invoke(methodName, fbxArgs, result);
        return result.var;
    }
};