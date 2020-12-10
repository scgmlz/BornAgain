//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Test/Minimizer/PlanFactory.cpp
//! @brief     Implements class FunctionTestPlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Test/Minimizer/PlanFactory.h"
#include "Fit/Test/Minimizer/PlanCases.h"

using mumufit::test::create_new;

PlanFactory::PlanFactory() {
    registerItem("RosenbrockPlan", create_new<RosenbrockPlan>);
    registerItem("EasyRosenbrockPlan", create_new<EasyRosenbrockPlan>);
    registerItem("WoodFourPlan", create_new<WoodFourPlan>);
    registerItem("EasyWoodFourPlan", create_new<EasyWoodFourPlan>);
    registerItem("DecayingSinPlan", create_new<DecayingSinPlan>);
    registerItem("DecayingSinPlanV2", create_new<DecayingSinPlanV2>);
    registerItem("TestMinimizerPlan", create_new<TestMinimizerPlan>);
}
