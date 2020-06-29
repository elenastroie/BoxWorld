#include "TimeLogger.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "LoggingUtils.h"

TimeLogger::TimeLogger(std::ostream& stream, const Level& level): FormattingLogger(stream, level) {}

std::string TimeLogger::GetPrefix() const
{
    const auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    tm tm{};
    const auto local = localtime_s(&tm, &time);
    if (local)
    {
        throw std::exception((std::string("Couldn't get local time. Error Code: ") + std::to_string(local)).c_str());
    }
    std::stringstream ss;

    ss << '[' <<
        Logging::LoggingUtils::PadLeft(std::to_string(tm.tm_hour), 2, '0') << ':' << 
        Logging::LoggingUtils::PadLeft(std::to_string(tm.tm_min), 2, '0') << ':' << 
        Logging::LoggingUtils::PadLeft(std::to_string(tm.tm_sec), 2, '0') << ' ' <<

        Logging::LoggingUtils::PadLeft(std::to_string(tm.tm_mday), 2, '0') << '/' << 
        Logging::LoggingUtils::PadLeft(std::to_string(1 + tm.tm_mon), 2, '0') << '/' << 
        1900 + tm.tm_year << 
        "] ";

    return ss.str();
}

std::string TimeLogger::GetSuffix() const { return ""; }
