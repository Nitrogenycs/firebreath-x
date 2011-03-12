#include "FBXJSAPI.h"
#include "FBXVariant.h"

FBXJSAPI::FBXJSAPI()
{
}
    
FBXJSAPI::FBXJSAPI( const FB::SecurityZone& securityLevel ) : FB::JSAPI(securityLevel)
{
}
        
FBXJSAPI::~FBXJSAPI()
{
}

void FBXJSAPI::getMemberNames(std::vector<std::string>& nameVector) const
{
    nameVector = getMemberNames();
}

void FBXJSAPI::SetProperty(int idx, const FB::variant& value) {
    fbxvariant var;
    var.set( value );
    bool success = SetProperty( idx, var );
}

void FBXJSAPI::SetProperty(const std::string& propertyName, const FB::variant& value) {
    fbxvariant var;
    var.set( value );
    bool success = SetProperty( propertyName, var );
}
    
FB::variant FBXJSAPI::GetProperty(const std::string& propertyName)
{
    fbxvariant result;
    bool success = GetProperty(propertyName, result);
    return result.get_variant();
}
    
FB::variant FBXJSAPI::GetProperty(int idx)
{
    fbxvariant result;
    bool success = GetProperty(idx, result);
    return result.get_variant();
}

FB::variant FBXJSAPI::Invoke(const std::string& methodName, const std::vector<FB::variant>& args)
{
    fbxvariant result;
    std::vector<fbxvariant> fbxArgs(args.size());
    for ( size_t i = 0; i < args.size(); i++ ) {
        fbxArgs[i].set( args[i] );
    }
    bool success = Invoke(methodName, fbxArgs, result);
    return result.get_variant();
}
