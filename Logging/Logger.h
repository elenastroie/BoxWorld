#pragma once
#include "defines.h"
#include <ostream>

class API_LOGGER Logger
{

public:
    enum class Level
    {
        Debug,
        Info,
        Warning,
        Error
    };

    Logger(std::ostream&, Level);
    Logger(const Logger&) = delete;
    Logger(Logger&&) noexcept = default;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    bool operator==(const Logger&) noexcept;

    virtual void Log(const std::string&, Level) const;
    auto Debug(const std::string&) const;
    auto Info(const std::string&) const;
    auto Warn(const std::string&) const;
    auto Error(const std::string&) const;
    void ForceFlush() const;

    const std::ostream& GetStream() const;
    Level GetLevel() const;
    bool GetAutoFlush() const;
    void SetAutoFlush(bool);

    virtual ~Logger() = default;

protected:
    inline virtual std::string GetSeparator() const;
    void MaybeFlush() const;

    std::ostream& m_output;
    const Level m_level;
    bool m_autoFlush{true};
};
