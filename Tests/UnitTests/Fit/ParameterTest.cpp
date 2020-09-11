#include "Fit/Kernel/Parameter.h"
#include "Tests/GTestWrapper/google_test.h"
#include <string>

class ParameterTest : public ::testing::Test
{
};

TEST_F(ParameterTest, defaultConstructor)
{
    Fit::Parameter par;

    EXPECT_EQ(par.name(), "");
    EXPECT_EQ(par.value(), 0.0);
    EXPECT_EQ(par.startValue(), 0.0);
    EXPECT_EQ(par.error(), 0.0);
    EXPECT_EQ(par.step(), 0.0);
    AttLimits expected = AttLimits::limitless();
    EXPECT_EQ(par.limits(), expected);
}

TEST_F(ParameterTest, fullConstructor)
{
    AttLimits limits = AttLimits::limited(-10.0, 2.0);

    Fit::Parameter par("par0", 2.0, limits, 0.2);

    EXPECT_EQ(par.name(), "par0");
    EXPECT_EQ(par.value(), 2.0);
    EXPECT_EQ(par.startValue(), 2.0);
    EXPECT_EQ(par.error(), 0.0);
    EXPECT_EQ(par.step(), 0.2);
    EXPECT_EQ(par.limits().lowerLimit(), -10.0);
    EXPECT_EQ(par.limits().upperLimit(), 2.0);
}

TEST_F(ParameterTest, defaultStep)
{
    const double start_value = 2.0;
    const double hardcoded_step_factor = 0.01;
    Fit::Parameter par("par0", start_value, AttLimits::limitless());
    EXPECT_EQ(par.step(), start_value * hardcoded_step_factor);

    // fit parameter with zero start value
    Fit::Parameter par2("par0", 0.0, AttLimits::limitless());
    EXPECT_EQ(par2.step(), hardcoded_step_factor);
}

TEST_F(ParameterTest, setters)
{
    Fit::Parameter par("par0", 2.0, AttLimits::limitless(), 0.2);
    par.setValue(42.0);
    EXPECT_EQ(par.value(), 42.0);
    EXPECT_EQ(par.startValue(), 2.0); // start value shouldn't change

    par.setError(43.0);
    EXPECT_EQ(par.error(), 43.0);
}
