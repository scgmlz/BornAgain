//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Test/Minimizer/PlanFactory.h
//! @brief     Defines class FunctionTestPlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_FIT_TEST_MINIMIZER_PLANFACTORY_H
#define BORNAGAIN_FIT_TEST_MINIMIZER_PLANFACTORY_H

#include "Fit/TestEngine/IFactory.h"
#include "Fit/TestEngine/MinimizerTestPlan.h"

//! Factory to generate plans for fitting objective functions.

class PlanFactory : public mumufit::test::IFactory<std::string, MinimizerTestPlan> {
public:
    PlanFactory();
};

#endif // BORNAGAIN_FIT_TEST_MINIMIZER_PLANFACTORY_H
