#include "FBXResult.h"

FBXResult FBXResult::successful = FBXResult(true);

FBXResult::FBXResult(bool Success, const std::string& Message) : success(Success), message(Message)
{
}