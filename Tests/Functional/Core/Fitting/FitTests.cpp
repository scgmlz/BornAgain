// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/FitTests.cpp
//! @brief     Defines classes from FitObjectiveTest family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/Minimizer.h"
#include "Fit/TestEngine/MinimizerTestPlan.h"
#include "Tests/Functional/Core/Fitting/PlanFactory.h"
#include "Tests/GTestWrapper/google_test.h"

class Fitting : public ::testing::Test
{
};

bool run(const std::string& minimizer_name, const std::string& algorithm_name,
         const std::string& fit_plan_name, const std::string& options = "")
{
    auto plan = PlanFactory().createItemPtr(fit_plan_name);
    Fit::Minimizer minimizer;
    minimizer.setMinimizer(minimizer_name, algorithm_name, options);
    return plan->checkMinimizer(minimizer);
}

TEST_F(Fitting, MigradCylindersInBA)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "CylindersInBAPlan"));
}

TEST_F(Fitting, MigradResidualCylindersInBA)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "CylindersInBAResidualPlan"));
}

TEST_F(Fitting, BfgsCylindersInBA)
{
    EXPECT_TRUE(run("GSLMultiMin", "BFGS2", "CylindersInBAEasyPlan"));
}

/* TODO: restore
TEST_F(Fitting, SteepestDescentCylindersInBA)
{
    EXPECT_TRUE(run("GSLMultiMin", "SteepestDescent", "CylindersInBAEasyPlan"));
}
*/

TEST_F(Fitting, FumuliCylindersInBA)
{
    EXPECT_TRUE(run("Minuit2", "Fumili", "CylindersInBAResidualPlan"));
}

TEST_F(Fitting, LevenbergMarquardtCylindersInBA)
{
    EXPECT_TRUE(run("GSLLMA", "", "CylindersInBAResidualPlan"));
}

TEST_F(Fitting, SimAnCylindersInBA)
{
    EXPECT_TRUE(run("GSLSimAn", "", "CylindersInBAEasyPlan",
                    "IterationsAtTemp=5;MaxIterations=10;t_min=1.0"));
}

TEST_F(Fitting, GeneticCylindersInBA)
{
    EXPECT_TRUE(run("Genetic", "", "CylindersInBAEasyPlan", "MaxIterations=1;RandomSeed=1"));
}

TEST_F(Fitting, RectDetectorFit)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "RectDetPlan", "Strategy=2"));
}

/* TODO: restore
TEST_F(Fitting, AdjustMinimizerFit)
{
    EXPECT_TRUE(run("Genetic", "", "AdjustMinimizerPlan"));
}
*/

TEST_F(Fitting, SpecularFitTest)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "SpecularPlan"));
}

TEST_F(Fitting, SpecularFitTestQ)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "SpecularPlanQ"));
}

TEST_F(Fitting, MultipleSpecFittingTest)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "MultipleSpecPlan"));
}

TEST_F(Fitting, OffSpecFitTest)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "OffSpecPlan"));
}
