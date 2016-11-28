#ifndef PARAMETERPOOLTEST_H
#define PARAMETERPOOLTEST_H

#include "ParameterPool.h"

/* TEMPORARILY DISABLED
class ParameterPoolTest : public ::testing::Test
{
 protected:
    ParameterPoolTest();
    virtual ~ParameterPoolTest(){}

    ParameterPool m_empty_pool;
    ParameterPool m_pool;
    double m_real_par1;
    double m_real_par2;
    double m_real_par3;
    double m_real_par4;
};


ParameterPoolTest::ParameterPoolTest()
    : m_real_par1(1.0), m_real_par2(2.0), m_real_par3(3.0), m_real_par4(4.0)
{
    m_pool.registerParameter("a_par1",&m_real_par1);
    m_pool.registerParameter("a_par2",&m_real_par2);
    ParameterPool::parameter_t poolpar(&m_real_par3);
    m_pool.addParameter("b_par3",poolpar);
}


TEST_F(ParameterPoolTest, InitialState)
{
    EXPECT_EQ( size_t(0), m_empty_pool.size() );
    ASSERT_THROW( m_empty_pool.getParameter("NotExistingName"), Exceptions::LogicErrorException );
}


TEST_F(ParameterPoolTest, registerParameters)
{
    EXPECT_EQ( size_t(3), m_pool.size() );
    EXPECT_EQ( double(1.0), m_pool.getParameter("a_par1").getValue());
    EXPECT_EQ( double(2.0), m_pool.getParameter("a_par2").getValue());
    EXPECT_EQ( double(3.0), m_pool.getParameter("b_par3").getValue());
    m_real_par3 = 3.1;
    EXPECT_EQ( double(3.1), m_pool.getParameter("b_par3").getValue());
    std::vector<ParameterPool::parameter_t > pars = m_pool.getMatchedParameters("*par*");
    EXPECT_EQ( size_t(3), pars.size() );
    pars = m_pool.getMatchedParameters("a_par*");
    EXPECT_EQ( size_t(2), pars.size() );

    ASSERT_THROW( m_pool.setParameterValue("NonExistingName", 3.2), Exceptions::LogicErrorException );
    m_pool.setParameterValue("b_par3", 3.2);
    EXPECT_EQ( double(3.2), m_pool.getParameter("b_par3").getValue());

    EXPECT_EQ( int(3), m_pool.setMatchedParametersValue("*par*",5.0));
    EXPECT_EQ( double(5.0), m_real_par1);
    EXPECT_EQ( double(5.0), m_real_par2);
    EXPECT_EQ( double(5.0), m_real_par3);
}


TEST_F(ParameterPoolTest, PoolClone)
{
    ParameterPool *clone = m_pool.clone();
    EXPECT_EQ( size_t(3), clone->size() );
    EXPECT_EQ( double(1.0), clone->getParameter("a_par1").getValue());
    EXPECT_EQ( double(2.0), clone->getParameter("a_par2").getValue());
    EXPECT_EQ( double(3.0), clone->getParameter("b_par3").getValue());
    delete clone;
}


TEST_F(ParameterPoolTest, CopyToExternalPool)
{
    m_real_par1 = 1.0;
    m_real_par2 = 2.0;
    m_real_par3 = 3.0;
    m_real_par4 = 4.0;
    ParameterPool external_pool;
    external_pool.registerParameter("par4",&m_real_par4);
    m_pool.copyToExternalPool("Another/",&external_pool);
//    std::cout << external_pool << std::endl;
    EXPECT_EQ( double(1.0), external_pool.getParameter("Another/a_par1").getValue());
    EXPECT_EQ( double(2.0), external_pool.getParameter("Another/a_par2").getValue());
    EXPECT_EQ( double(3.0), external_pool.getParameter("Another/b_par3").getValue());
    EXPECT_EQ( double(4.0), external_pool.getParameter("par4").getValue());
}


TEST_F(ParameterPoolTest, SetMatchedParametersValue)
{
    double x(1.0), y(2.0), z(3.0);
    ParameterPool pool;
    pool.registerParameter("xx_x", &x);
    pool.registerParameter("xx_y", &y);
    pool.registerParameter("xx_z", &z);
    EXPECT_THROW( pool.setMatchedParametersValue("zz*", 4.0), Exceptions::LogicErrorException );
    pool.setMatchedParametersValue("xx*", 4.0);
    EXPECT_EQ( double(4.0), pool.getParameter("xx_x").getValue());
    EXPECT_EQ( double(4.0), pool.getParameter("xx_y").getValue());
    EXPECT_EQ( double(4.0), pool.getParameter("xx_z").getValue());
}

TEST_F(ParameterPoolTest, LimitsOnParameterValue)
{
    double x(0.0);
    ParameterPool pool;

    EXPECT_THROW(pool.registerParameter("xx_x", &x, Limits::limited(1.0, 2.0)), Exceptions::OutOfBoundsException);

    pool.registerParameter("xx_x", &x, Limits::limited(-1.0, 1.0));

    EXPECT_TRUE(pool.setParameterValue("xx_x", 0.5));
    EXPECT_EQ(0.5, x);

    EXPECT_THROW(pool.setParameterValue("xx_x", 2.0), Exceptions::LogicErrorException);
    EXPECT_EQ(0.5, x);

    EXPECT_THROW(pool.setMatchedParametersValue("xx*", 2.0), Exceptions::LogicErrorException);
    EXPECT_EQ(0.5, x);
}

*/
#endif // PARAMETERPOOLTEST_H
