#ifndef REALPARAMETERWRAPPERTEST_H
#define REALPARAMETERWRAPPERTEST_H

#include "IParameterized.h"
#include "RealParameter.h"
#include <stdexcept>

class RealParameterTest : public ::testing::Test
{
 protected:
    RealParameterTest() {}
    virtual ~RealParameterTest() {}
};

TEST_F(RealParameterTest, ParameterAccess)
{
    class ParametrizedObject : public IParameterized
    {
    public:
        ParametrizedObject()
            : m_par1(17), m_changed(false)
        {
            registerParameter("par1", &m_par1);
        }
        virtual void onChange() final { m_changed = true; }
        double m_par1;
        bool m_changed;
    };
    ParametrizedObject obj1;

    EXPECT_EQ( obj1.m_par1, 17. );
    RealParameter* par11 = obj1.getParameter("par1");
    EXPECT_EQ( obj1.m_par1, par11->getValue() );

    RealParameter* par12 = par11;
    EXPECT_EQ( obj1.m_par1, par12->getValue() );

    RealParameter* par13 = obj1.getParameterPool()->getParameter("par1");
    EXPECT_EQ( obj1.m_par1, par13->getValue() );

    obj1.m_par1 = 2;
    EXPECT_EQ( par11->getValue(), 2. );
    EXPECT_EQ( par12->getValue(), 2. );
    EXPECT_EQ( par11->getValue(), 2. );

    EXPECT_FALSE( obj1.m_changed );
    par11->setValue( 3.14 );
    EXPECT_EQ( par11->getValue(), 3.14 );
    EXPECT_EQ( par12->getValue(), par11->getValue() );
    EXPECT_TRUE( obj1.m_changed );

    std::vector<RealParameter*> parameters;
    parameters.push_back(par11);
    parameters.push_back(par12);
    parameters[0]->setValue(3.0);
    EXPECT_EQ( obj1.m_par1, 3. );
    EXPECT_EQ( parameters[1]->getValue(), 3. );
}

/* incompatible with new handling of limits

TEST_F(RealParameterTest, LimitedParameter)
{
    class ParametrizedObject : public IParameterized
    {
    public:
        ParametrizedObject(double p, const Limits& lim)
            : m_par(p), m_changed(false)
        {
            registerParameter("par", &m_par, lim);
        }
        virtual void onChange() final { m_changed = true; }
        double m_par;
        bool m_changed;
    };

    EXPECT_THROW(ParametrizedObject(7., Limits::limited(10., 20.)), std::runtime_error);
    EXPECT_THROW(ParametrizedObject(1., Limits::lowerLimited(2.0)), std::runtime_error);
    EXPECT_THROW(ParametrizedObject(1., Limits::upperLimited(0.0)), std::runtime_error);

    ParametrizedObject obj1(15., Limits::limited(10, 20));
    EXPECT_EQ(obj1.m_par, 15.);

    RealParameter* par1 = obj1.getParameterPool()->getParameter("par");
    par1->setValue(16.0);
    EXPECT_EQ(obj1.m_par, 16.);
    EXPECT_THROW(par1->setValue(21.0), std::runtime_error);
    EXPECT_EQ(obj1.m_par, 16.);

    RealParameter* par2(par1);
    EXPECT_TRUE(par1->getLimits() == par2->getLimits());
    EXPECT_TRUE(*par1 == *par2);

    EXPECT_THROW(par2->setValue(21.0), std::runtime_error);
    EXPECT_EQ(par2->getValue(), 16.);

    par1->setValue(11.0);
    EXPECT_EQ(par1->getValue(), 11.);
}
*/

#endif // REALPARAMETERWRAPPERTEST_H
