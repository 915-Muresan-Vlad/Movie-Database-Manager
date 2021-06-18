#include "CustomExceptions.h"


const char *CustomExceptions::what() const noexcept
{
    return errorMessage.c_str();
}

CustomExceptions::CustomExceptions(const std::string &errorMessage) : errorMessage(errorMessage) {}
