#pragma once
#include "defines.h"
#include "Logger.h"

class API_LOGGER FormattingLogger : public Logger
{
public:
    FormattingLogger(std::ostream&, const Level&);

    void Log(const std::string&, Level) const override;

protected:
    [[nodiscard]] virtual std::string GetPrefix() const = 0;
    [[nodiscard]] virtual std::string GetSuffix() const = 0;
};
