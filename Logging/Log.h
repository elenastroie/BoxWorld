#pragma once
#include <vector>
#include "defines.h"
#include "Logger.h"

class API_LOGGER Log
{
public:
    Log() = delete;

    static void Debug(const std::string&);
    static void Info(const std::string&);
    static void Warn(const std::string&);
    static void Error(const std::string&);

    static void RegisterLogger(Logger&);
    static void UnregisterLogger(const Logger&);
    static void UnregisterAllLoggers();

private:
    static std::vector<Logger*>::iterator WhereLogger(const Logger& logger);
    static void LogAll(const std::string&, Logger::Level);

    static std::vector<Logger*> s_loggers;
};
