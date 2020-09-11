#include "Core/Parametrization/DistributionHandler.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/IParameterized.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Tests/GTestWrapper/google_test.h"
#include <cmath>

class DistributionHandlerTest : public ::testing::Test
{
protected:
    DistributionHandlerTest() : m_value(99.0) {}
    double m_value;
};

TEST_F(DistributionHandlerTest, DistributionHandlerConstructor)
{
    DistributionHandler handler;
    DistributionGate distribution(1.0, 2.0);
    std::string paraName = "value";

    EXPECT_EQ(size_t(1), handler.getTotalNumberOfSamples());

    ParameterDistribution par_distr(paraName, distribution, 2, 1.0);
    handler.addParameterDistribution(par_distr);

    EXPECT_EQ(size_t(2), handler.getTotalNumberOfSamples());

    const DistributionHandler::Distributions_t& distr = handler.getDistributions();
    ParameterDistribution distribution1 = distr[0];
    EXPECT_EQ(distribution1.getNbrSamples(), size_t(2));
    EXPECT_EQ(distribution1.getSigmaFactor(), 1.0);
}
