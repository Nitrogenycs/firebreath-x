%module(directors="1") FireBreath

%include "std_string.i"
%include "std_wstring.i"
%include "std_vector.i"

%template(StringVector) std::vector<std::string>;

%ignore fbxvariant::set(const FB::variant& Var);
%ignore fbxvariant::var;
%include "FBXVariant.h"
%template(VariantVector) std::vector<fbxvariant>;

namespace FB
{
    typedef int SecurityZone;

    enum SecurityLevel {
        SecurityScope_Public = 0,
        SecurityScope_Protected = 2,
        SecurityScope_Private = 4,
        SecurityScope_Local = 6
    };
}


%feature("director") FBXJSAPI;

class FBXJSAPI
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
    virtual size_t getMemberCount() const = 0;

    virtual bool HasProperty(const std::string& propertyName) const = 0;
    virtual bool HasProperty(int idx) const = 0;

    virtual bool GetProperty(int idx, fbxvariant& value) = 0;
    virtual bool GetProperty(const std::string& propertyName, fbxvariant& value) = 0;

    virtual bool SetProperty(int idx, const fbxvariant& value) = 0;
    virtual bool SetProperty(const std::string& propertyName, const fbxvariant& value) = 0;

    virtual bool HasMethod(const std::string& methodName) const = 0;

    virtual bool Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& result) = 0;
};
