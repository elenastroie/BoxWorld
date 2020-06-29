#include "LoggingUtils.h"
#include <string>

std::string Logging::LoggingUtils::PadLeft(std::string const& str, const size_t s, const char pad)
{
    if (str.size() < s)
    {
        return std::string(s - str.size(), pad) + str;
    }
    return str;
}

std::string Logging::LoggingUtils::PadRight(std::string const& str, const size_t s, const char pad)
{
    if (str.size() < s)
    {
        return str + std::string(s - str.size(), pad);
    }
    return str;
}
