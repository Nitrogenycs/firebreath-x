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

FBXResult FBXJSAPIWrapper::SetProperty(int idx, const fbxvariant& value) 
{
    try
    {
        wrapped->SetProperty( idx, value.get_variant() );
    }
    catch (FB::script_error& e)
    {
        return FBXResult(false, "Error setting property '" + boost::lexical_cast<std::string>(idx) + "'. Reason: " + e.what());
    }
    return FBXResult::successful;
}

FBXResult FBXJSAPIWrapper::SetProperty(const std::string& propertyName, const fbxvariant& value) 
{
    try
    {
        wrapped->SetProperty( propertyName, value.get_variant() );
    }
    catch (FB::script_error& e)
    {
        return FBXResult(false, "Error setting property '" + propertyName + "'. Reason: " + e.what());
    }
    return FBXResult::successful;
}
        
FBXResult FBXJSAPIWrapper::GetProperty(int idx, fbxvariant& value)
{
    FB::variant result;
    try
    {
        result = wrapped->GetProperty(idx);
    }
    catch (FB::script_error& e)
    {
        return FBXResult(false, "Error getting property '" + boost::lexical_cast<std::string>(idx) + "'. Reason: " + e.what());
    }
    value.set(result);
    return FBXResult::successful;
}

FBXResult FBXJSAPIWrapper::GetProperty(const std::string& propertyName, fbxvariant& value)
{
    FB::variant result;
    try
    {
        result = wrapped->GetProperty(propertyName);
    }
    catch (FB::script_error& e)
    {
        return FBXResult(false, "Error getting property '" + propertyName + "'. Reason: " + e.what());
    }
    value.set(result);
    return FBXResult::successful;
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

FBXResult FBXJSAPIWrapper::Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& returnValue)
{
    std::vector<FB::variant> fbArgs(args.size());
    for ( size_t i = 0; i < args.size(); i++ ) {
        fbArgs[i] = args[i].get_variant();
    }

    FB::variant value;
    try
    {
        value = wrapped->Invoke(methodName, fbArgs);
    }
    catch (FB::script_error& e)
    {
        return FBXResult(false, "Error invoking method '" + methodName + "'. Reason: " + e.what());
    }
    returnValue.set( value );
    return FBXResult::successful;
}