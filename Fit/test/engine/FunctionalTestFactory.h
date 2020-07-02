// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/engine/FunctionalTestFactory.h
//! @brief     Defines FunctionalTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTFACTORY_H
#define FUNCTIONALTESTFACTORY_H

#include "IFactory.h"
#include "IFunctionalTest.h"

//! Simple factory to hold packs of functional tests.

class BA_CORE_API_ FunctionalTestFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    std::unique_ptr<IFunctionalTest> createTest(std::string& test_name);
};

#endif
