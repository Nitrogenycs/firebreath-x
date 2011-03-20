#ifndef FBXRESULT_H
#define FBXRESULT_H

#include <string>

class FBXResult
{
public:
    FBXResult();
    FBXResult(bool success, const std::string& message = "");

    bool success;
    std::string message;

    static FBXResult successful;
};

#endif