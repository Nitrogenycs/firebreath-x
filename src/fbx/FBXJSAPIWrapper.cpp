#include "FBXJSAPIWrapper.h"
#include "FBXVariant.h"

FBXJSAPIWrapper::FBXJSAPIWrapper( FB::JSAPIPtr Wrapped ) : wrapped(Wrapped)
{
}
        
FBXJSAPIWrapper::~FBXJSAPIWrapper()
{
}

std::vector<std::string> FBXJSAPIWrapper::getMemberNames() const
{
    std::vector<std::string> nameVector;
    wrapped->getMemberNames(nameVector);
    return nameVector;
}

size_t FBXJSAPIWrapper::getMemberCount() const
{
    return wrapped->getMemberCount();
}

bool FBXJSAPIWrapper::SetProperty(int idx, const fbxvariant& value) 
{
    wrapped->SetProperty( idx, value.get_variant() );
    return true;
}

bool FBXJSAPIWrapper::SetProperty(const std::string& propertyName, const fbxvariant& value) 
{
    wrapped->SetProperty( propertyName, value.get_variant() );
    return true;
}
        
bool FBXJSAPIWrapper::GetProperty(int idx, fbxvariant& value)
{
    FB::variant result = wrapped->GetProperty(idx);
    value.set(result);
    return true;
}

bool FBXJSAPIWrapper::GetProperty(const std::string& propertyName, fbxvariant& value)
{
    FB::variant result = wrapped->GetProperty(propertyName);
    value.set(result);
    return true;
}


bool FBXJSAPIWrapper::HasProperty(int idx) const
{
    return wrapped->HasProperty(idx);
}

bool FBXJSAPIWrapper::HasProperty(const std::string& propertyName) const
{
    return wrapped->HasProperty(propertyName);
}

bool FBXJSAPIWrapper::HasMethod(const std::string& methodName) const
{
    return wrapped->HasMethod(methodName);
}

bool FBXJSAPIWrapper::Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& returnValue)
{
    std::vector<FB::variant> fbArgs(args.size());
    for ( size_t i = 0; i < args.size(); i++ ) {
        fbArgs[i] = args[i].get_variant();
    }
    FB::variant value = wrapped->Invoke(methodName, fbArgs);
    returnValue.set( value );
    return true;
}