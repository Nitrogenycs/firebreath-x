#ifndef FBXRESULT_H
#define FBXRESULT_H

#include <string>

struct FBXResult
{
    bool success;
    std::string message;

    FBXResult(bool success, const std::string& message = "");

    static FBXResult successful;
};

#endif