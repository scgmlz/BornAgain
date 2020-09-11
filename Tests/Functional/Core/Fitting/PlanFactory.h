// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/PlanFactory.h
//! @brief     Defines class PlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLANFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLANFACTORY_H

#include "Fit/TestEngine/IFactory.h"
#include "Fit/TestEngine/MinimizerTestPlan.h"

//! Factory to generate plans for fitting with FitObjective.

class PlanFactory : public IFactory<std::string, MinimizerTestPlan>
{
public:
    PlanFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLANFACTORY_H
