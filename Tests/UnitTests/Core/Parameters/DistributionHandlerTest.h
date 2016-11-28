#ifndef DISTRIBUTIONHANDLERTEST_H
#define DISTRIBUTIONHANDLERTEST_H

#include "IParameterized.h"
#include "DistributionHandler.h"
#include "Distributions.h"
#include "ParameterPool.h"
#include <cmath>

class DistributionHandlerTest : public ::testing::Test
{
protected:
    DistributionHandlerTest() : m_value(99.0) {}
    virtual ~DistributionHandlerTest(){}
    double m_value;
};

TEST_F(DistributionHandlerTest, DistributionHandlerConstructor)
{
    DistributionHandler handler;
    DistributionGate distribution(1.0, 2.0);
    std::string paraName = "value";
    EXPECT_EQ(size_t(1), handler.getTotalNumberOfSamples());
    handler.addParameterDistribution(paraName, distribution, 2, 1.0);
    EXPECT_EQ(size_t(2), handler.getTotalNumberOfSamples());
    EXPECT_EQ("DistributionHandler",handler.getName());

    const DistributionHandler::Distributions_t &distr = handler.getDistributions();
    ParameterDistribution distribution1 = distr[0];
    EXPECT_EQ(distribution1.getName(), "ParameterDistribution");
    EXPECT_EQ(distribution1.getNbrSamples(), size_t(2));
    EXPECT_EQ(distribution1.getSigmaFactor(), 1.0);

    /* TEMPORARILY DISABLED getParameterPool() 
    ParameterPool* parameterPool = distribution1.getParameterPool();
    parameterPool->registerParameter("value",&m_value);
    handler.setParameterValues(parameterPool, 0);
    EXPECT_EQ(m_value, 1.0);
    handler.setParameterValues(parameterPool, 1);
    EXPECT_EQ(m_value, 2.0);

    delete parameterPool;
    */
}


#endif // DISTRIBUTIONHANDLERTEST_H
