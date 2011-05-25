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
    FBXResult result = wrapped->SetProperty( idx, var );
    if ( !result.success )
    {
        throw FB::script_error("Error setting property '" + boost::lexical_cast<std::string>(idx) + "'. Reason: " + result.message );
    }
}

void JSAPIWrapper::SetProperty(const std::string& propertyName, const FB::variant& value) 
{
    fbxvariant var;
    var.set( value );
    FBXResult result = wrapped->SetProperty( propertyName, var );
    if ( !result.success )
    {
        throw FB::script_error("Error setting property '" + propertyName + "'. Reason: " + result.message );
    }
}
    
FB::variant JSAPIWrapper::GetProperty(int idx)
{
    fbxvariant value;
    FBXResult result = wrapped->GetProperty( idx, value );
    if ( !result.success )
    {
        throw FB::script_error("Error getting property '" + boost::lexical_cast<std::string>(idx) + "'. Reason: " + result.message );
    }
    return value.get_variant();
}

FB::variant JSAPIWrapper::GetProperty(const std::string& propertyName)
{
    fbxvariant value;
    FBXResult result = wrapped->GetProperty( propertyName, value );
    if ( !result.success )
    {
        throw FB::script_error("Error getting property '" + propertyName + "'. Reason: " + result.message );
    }
    return value.get_variant();
}

bool JSAPIWrapper::RemoveProperty(int idx) 
{
    FBXResult result = wrapped->RemoveProperty( idx );
    /*if ( !result.success )
    {
        throw FB::script_error("Error removing property '" + boost::lexical_cast<std::string>(idx) + "'. Reason: " + result.message );
    }*/
    return result.success;
}

bool JSAPIWrapper::RemoveProperty(const std::string& propertyName) 
{
    FBXResult result = wrapped->RemoveProperty( propertyName );
    /*if ( !result.success )
    {
        throw FB::script_error("Error removing property '" + propertyName + "'. Reason: " + result.message );
    }*/
    return result.success;
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
    fbxvariant returnValue;
    std::vector<fbxvariant> fbxArgs(args.size());
    for ( size_t i = 0; i < args.size(); i++ ) {
        fbxArgs[i].set( args[i] );
    }
    FBXResult result = wrapped->Invoke(methodName, fbxArgs, returnValue);
    if ( !result.success )
    {
        throw FB::script_error("Error invoking method '" + methodName + "'. Reason: " + result.message);
    }
    return returnValue.get_variant();
}

FB::variant JSAPIWrapper::Construct(const std::vector<FB::variant>& args)
{
    fbxvariant returnValue;
    std::vector<fbxvariant> fbxArgs(args.size());
    for ( size_t i = 0; i < args.size(); i++ ) {
        fbxArgs[i].set( args[i] );
    }
    FBXResult result = wrapped->Construct(fbxArgs, returnValue);
    if ( !result.success )
    {
        throw FB::script_error("Error invoking constructor. Reason: " + result.message);
    }
    return returnValue.get_variant();
}