#include "JSAPIWrapper.h"
#include "FBXJSAPI.h"
#include "FBXVariant.h"


JSAPIWrapper::JSAPIWrapper( FBXJSAPI* Wrapped ) : wrapped(Wrapped)
{
}
        
JSAPIWrapper::~JSAPIWrapper()
{
}

void JSAPIWrapper::getMemberNames(std::vector<std::string>& nameVector) const
{
    nameVector = wrapped->getMemberNames();
}

size_t JSAPIWrapper::getMemberCount() const
{
    return wrapped->getMemberCount();
}

void JSAPIWrapper::SetProperty(int idx, const FB::variant& value) 
{
    fbxvariant var;
    var.set( value );
    bool success = wrapped->SetProperty( idx, var );
}

void JSAPIWrapper::SetProperty(const std::string& propertyName, const FB::variant& value) 
{
    fbxvariant var;
    var.set( value );
    bool success = wrapped->SetProperty( propertyName, var );
}
    
FB::variant JSAPIWrapper::GetProperty(int idx)
{
    fbxvariant result;
    bool success = wrapped->GetProperty(idx, result);
    return result.get_variant();
}

FB::variant JSAPIWrapper::GetProperty(const std::string& propertyName)
{
    fbxvariant result;
    bool success = wrapped->GetProperty(propertyName, result);
    return result.get_variant();
}
    
bool JSAPIWrapper::HasProperty(int idx) const
{
    return wrapped->HasProperty(idx);
}

bool JSAPIWrapper::HasProperty(const std::string& propertyName) const
{
    return wrapped->HasProperty(propertyName);
}

bool JSAPIWrapper::HasMethod(const std::string& methodName) const
{
    return wrapped->HasMethod(methodName);
}

FB::variant JSAPIWrapper::Invoke(const std::string& methodName, const std::vector<FB::variant>& args)
{
    fbxvariant result;
    std::vector<fbxvariant> fbxArgs(args.size());
    for ( size_t i = 0; i < args.size(); i++ ) {
        fbxArgs[i].set( args[i] );
    }
    bool success = wrapped->Invoke(methodName, fbxArgs, result);
    return result.get_variant();
}