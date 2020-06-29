#pragma once
#include "defines.h"
#include "FormattingLogger.h"

class API_LOGGER TimeLogger : public FormattingLogger
{
public:
    TimeLogger(std::ostream&, const Level&);

protected:
    [[nodiscard]] std::string GetPrefix() const override;
    [[nodiscard]] std::string GetSuffix() const override;
};
