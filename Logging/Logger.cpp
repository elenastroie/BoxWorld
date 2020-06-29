#include "Logger.h"
#include <iostream>

Logger::Logger(std::ostream& output, const Level level) : m_output(output), m_level(level) {}

bool Logger::operator==(const Logger& other) noexcept
{
    return this == &other;
}

void Logger::Log(const std::string& message, const Level level) const
{
    if (level >= m_level)
    {
        m_output << message << GetSeparator();
        MaybeFlush();
    }
}

auto Logger::Debug(const std::string& message) const
{
    return Log(message, Level::Debug);
}

auto Logger::Info(const std::string& message) const
{
    return Log(message, Level::Info);
}

auto Logger::Warn(const std::string& message) const
{
    return Log(message, Level::Warning);
}

auto Logger::Error(const std::string& message) const
{
    return Log(message, Level::Error);
}

void Logger::ForceFlush() const
{
    m_output.flush();
}

const std::ostream& Logger::GetStream() const { return m_output; }

Logger::Level Logger::GetLevel() const { return m_level; }

bool Logger::GetAutoFlush() const { return m_autoFlush; }

void Logger::SetAutoFlush(const bool autoFlush) { m_autoFlush = autoFlush; }

std::string Logger::GetSeparator() const { return "\n"; }

void Logger::MaybeFlush() const
{
    if (m_autoFlush)
    {
        ForceFlush();
    }
}
