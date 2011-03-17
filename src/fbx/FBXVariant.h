#ifndef FBXVARIANT_H
#define FBXVARIANT_H

#include "variant.h"
#include <string>

#define fbxvariant_entry_def(_type_, name)  \
    void set(const _type_& value);          \
    _type_ get_ ## name ();

class FBXJSAPI;

class fbxvariant
{
public:
    fbxvariant_entry_def(bool, bool)
    fbxvariant_entry_def(int, int)
    fbxvariant_entry_def(unsigned int, uint)
    fbxvariant_entry_def(double, double)
    fbxvariant_entry_def(float, float)
    //fbxvariant_entry_def(std::string, string)
    fbxvariant_entry_def(std::wstring, wstring)
    //fbxvariant_entry_def(long, long)
    //fbxvariant_entry_def(unsigned long, ulong)
    fbxvariant_entry_def(short, short)
    fbxvariant_entry_def(unsigned short, ushort)
    fbxvariant_entry_def(char, char)
    fbxvariant_entry_def(unsigned char, uchar)
    fbxvariant_entry_def(long long, int64)
    fbxvariant_entry_def(unsigned long long, uint64)

    void set_empty();
    bool is_empty();

    void set_null();
    bool is_null();

    void set(FBXJSAPI* value);
    FBXJSAPI* get_object();

    void set(const FB::variant& var);

    std::string get_type() const;
    FB::variant get_variant() const;

protected:
    FB::variant var;
    std::string type;
};

#undef fbxvariant_entry_def

#endif