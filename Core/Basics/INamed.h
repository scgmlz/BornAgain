// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/INamed.h
//! @brief     Defines and implements the standard mix-in INamed.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INAMED_H
#define INAMED_H

#include <string>
#include "WinDllMacros.h"

//! Interface for named objects.
//! @ingroup tools_internal

class BA_CORE_API_ INamed
{
public:
    INamed() : m_name() {}
    INamed(const std::string& name) : m_name(name) {}
    virtual ~INamed() {}
    std::string getName() const { return m_name; }

protected:
    void setName(const std::string& name) { m_name = name; }

private:
    std::string m_name;
};

#endif // INAMED_H
