// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/PlanCases.h
//! @brief     Defines collection of FunctionTestPlan classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_PLANCASES_H
#define BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_PLANCASES_H

#include "Tests/Functional/Fit/Minimizer/ResidualTestPlan.h"
#include "Tests/Functional/Fit/Minimizer/ScalarTestPlan.h"

//! Setting for standalone fit of Rosenbrock function.

class RosenbrockPlan : public ScalarTestPlan
{
public:
    RosenbrockPlan();
};

//! Setting for standalone fit of Rosenbrock function. Fit parameter limits
//! are made small here to help stochastic minimizer to converge in reasonable time.

class EasyRosenbrockPlan : public ScalarTestPlan
{
public:
    EasyRosenbrockPlan();
};

//! Setting for standalone fit of WoodFour function.

class WoodFourPlan : public ScalarTestPlan
{
public:
    WoodFourPlan();
};

//! Setting for standalone fit of WoodFour function. Fit parameter limits
//! are made small here to help stochastic minimizer to converge in reasonable time.

class EasyWoodFourPlan : public ScalarTestPlan
{
public:
    EasyWoodFourPlan();
};

//! Settings for standalone fit using Minimizer's residual interface.
//! "Decaying sin" objective function from lmfit tutorial is used.

class DecayingSinPlan : public ResidualTestPlan
{
public:
    DecayingSinPlan();
};

//! Same as DecayingSinPlan with fewer fit parameters

class DecayingSinPlanV2 : public ResidualTestPlan
{
public:
    DecayingSinPlanV2();
};

//! Special plan to test TestMinimizer.

class TestMinimizerPlan : public ScalarTestPlan
{
public:
    TestMinimizerPlan();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_PLANCASES_H
