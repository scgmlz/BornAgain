#ifndef PARAMETERDISTRIBUTIONTEST_H
#define PARAMETERDISTRIBUTIONTEST_H

#include "ParameterDistribution.h"
#include "Distributions.h"
#include "Exceptions.h"
#include "ParameterSample.h"
#include "IParameterized.h"
#include <cmath>

class ParameterDistributionTest : public ::testing::Test
{

protected:
   ParameterDistributionTest() {}
};

TEST_F(ParameterDistributionTest, ParameterDistributionConstructor)
{
    std::string name = "MainParameterName";
    DistributionGate distribution(1.0, 2.0);
    EXPECT_THROW(ParameterDistribution(name, distribution, 1, -1.0),
                 Exceptions::RuntimeErrorException);
    EXPECT_THROW(ParameterDistribution(name, distribution, 0),
                 Exceptions::RuntimeErrorException);

    // Sigma constructor
    ParameterDistribution pardistr(name, distribution, 1);
    EXPECT_EQ("ParameterDistribution", pardistr.getName());
    EXPECT_EQ(1.5, pardistr.getDistribution()->getMean());
    EXPECT_EQ("DistributionGate", pardistr.getDistribution()->getName());
    EXPECT_EQ(1.0, pardistr.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(name, pardistr.getMainParameterName());
    EXPECT_EQ(size_t(1), pardistr.getNbrSamples());
    EXPECT_EQ(0.0, pardistr.getSigmaFactor());
    EXPECT_EQ(RealLimits(), pardistr.getLimits());
    EXPECT_EQ(pardistr.getLinkedParameterNames().size(), size_t(0));
    EXPECT_EQ(1.0, pardistr.getMinValue());
    EXPECT_EQ(-1.0, pardistr.getMaxValue());

    ParameterDistribution pardistr2(name, distribution, 5, 2.0, RealLimits::limited(1.0, 2.0));
    EXPECT_EQ(size_t(5), pardistr2.getNbrSamples());
    EXPECT_EQ(2.0, pardistr2.getSigmaFactor());
    EXPECT_EQ(RealLimits::limited(1.0, 2.0), pardistr2.getLimits());

    // xmin, xmax constructor
    ParameterDistribution pardistr3(name, distribution, 5, 1.0, 2.0);
    EXPECT_EQ("ParameterDistribution", pardistr3.getName());
    EXPECT_EQ(1.5, pardistr3.getDistribution()->getMean());
    EXPECT_EQ("DistributionGate", pardistr3.getDistribution()->getName());
    EXPECT_EQ(1.0, pardistr3.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(name, pardistr3.getMainParameterName());
    EXPECT_EQ(size_t(5), pardistr3.getNbrSamples());
    EXPECT_EQ(0.0, pardistr3.getSigmaFactor());
    EXPECT_EQ(RealLimits(), pardistr3.getLimits());
    EXPECT_EQ(pardistr3.getLinkedParameterNames().size(), size_t(0));
}

TEST_F(ParameterDistributionTest, ParameterDistributionCopyConstructor)
{
    DistributionGate distribution(1.0, 2.0);
    std::string name = "MainParameterName";
    ParameterDistribution pardistr(name, distribution, 5, 2.0, RealLimits::limited(1.0, 2.0));
    pardistr.linkParameter("link1").linkParameter("link2");

    ParameterDistribution pcopy(pardistr);
    EXPECT_EQ(pardistr.getName(), pcopy.getName());
    EXPECT_EQ(1.5, pcopy.getDistribution()->getMean());
    EXPECT_EQ(pardistr.getDistribution()->getName(), pcopy.getDistribution()->getName());

    EXPECT_EQ(pardistr.getDistribution()->probabilityDensity(1), pcopy.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(pardistr.getMainParameterName(), pcopy.getMainParameterName());
    EXPECT_EQ(pardistr.getNbrSamples(), pcopy.getNbrSamples());
    EXPECT_EQ(pardistr.getSigmaFactor(), pcopy.getSigmaFactor());
    EXPECT_EQ(pardistr.getLimits(), pcopy.getLimits());
    EXPECT_EQ(pardistr.getLinkedParameterNames().size(), pcopy.getLinkedParameterNames().size());
    EXPECT_EQ("link1", pcopy.getLinkedParameterNames()[0]);
    EXPECT_EQ("link2", pcopy.getLinkedParameterNames()[1]);
    EXPECT_EQ(pardistr.getMinValue(), pcopy.getMinValue());
    EXPECT_EQ(pardistr.getMaxValue(), pcopy.getMaxValue());
}

TEST_F(ParameterDistributionTest, ParameterDistributionAssignment)
{
    DistributionGate distribution(1.0, 2.0);
    std::string name = "MainParameterName";
    ParameterDistribution pardistr(name, distribution, 5, 2.0, RealLimits::limited(1.0, 2.0));
    pardistr.linkParameter("link1").linkParameter("link2");

    ParameterDistribution pcopy = pardistr;
    EXPECT_EQ(pardistr.getName(), pcopy.getName());
    EXPECT_EQ(1.5, pcopy.getDistribution()->getMean());
    EXPECT_EQ(pardistr.getDistribution()->getName(), pcopy.getDistribution()->getName());

    EXPECT_EQ(pardistr.getDistribution()->probabilityDensity(1), pcopy.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(pardistr.getMainParameterName(), pcopy.getMainParameterName());
    EXPECT_EQ(pardistr.getNbrSamples(), pcopy.getNbrSamples());
    EXPECT_EQ(pardistr.getSigmaFactor(), pcopy.getSigmaFactor());
    EXPECT_EQ(pardistr.getLimits(), pcopy.getLimits());
    EXPECT_EQ(pardistr.getLinkedParameterNames().size(), pcopy.getLinkedParameterNames().size());
    EXPECT_EQ("link1", pcopy.getLinkedParameterNames()[0]);
    EXPECT_EQ("link2", pcopy.getLinkedParameterNames()[1]);
    EXPECT_EQ(pardistr.getMinValue(), pcopy.getMinValue());
    EXPECT_EQ(pardistr.getMaxValue(), pcopy.getMaxValue());
}

TEST_F(ParameterDistributionTest, GenerateSamples)
{
    const double mean(1.0);
    const double sigma(0.8);
    DistributionGaussian distribution(mean, sigma);

    std::string name = "MainParameterName";
    const int nbr_samples(3);
    const double sigma_factor(2.0);

    // without Limits
    ParameterDistribution pardistr(name, distribution, nbr_samples, sigma_factor);
    std::vector<ParameterSample> sample_values = pardistr.generateSamples();
    EXPECT_EQ(sample_values.size(), size_t(3));
    EXPECT_EQ(sample_values[0].value, mean-sigma_factor*sigma);
    EXPECT_EQ(sample_values[1].value, mean);
    EXPECT_EQ(sample_values[2].value, mean+sigma_factor*sigma);

    // with Limits
    ParameterDistribution pardistr2(name, distribution, nbr_samples, sigma_factor, RealLimits::lowerLimited(mean));
    sample_values = pardistr2.generateSamples();
    EXPECT_EQ(sample_values.size(), size_t(3));
    EXPECT_EQ(sample_values[0].value, mean);
    EXPECT_EQ(sample_values[1].value, mean+sigma_factor*sigma/2.0);
    EXPECT_EQ(sample_values[2].value, mean+sigma_factor*sigma);

    // with xmin, xmax defined
    double xmin(-1.0);
    double xmax(2.0);
    ParameterDistribution pardistr3(name, distribution, nbr_samples, xmin, xmax);
    sample_values = pardistr3.generateSamples();
    EXPECT_EQ(sample_values.size(), size_t(3));
    EXPECT_EQ(sample_values[0].value, xmin);
    EXPECT_EQ(sample_values[1].value, xmin + (xmax-xmin)/2.0);
    EXPECT_EQ(sample_values[2].value, xmax);
}


#endif // PARAMETERDISTRIBUTIONTEST_H
