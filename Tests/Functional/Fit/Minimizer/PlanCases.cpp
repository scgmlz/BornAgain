// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/PlanCases.cpp
//! @brief     Defines collection of FunctionTestPlan classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Fit/Minimizer/PlanCases.h"
#include "Fit/Kernel/Parameter.h"
#include "Tests/Functional/Fit/Minimizer/ClassicalTestFunctions.h"

namespace
{
const double loose_tolerance_on_function_min = 0.1;
}

using namespace Fit;

//! Plan to minimize a Rosenbrock function.
//! start point: F(-1.2,1.0) = 24.20
//! minimum    : F(1.0,1.0)  = 0.

RosenbrockPlan::RosenbrockPlan() : ScalarTestPlan("RosenbrockPlan", TestFunctions::RosenBrock, 0.0)
{
    addParameter(Parameter("par0", -1.2, AttLimits::limited(-5.0, 5.0), 0.01), 1.0);
    addParameter(Parameter("par1", 1.0, AttLimits::limited(-5.0, 5.0), 0.01), 1.0);
}

EasyRosenbrockPlan::EasyRosenbrockPlan()
    : ScalarTestPlan("EasyRosenbrockPlan", TestFunctions::RosenBrock, 0.0,
                     loose_tolerance_on_function_min)
{
    // narrow parameter limits and big tolerance for stochastic minimizers
    const double tolerance = 0.1;
    addParameter(Parameter("par0", 1.1, AttLimits::limited(0.8, 1.2), 0.01), 1.0, tolerance);
    addParameter(Parameter("par1", 1.1, AttLimits::limited(0.8, 1.2), 0.01), 1.0, tolerance);
}

//! Plan for WoodFour function
//!   start point: F(-3,-1,-3,-1) = 19192
//!   minimum    : F(1,1,1,1)  =   0.

WoodFourPlan::WoodFourPlan() : ScalarTestPlan("WoodFourPlan", TestFunctions::WoodFour, 0.0)
{
    addParameter(Parameter("par0", -3.0, AttLimits::limited(-5.0, 5.0)), 1.0);
    addParameter(Parameter("par1", -1.0, AttLimits::limited(-5.0, 5.0)), 1.0);
    addParameter(Parameter("par2", -3.0, AttLimits::limited(-5.0, 5.0)), 1.0);
    addParameter(Parameter("par3", -1.0, AttLimits::limited(-5.0, 5.0)), 1.0);
}

EasyWoodFourPlan::EasyWoodFourPlan()
    : ScalarTestPlan("EasyWoodFourPlan", TestFunctions::WoodFour, 0.0,
                     loose_tolerance_on_function_min)
{
    // narrow parameter limits and big tolerance for stochastic minimizers
    const double tolerance = 0.1;
    addParameter(Parameter("par0", 1.1, AttLimits::limited(0.8, 1.2)), 1.0, tolerance);
    addParameter(Parameter("par1", 1.1, AttLimits::limited(0.8, 1.2)), 1.0, tolerance);
    addParameter(Parameter("par2", 1.1, AttLimits::limited(0.8, 1.2)), 1.0, tolerance);
    addParameter(Parameter("par3", 1.1, AttLimits::limited(0.8, 1.2)), 1.0, tolerance);
}

DecayingSinPlan::DecayingSinPlan() : ResidualTestPlan("DecayingSinPlan", TestFunctions::DecayingSin)
{
    addParameter(Parameter("amp", 1.0, AttLimits::nonnegative()), 10.0);
    addParameter(Parameter("frequency", 1.0, AttLimits::nonnegative()), 4.0);
    addParameter(Parameter("phase", 0.1, AttLimits::limited(0.0, 3.1)), 1.0);
    addParameter(Parameter("decay", 0.1, AttLimits::nonnegative()), 0.05);
}

DecayingSinPlanV2::DecayingSinPlanV2()
    : ResidualTestPlan("DecayingSinPlanV2", TestFunctions::DecayingSin)
{
    addParameter(Parameter("amp", 1.0, AttLimits::limitless()), 2.0);
    addParameter(Parameter("frequency", 1.0, AttLimits::limitless()), 2.0);
    addParameter(Parameter("phase", 1.0, AttLimits::fixed()), 1.0);
    addParameter(Parameter("decay", 0.05, AttLimits::fixed()), 0.05);
}

TestMinimizerPlan::TestMinimizerPlan()
    : ScalarTestPlan("TestMinimizerPlan", TestFunctions::RosenBrock, 0.0)
{
    // starting values of fit parameters are already correct
    addParameter(Parameter("par0", 1.0, AttLimits::limited(-5.0, 5.0), 0.01), 1.0);
    addParameter(Parameter("par1", 1.0, AttLimits::limited(-5.0, 5.0), 0.01), 1.0);
}
