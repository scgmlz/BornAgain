// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/FitObjective/FitPlanFactory.h
//! @brief     Defines class FitPlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITPLANFACTORY_H
#define FITPLANFACTORY_H

#include "IFactory.h"
#include "MinimizerTestPlan.h"

//! Factory to generate plans for fitting with FitObjective.

class FitPlanFactory : public IFactory<std::string, MinimizerTestPlan>
{
public:
    FitPlanFactory();
};

#endif //   FITPLANFACTORY_H
