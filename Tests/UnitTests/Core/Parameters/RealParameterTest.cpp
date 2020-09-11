#include "Core/Parametrization/RealParameter.h"
#include "Core/Parametrization/IParameterized.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>
#include <stdexcept>

class RealParameterTest : public ::testing::Test
{
};

TEST_F(RealParameterTest, simpleConstructor)
{
    double value(42.0);
    std::unique_ptr<RealParameter> par(new RealParameter("name", &value));
    EXPECT_EQ(par->value(), value);
    EXPECT_EQ(par->limits(), RealLimits::limitless());
    EXPECT_EQ(par->unit(), std::string());
    EXPECT_EQ(&value, &par->getData());
    EXPECT_FALSE(par->isNull());
}

TEST_F(RealParameterTest, dataComparison)
{
    double value(1.0);
    RealParameter par1("name1", &value);
    RealParameter par2("name2", &value);
    EXPECT_EQ(&par1.getData(), &value);
    EXPECT_EQ(&par1.getData(), &par2.getData());
    EXPECT_TRUE(par1.hasSameData(par2));

    double another_value(42.0);
    RealParameter par3("name3", &another_value);
    EXPECT_FALSE(par3.hasSameData(par1));
}

TEST_F(RealParameterTest, extendedConstructor)
{
    double value(42.0);
    bool is_changed(false);
    RealParameter par(
        "name", &value, "parent_name", [&]() { is_changed = true; }, RealLimits::limited(1.0, 43.0),
        Attributes::free());
    EXPECT_EQ(par.value(), value);
    EXPECT_EQ(par.limits(), RealLimits::limited(1.0, 43.0));

    // checks
    EXPECT_FALSE(is_changed);
    const double new_value(41.0);
    par.setValue(new_value);
    EXPECT_TRUE(is_changed);
    EXPECT_EQ(par.value(), new_value);
}

TEST_F(RealParameterTest, clone)
{
    double value(42.0);
    bool is_changed(false);
    std::unique_ptr<RealParameter> par(new RealParameter(
        "name", &value, "parent_name", [&]() { is_changed = true; }, RealLimits::limited(1.0, 43.0),
        Attributes::free()));

    // cloning and deleting original
    std::unique_ptr<RealParameter> clone(par->clone());
    par.reset();
    EXPECT_EQ(clone->value(), value);
    EXPECT_EQ(clone->limits(), RealLimits::limited(1.0, 43.0));

    // checks
    EXPECT_FALSE(is_changed);
    const double new_value(41.0);
    clone->setValue(new_value);
    EXPECT_TRUE(is_changed);
    EXPECT_EQ(clone->value(), new_value);
    EXPECT_EQ(value, new_value);
}
