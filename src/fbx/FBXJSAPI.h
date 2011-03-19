#ifndef FBXJSAPI_H
#define FBXJSAPI_H

#include <vector>
#include <string>

#include "FBXResult.h"

class fbxvariant;

class FBXJSAPI
{
public:
    virtual
    ~FBXJSAPI();

public:
    virtual std::vector<std::string> getMemberNames() const = 0;
    virtual size_t getMemberCount() const = 0;

    virtual FBXResult SetProperty(int idx, const fbxvariant& value) = 0;
    virtual FBXResult SetProperty(const std::string& propertyName, const fbxvariant& value) = 0;    

    virtual FBXResult GetProperty(const std::string& propertyName, fbxvariant& value) = 0;    
    virtual FBXResult GetProperty(int idx, fbxvariant& value) = 0;

    virtual bool HasProperty(const std::string& propertyName) const = 0;
    virtual bool HasProperty(int idx) const = 0;
    
    virtual bool HasMethod(const std::string& methodName) const= 0;

    virtual FBXResult Invoke(const std::string& methodName, const std::vector<fbxvariant>& args, fbxvariant& returnValue) = 0;
};

#endif