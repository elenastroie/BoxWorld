#include "FormattingLogger.h"

FormattingLogger::FormattingLogger(std::ostream& output, const Level& level) : Logger(output, level) {}

void FormattingLogger::Log(const std::string& message, const Level level) const
{
    if (level >= m_level)
    {
        m_output << GetPrefix() << message << GetSuffix() << GetSeparator();
        MaybeFlush();
    }
}
