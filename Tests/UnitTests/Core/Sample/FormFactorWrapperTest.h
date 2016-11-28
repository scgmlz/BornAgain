#ifndef FORMFACTORWRAPPERTEST_H
#define FORMFACTORWRAPPERTEST_H

#include "FormFactorWrapper.h"
#include "FormFactorTrivial.h"
#include "Exceptions.h"

class FormFactorWrapperTest : public ::testing::Test
{
protected:
    FormFactorWrapperTest() {}
    virtual ~FormFactorWrapperTest() {}
};

TEST_F(FormFactorWrapperTest, RelAbundance)
{
    const double epsilon=1e-12;
    auto p_ff = new FormFactorTrivial();
    FormFactorWrapper ffw(p_ff, 1.0);
    EXPECT_EQ(1.0, ffw.relativeAbundance());
    ffw.scaleRelativeAbundance(2.0);
    EXPECT_NEAR(0.5, ffw.relativeAbundance(), epsilon);
    EXPECT_THROW(ffw.scaleRelativeAbundance(0.0), Exceptions::LogicErrorException);
}

TEST_F(FormFactorWrapperTest, FormFactor)
{
    auto p_ff = new FormFactorTrivial();
    FormFactorWrapper ffw(p_ff, 1.0);
    EXPECT_EQ(0.0, ffw.radialExtension());
    ffw.scaleRelativeAbundance(2.0);
    EXPECT_EQ(0.0, ffw.radialExtension());
}

#endif // FORMFACTORWRAPPERTEST_H
