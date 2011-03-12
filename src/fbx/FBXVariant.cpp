#include "FBXVariant.h"
#include "FBXJSAPI.h"

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
    }

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

void fbxvariant::set(FB::JSAPI* value) {
    var = FB::JSAPIPtr(value);
    type = "jsapi";
}
FB::JSAPI* fbxvariant::get_object () {
    return var.cast<FB::JSAPIPtr>().get();
}
FBXJSAPI* fbxvariant::get_derived_object () {
    return dynamic_cast<FBXJSAPI*>( get_object() );
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
    //type_entry(std::string, string)
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
    type_entry(FB::JSAPIPtr, jsapi)
}

std::string fbxvariant::get_type() const {
    return type;
}

FB::variant fbxvariant::get_variant() const {
    return var;
}
