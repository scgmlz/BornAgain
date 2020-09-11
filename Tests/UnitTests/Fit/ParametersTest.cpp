#include "Fit/Kernel/Parameters.h"
#include "Tests/GTestWrapper/google_test.h"
#include <string>

class ParametersTest : public ::testing::Test
{
};

TEST_F(ParametersTest, defaultConstructor)
{
    Fit::Parameters pars;
    EXPECT_EQ(pars.size(), 0u);
    EXPECT_TRUE(pars.values().empty());
    EXPECT_TRUE(pars.errors().empty());
}

TEST_F(ParametersTest, addParameter)
{
    Fit::Parameters pars;

    Fit::Parameter par0("par0", 2.0, AttLimits::limitless(), 0.2);
    Fit::Parameter par1("par1", 3.0, AttLimits::limitless(), 0.2);
    pars.add(par0);
    pars.add(par1);

    EXPECT_EQ(pars.size(), 2u);

    std::vector<double> expected_values = {2.0, 3.0};
    std::vector<double> expected_errors = {0.0, 0.0};
    EXPECT_EQ(pars.values(), expected_values);
    EXPECT_EQ(pars.errors(), expected_errors);

    // attempt to add parameter with same name should lead to exception
    Fit::Parameter par2("par1", 3.0, AttLimits::limitless(), 0.2);
    EXPECT_THROW(pars.add(par2), std::runtime_error);

    // access to parameters by name
    EXPECT_EQ(pars["par0"].name(), "par0");
    // access to non-existing parameters
    EXPECT_THROW(pars["non-existing"], std::runtime_error);

    // access to parameters by index
    EXPECT_EQ(pars[0].name(), "par0");
    EXPECT_THROW(pars[2], std::runtime_error);
}

TEST_F(ParametersTest, setters)
{
    Fit::Parameters pars;
    pars.add(Fit::Parameter("par0", 2.0, AttLimits::limitless(), 0.2));
    pars.add(Fit::Parameter("par1", 3.0, AttLimits::limitless(), 0.2));

    std::vector<double> expected_values = {42.0, 43.0};
    std::vector<double> expected_errors = {0.1, 0.2};
    pars.setValues(expected_values);
    pars.setErrors(expected_errors);
    EXPECT_EQ(pars.values(), expected_values);
    EXPECT_EQ(pars.errors(), expected_errors);

    // wrong size vector
    std::vector<double> more_values = {42.0, 43.0, 44.0};
    EXPECT_THROW(pars.setValues(more_values), std::runtime_error);
}

TEST_F(ParametersTest, freeParameterCount)
{
    Fit::Parameters pars;
    EXPECT_EQ(pars.freeParameterCount(), 0u);

    pars.add(Fit::Parameter("par0", 2.0, AttLimits::fixed(), 0.2));
    pars.add(Fit::Parameter("par1", 3.0, AttLimits::limitless(), 0.2));

    EXPECT_EQ(pars.freeParameterCount(), 1u);
}
