#include "FBXVariant.h"
#include "FBXJSAPIWrapper.h"
#include "JSAPIWrapper.h"

#define fbxvariant_entry(_type_, name)          \
    void fbxvariant::set(const _type_& value) { \
        var = value;                            \
    }                                           \
    _type_ fbxvariant::get_ ## name () {        \
        return var.cast<_type_>();              \
    }

#define type_entry(_type_, name)                \
    if (*varType == typeid(_type_)) {           \
        type = #name;                           \
    } else 

fbxvariant_entry(bool, bool)
fbxvariant_entry(int, int)
fbxvariant_entry(unsigned int, uint)
fbxvariant_entry(double, double)
fbxvariant_entry(float, float)
//fbxvariant_entry(std::string, string)
fbxvariant_entry(std::wstring, wstring)
//fbxvariant_entry(long, long);
//fbxvariant_entry(unsigned long, ulong);
fbxvariant_entry(short, short)
fbxvariant_entry(unsigned short, ushort)
fbxvariant_entry(char, char)
fbxvariant_entry(unsigned char, uchar)
fbxvariant_entry(long long, int64)
fbxvariant_entry(unsigned long long, uint64)


void fbxvariant::set_empty() {
    var = FB::FBVoid();
    type = "empty";
}
bool fbxvariant::is_empty() {
    return var.empty();
}

void fbxvariant::set_null() {
    var = FB::FBNull();
    type = "null";
}
bool fbxvariant::is_null() {
    return var.is_null();
}

void fbxvariant::set(FBXJSAPI* value) {
    var = boost::make_shared<JSAPIWrapper>(value);
    type = "jsapi";
}
FBXJSAPI* fbxvariant::get_object () {
    return new FBXJSAPIWrapper( var.cast<FB::JSAPIPtr>() );
}

void fbxvariant::set(const FB::variant& Var)
{
    var = Var;
    const std::type_info *varType(&var.get_type());

    type_entry(bool, bool)
    type_entry(int, int)
    type_entry(unsigned int, uint)
    type_entry(double, double)
    type_entry(float, float)
    //type_entry(std::string, wstring)
    type_entry(std::wstring, wstring)
    //type_entry(long, long);
    //type_entry(unsigned long, ulong);
    type_entry(short, short)
    type_entry(unsigned short, ushort)
    type_entry(char, char)
    type_entry(unsigned char, uchar)
    type_entry(long long, int64)
    type_entry(unsigned long long, uint64)
    type_entry(FB::FBVoid(), empty)
    type_entry(FB::FBNull(), null)
    type_entry(FB::JSAPIPtr, object)
    if (*varType == typeid(std::string)) {
        var = FB::utf8_to_wstring(Var.cast<std::string>());
        type = "wstring";
    } else 
    {
        // unknown type here
    }
}

std::string fbxvariant::get_type() const {
    return type;
}

FB::variant fbxvariant::get_variant() const {
    return var;
}
