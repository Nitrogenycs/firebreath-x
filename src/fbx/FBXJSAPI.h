#include "JSAPI.h"
#include "FBXVariant.h"

class FBXJSAPI : public FB::JSAPI
{
public:
    FBXJSAPI();
    FBXJSAPI( const FB::SecurityZone& securityLevel );
        
    virtual
    ~FBXJSAPI();

public:
    virtual std::vector<std::string> getMemberNames() const = 0;
    virtual void getMemberNames(std::vector<std::string>& nameVector) const;

    virtual bool SetProperty(int idx, const fbxvariant& value) = 0;
    virtual void SetProperty(int idx, const FB::variant& value);

    virtual bool SetProperty(const std::string& propertyName, const fbxvariant& value) = 0;
    virtual void SetProperty(const std::string& propertyName, const FB::variant& value);
    
    virtual bool GetProperty(const std::string& propertyName, fbxvariant& value) = 0;
    virtual FB::variant GetProperty(const std::string& propertyName);
    
    virtual bool GetProperty(int idx, fbxvariant& value) = 0;
    virtual FB::variant GetProperty(int idx);

    virtual bool Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& result) = 0;
    virtual FB::variant Invoke(const std::string& methodName, const std::vector<FB::variant>& args);
};