// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/engine/IFunctionalTest.h
//! @brief     Defines IFunctionalTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IFUNCTIONALTEST_H
#define IFUNCTIONALTEST_H

#include "INamed.h"
#include <map>

//! Base class for all functional tests.
//! @class IFunctionalTest

class BA_CORE_API_ IFunctionalTest : public INamed
{
public:
    IFunctionalTest() {}
    IFunctionalTest(const std::string& name, const std::string& description)
        : INamed(name), m_description(description)
    {
    }
    virtual ~IFunctionalTest();

    bool execute();

    std::string description() const { return m_description; }
    void setDescription(const std::string& description) { m_description = description; }

    using INamed::setName;

protected:
    virtual bool runTest() = 0; //!< Returns true when successful

    std::string m_description;
};

#endif // IFUNCTIONALTEST_H
