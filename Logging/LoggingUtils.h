#pragma once
#include <string>

namespace Logging
{
    class LoggingUtils
    {
    public:
        LoggingUtils() = delete;
        static std::string PadLeft(const std::string&, size_t, char = ' ');
        static std::string PadRight(const std::string&, size_t, char = ' ');
    };
}
