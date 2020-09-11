// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTests.cpp
//! @brief     Implements classes from MinimizerTest family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/Minimizer.h"
#include "Fit/TestEngine/MinimizerTestPlan.h"
#include "Tests/Functional/Fit/Minimizer/PlanFactory.h"
#include "Tests/GTestWrapper/google_test.h"

class Minimize : public ::testing::Test
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

TEST_F(Minimize, MinuitTestV1)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "RosenbrockPlan"));
}

TEST_F(Minimize, MinuitTestV2)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "WoodFourPlan"));
}

TEST_F(Minimize, MinuitTestV3)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "DecayingSinPlan"));
}

/* known to fail
TEST_F(Minimize, SteepestDescentTestV1)
{
    EXPECT_TRUE(run("GSLMultiMin", "SteepestDescent", "RosenbrockPlan"));
}
*/

TEST_F(Minimize, SteepestDescentTestV2)
{
    EXPECT_TRUE(run("GSLMultiMin", "SteepestDescent", "WoodFourPlan"));
}

TEST_F(Minimize, ConjugateFRTestV1)
{
    EXPECT_TRUE(run("GSLMultiMin", "ConjugateFR", "RosenbrockPlan"));
}

TEST_F(Minimize, ConjugateFRTestV2)
{
    EXPECT_TRUE(run("GSLMultiMin", "ConjugateFR", "WoodFourPlan"));
}

TEST_F(Minimize, ConjugatePRTestV1)
{
    EXPECT_TRUE(run("GSLMultiMin", "ConjugatePR", "RosenbrockPlan"));
}

TEST_F(Minimize, ConjugatePRTestV2)
{
    EXPECT_TRUE(run("GSLMultiMin", "ConjugatePR", "WoodFourPlan"));
}

TEST_F(Minimize, BfgsTestV1)
{
    EXPECT_TRUE(run("GSLMultiMin", "BFGS", "RosenbrockPlan"));
}

TEST_F(Minimize, BfgsTestV2)
{
    EXPECT_TRUE(run("GSLMultiMin", "BFGS", "WoodFourPlan"));
}

TEST_F(Minimize, Bfgs2TestV1)
{
    EXPECT_TRUE(run("GSLMultiMin", "BFGS2", "RosenbrockPlan"));
}

TEST_F(Minimize, Bfgs2TestV2)
{
    EXPECT_TRUE(run("GSLMultiMin", "BFGS2", "WoodFourPlan"));
}

TEST_F(Minimize, GSLSimAnTestV1)
{
    EXPECT_TRUE(run("GSLSimAn", "Default", "EasyRosenbrockPlan"));
}

TEST_F(Minimize, GSLSimAnTestV2)
{
    EXPECT_TRUE(run("GSLSimAn", "Default", "EasyWoodFourPlan"));
}

TEST_F(Minimize, GeneticTestV1)
{
    EXPECT_TRUE(run("Genetic", "Default", "EasyRosenbrockPlan", "RandomSeed=1"));
}

TEST_F(Minimize, GeneticTestV2)
{
    EXPECT_TRUE(run("Genetic", "Default", "EasyWoodFourPlan", "RandomSeed=1"));
}

TEST_F(Minimize, FumiliTestV3)
{
    EXPECT_TRUE(run("Minuit2", "Fumili", "DecayingSinPlan", "MaxFunctionCalls=10000"));
}

TEST_F(Minimize, LevenbergMarquardtV3)
{
    EXPECT_TRUE(run("GSLLMA", "Default", "DecayingSinPlanV2"));
}

TEST_F(Minimize, TestMinimizerV1)
{
    EXPECT_TRUE(run("Test", "Default", "TestMinimizerPlan"));
}
