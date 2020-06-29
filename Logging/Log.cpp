#include "Log.h"
#include <iostream>
#include <algorithm>

void Log::Debug(const std::string& message)
{
    LogAll(message, Logger::Level::Debug);
}

void Log::Info(const std::string& message)
{
    LogAll(message, Logger::Level::Info);
}

void Log::Warn(const std::string& message)
{
    LogAll(message, Logger::Level::Warning);
}

void Log::Error(const std::string& message)
{
    LogAll(message, Logger::Level::Error);
}

void Log::RegisterLogger(Logger& logger)
{
    const auto it = WhereLogger(logger);
    if (it == s_loggers.end())
    {
        s_loggers.push_back(&logger);
    }
}

void Log::UnregisterLogger(const Logger& logger)
{
    const auto it = WhereLogger(logger);
    if (it != s_loggers.end())
    {
        s_loggers.erase(it);
    }
}

void Log::UnregisterAllLoggers()
{
    for (const auto& logger : s_loggers)
    {
        UnregisterLogger(*logger);
    }
}

std::vector<Logger*>::iterator Log::WhereLogger(const Logger& logger)
{
    return std::find_if(s_loggers.begin(), s_loggers.end(), [&logger](const Logger* elem) -> bool
    {
        return &logger == elem;
    });
}

void Log::LogAll(const std::string& message, const Logger::Level level)
{
    for (const auto& logger : s_loggers)
    {
        if (logger != nullptr)
        {
            logger->Log(message, level);
        }
    }
}

std::vector<Logger*> Log::s_loggers{};
