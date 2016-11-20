// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/Logger.h
//! @brief     Defines namespace Logging and class Logger.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LOGGER_H
#define LOGGER_H

#include "WinDllMacros.h"
#include <iomanip>
#include <sstream>
#include <vector>

//! Class Logger and utility functions for logging messages.

namespace Logging
{

enum EMessageLevel { VERBOSE, DEBUG2, DEBUG, INFO, WARNING, ERROR, FATAL };

//! Message service, used through macro msglog.
//! @ingroup tools_internal

class BA_CORE_API_ Logger
{
public:
    Logger(EMessageLevel level);

    template <typename T>
    Logger&  operator<<(T const&  value)
    {
        m_buffer << value;
        return *this;
    }

    ~Logger();

    std::string nowTime();
    const std::string& toString(EMessageLevel level);
    static void setLevel(EMessageLevel level);
    static void setLevel(const std::string& levelname);
    static EMessageLevel level();

private:
    static EMessageLevel m_logLevel;
    static std::vector<std::string > m_level_names;
    std::ostringstream m_buffer;
};

BA_CORE_API_ void setLevel(EMessageLevel level);
BA_CORE_API_ void setLevel(const std::string& levelname);

} // namespace Logging

#define msglog(_level) \
if (_level < Logging::Logger::level()) ; \
else Logging::Logger(_level)

#endif // LOGGER_H
