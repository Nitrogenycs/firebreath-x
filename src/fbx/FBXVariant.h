#ifndef FBXVARIANT_H
#define FBXVARIANT_H

#include "variant.h"
#include <string>

#define fbxvariant_entry(_type_, name)   \
    void set(const _type_& value) {        \
        var = value;                       \
    }                                      \
    _type_ get_ ## name () {               \
        return var.cast<_type_>();         \
    }

#define type_entry(_type_, name)           \
    if (*varType == typeid(_type_)) {      \
        type = #name;                      \
    }

class FBXJSAPI;

class fbxvariant
{
public:
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

    void set_empty() {
        var = FB::FBVoid();
        type = "empty";
    }
    bool is_empty() {
        return var.empty();
    }

    void set_null() {
        var = FB::FBNull();
        type = "null";
    }
    bool is_null() {
        return var.is_null();
    }

    void set(FB::JSAPI* value) {
        var = FB::JSAPIPtr(value);
        type = "jsapi";
    }
    FB::JSAPI* get_object () {
        return var.cast<FB::JSAPIPtr>().get();
    }

    void set(const FB::variant& Var)
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

    std::string get_type() const {
        return type;
    }

    FB::variant get_variant() const {
        return var;
    }

protected:
    FB::variant var;
    std::string type;
};

#endif