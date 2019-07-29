// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/FunctionalTestFactory.cpp
//! @brief     Defines FunctionalTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FunctionalTestFactory.h"

std::unique_ptr<IFunctionalTest> FunctionalTestFactory::createTest(std::string& test_name)
{
    auto result = create(test_name);
    result->setName(test_name);
    result->setDescription(m_descriptions[test_name]);
    return result;
}
