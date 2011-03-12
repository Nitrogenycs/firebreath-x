#ifndef FBXVARIANT_H
#define FBXVARIANT_H

#include "variant.h"
#include <string>

#define fbxvariant_entry(_type_, name)  \
    void set(const _type_& value);      \
    _type_ get_ ## name ();

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

    void set_empty();
    bool is_empty();

    void set_null();
    bool is_null();

    void set(FB::JSAPI* value);
    FB::JSAPI* get_object();
    FBXJSAPI* get_derived_object();

    void set(const FB::variant& Var);

    std::string get_type();
    FB::variant get_variant();

protected:
    FB::variant var;
    std::string type;
};

#endif