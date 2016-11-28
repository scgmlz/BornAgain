#ifndef DISTRIBUTIONSTEST_H
#define DISTRIBUTIONSTEST_H

#include "MathConstants.h"
#include "BornAgainNamespace.h"
#include "Distributions.h"
#include "Exceptions.h"
#include "RealParameter.h"
#include "ParameterSample.h"
#include <cmath>
#include <memory>

class DistributionsTest : public ::testing::Test
{
protected:
   DistributionsTest() {}
};

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionGateDefaultConstructor)
{
    std::unique_ptr<DistributionGate> P_distr_gate { new DistributionGate() };
    EXPECT_EQ(0.5, P_distr_gate->getMean());
    EXPECT_EQ(0.0, P_distr_gate->getMin());
    EXPECT_EQ(1.0, P_distr_gate->getMax());
    EXPECT_EQ(1.0, P_distr_gate->probabilityDensity(1.0));
    EXPECT_EQ(0, P_distr_gate->probabilityDensity(3.0));
    EXPECT_EQ(BornAgain::DistributionGateType, P_distr_gate->getName());

    std::vector<double> list1 = P_distr_gate->equidistantPoints(1, 0.0);
    EXPECT_EQ(list1.size(), size_t(1));
    EXPECT_EQ(P_distr_gate->getMean(), list1[0]);

    std::vector<double> list2 = P_distr_gate->equidistantPoints(2, 0.0);
    EXPECT_EQ(list2.size(), size_t(2));
    EXPECT_EQ(0, list2[0]);
    EXPECT_EQ(1, list2[1]);
}

TEST_F(DistributionsTest, DistributionGateConstructor)
{
    // Throw error when m_min > m_max:
    EXPECT_THROW(DistributionGate(1.1, 1.0), Exceptions::ClassInitializationException);

    // When m_min == m_max, only one sample is generated (the mean):
    DistributionGate distr1(1.0, 1.0);
    std::vector<double> list1 = distr1.equidistantPoints(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with m_min < m_max:
    DistributionGate distr2(1.0, 2.0);
    EXPECT_EQ(1.5, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getMin());
    EXPECT_EQ(2.0, distr2.getMax());
    EXPECT_EQ(1.0, distr2.probabilityDensity(1));
    EXPECT_EQ(0, distr2.probabilityDensity(3));
    EXPECT_EQ(BornAgain::DistributionGateType, distr2.getName());

    std::vector<double> list2 = distr2.equidistantPoints(1, 0.0);
    EXPECT_EQ(list2.size(), size_t(1));
    EXPECT_EQ(distr2.getMean(), list2[0]);

    list2 = distr2.equidistantPoints(2, 0.0);
    EXPECT_EQ(list2.size(), size_t(2));
    EXPECT_EQ(1.0, list2[0]);
    EXPECT_EQ(2.0, list2[1]);

    std::vector<ParameterSample> samples = distr2.equidistantSamples(3);
    EXPECT_EQ(samples.size(), size_t(3));
    EXPECT_EQ(samples[0].value, 1.0);
    EXPECT_EQ(samples[0].weight, 1./3.);
    EXPECT_EQ(samples[1].value, 1.5);
    EXPECT_EQ(samples[1].weight, 1./3.);
    EXPECT_EQ(samples[2].value, 2.0);
    EXPECT_EQ(samples[2].weight, 1./3.);
}

TEST_F(DistributionsTest, DistributionGateParameters)
{
    DistributionGate gate(2.0, 3.0);
    EXPECT_EQ(gate.getMin(), gate.getParameter(BornAgain::Minimum)->getValue());
    EXPECT_EQ(gate.getMax(), gate.getParameter(BornAgain::Maximum)->getValue());
}

TEST_F(DistributionsTest, DistributionGateClone)
{
    DistributionGate gate(2.0, 3.0);
    DistributionGate *clone = gate.clone();
    EXPECT_EQ(gate.getName(), clone->getName());
    EXPECT_EQ(gate.getMean(), clone->getMean());
    EXPECT_EQ(gate.getMin(), clone->getMin());
    EXPECT_EQ(gate.getMax(), clone->getMax());
    delete clone;
}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionLorentzDefaultConstructor)
{
    std::unique_ptr<DistributionLorentz> P_distr_lorentz { new DistributionLorentz() };
    EXPECT_EQ(0.0, P_distr_lorentz->getMean());
    EXPECT_EQ(1.0, P_distr_lorentz->getHWHM());
    EXPECT_EQ(BornAgain::DistributionLorentzType, P_distr_lorentz->getName());
    EXPECT_EQ(1/(M_TWOPI), P_distr_lorentz->probabilityDensity(1.0));

    std::vector<double> list1 = P_distr_lorentz->equidistantPoints(1, 0.0);
    EXPECT_EQ(P_distr_lorentz->getMean(), list1[0]);

    std::vector<double> list2 = P_distr_lorentz->equidistantPoints(2, 0.0);
    EXPECT_EQ(-2, list2[0]);
    EXPECT_EQ(2, list2[1]);
}

TEST_F(DistributionsTest, DistributionLorentzConstructor)
{
    // When HWHM == 0.0, only one sample is generated (the mean):
    DistributionLorentz distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.equidistantPoints(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with HWHM > 0.0:
    DistributionLorentz distr2(1.0, 1.0);
    EXPECT_EQ(1.0, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getHWHM());
    EXPECT_EQ(BornAgain::DistributionLorentzType, distr2.getName());
    EXPECT_EQ(1.0/M_PI, distr2.probabilityDensity(1.0));

    std::vector<double> list2 = distr2.equidistantPoints(1, 0.0);
    EXPECT_EQ(distr2.getMean(), list2[0]);

    std::vector<double> list3 = distr2.equidistantPoints(2, 0.0);
    EXPECT_EQ(-1, list3[0]);
    EXPECT_EQ(3, list3[1]);
}

TEST_F(DistributionsTest, DistributionLorentzParameters)
{
    DistributionLorentz lorentz(2.0, 3.0);
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ(lorentz.getMean(),
              lorentz.getParameterPool()->getParameter(BornAgain::Mean).getValue());
    EXPECT_EQ(lorentz.getHWHM(),
              lorentz.getParameterPool()->getParameter(BornAgain::HWHM).getValue());
    */
}

TEST_F(DistributionsTest, DistributionLorentzClone)
{
    std::unique_ptr<DistributionLorentz> P_distr_lorentz { new DistributionLorentz(1.0, 2.0) };
    std::unique_ptr<DistributionLorentz> P_clone { P_distr_lorentz->clone() };
    EXPECT_EQ(1.0, P_clone->getMean());
    EXPECT_EQ(2.0, P_clone->getHWHM());
    EXPECT_EQ(BornAgain::DistributionLorentzType, P_clone->getName());
}

TEST_F(DistributionsTest, DistributionLorentzSamples)
{
    DistributionLorentz distr(1.0, 0.1);

    const int nbr_samples(3);

    // with sigma factor
    const double sigma_factor(2.0);
    std::vector<ParameterSample> samples = distr.equidistantSamples(nbr_samples, sigma_factor);

    EXPECT_EQ(samples.size(), size_t(nbr_samples));
    EXPECT_EQ(samples[0].value, 1.0 - sigma_factor*0.1);
    EXPECT_EQ(samples[1].value, 1.0);
    EXPECT_EQ(samples[2].value, 1.0 + sigma_factor*0.1);
    double d1 = distr.probabilityDensity(samples[0].value);
    double d2 = distr.probabilityDensity(samples[1].value);
    double d3 = distr.probabilityDensity(samples[2].value);
    EXPECT_EQ(samples[0].weight, d1/(d1+d2+d3));
    EXPECT_EQ(samples[1].weight, d2/(d1+d2+d3));
    EXPECT_EQ(samples[2].weight, d3/(d1+d2+d3));

    // with Limits
    samples = distr.equidistantSamples(nbr_samples, sigma_factor, RealLimits::lowerLimited(0.99));
    EXPECT_EQ(samples[0].value, 0.99);
    EXPECT_EQ(samples[1].value, samples[0].value + (samples[2].value - samples[0].value)/2.0);
    EXPECT_EQ(samples[2].value, 1.0 + sigma_factor*0.1);

    // with xmin, xmax
    samples = distr.equidistantSamplesInRange(nbr_samples, 0.8, 1.2);
    EXPECT_EQ(samples[0].value, 0.8);
    EXPECT_EQ(samples[1].value, 1.0);
    EXPECT_EQ(samples[2].value, 1.2);
}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionGaussianDefaultConstructor)
{
    std::unique_ptr<DistributionGaussian> P_distr_gauss { new DistributionGaussian() };
    EXPECT_EQ(0.0, P_distr_gauss->getMean());
    EXPECT_EQ(1.0, P_distr_gauss->getStdDev());
    EXPECT_EQ(std::exp(-1.0/2.0)/std::sqrt(M_TWOPI), P_distr_gauss->probabilityDensity(1.0));
    EXPECT_EQ(BornAgain::DistributionGaussianType, P_distr_gauss->getName());

    std::vector<double> list1 = P_distr_gauss->equidistantPoints(1, 0.0);
    EXPECT_EQ(P_distr_gauss->getMean(), list1[0]);

    std::vector<double> list2 = P_distr_gauss->equidistantPoints(2, 0.0);
    EXPECT_EQ(-2, list2[0]);
    EXPECT_EQ(2, list2[1]);
}

TEST_F(DistributionsTest, DistributionGaussianConstructor)
{
    // When std_dev == 0.0, only one sample is generated (the mean):
    DistributionGaussian distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.equidistantPoints(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with std_dev > 0.0:
    DistributionGaussian distr2(1.0, 1.0);
    EXPECT_EQ(1.0, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getStdDev());
    EXPECT_EQ(1/std::sqrt(M_TWOPI), distr2.probabilityDensity(1.0));
    EXPECT_EQ(BornAgain::DistributionGaussianType, distr2.getName());

    std::vector<double> list2 = distr2.equidistantPoints(1, 0.0);
    EXPECT_EQ(distr2.getMean(), list2[0]);

    std::vector<double> list3 = distr2.equidistantPoints(2, 0.0);
    EXPECT_EQ(-1, list3[0]);
    EXPECT_EQ(3, list3[1]);
}

TEST_F(DistributionsTest, DistributionGaussianParameters)
{
    DistributionGaussian gaussian(2.0, 3.0);
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ(gaussian.getMean(),
              gaussian.getParameterPool()->getParameter(BornAgain::Mean).getValue());
    EXPECT_EQ(gaussian.getStdDev(),
              gaussian.getParameterPool()->getParameter(BornAgain::StdDeviation).getValue());
    */
}

TEST_F(DistributionsTest, DistributionGaussianClone)
{
    std::unique_ptr<DistributionGaussian> P_distr_gauss { new DistributionGaussian(1.0, 1.0) };
    std::unique_ptr<DistributionGaussian> P_clone { P_distr_gauss->clone() };
    EXPECT_EQ(1.0, P_clone->getMean());
    EXPECT_EQ(1.0, P_clone->getStdDev());
    EXPECT_EQ(1/std::sqrt(M_TWOPI), P_clone->probabilityDensity(1.0));
    EXPECT_EQ(BornAgain::DistributionGaussianType, P_clone->getName());

    std::vector<double> list1 = P_clone->equidistantPoints(1, 0.0);
    EXPECT_EQ(P_distr_gauss->getMean(), list1[0]);

    std::vector<double> list2 = P_clone->equidistantPoints(2, 0.0);
    EXPECT_EQ(-1, list2[0]);
    EXPECT_EQ(3, list2[1]);
}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionLogNormalConstructorWithOneParameter)
{
    // When scale_par == 0.0, only one sample is generated (the mean):
    DistributionLogNormal distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.equidistantPoints(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with scale_par > 0.0:
    DistributionLogNormal distr2(1.0);
    EXPECT_EQ(1.0, distr2.getMedian());
    EXPECT_EQ(1.0, distr2.getScalePar());
    EXPECT_EQ(std::exp(0.5), distr2.getMean());
    EXPECT_EQ(1.0/std::sqrt(M_TWOPI), distr2.probabilityDensity(1.0));
    EXPECT_EQ(BornAgain::DistributionLogNormalType, distr2.getName());

    std::vector<double> list2 = distr2.equidistantPoints(1, 0.0);
    EXPECT_EQ(distr2.getMedian(), list2[0]);

    std::vector<double> list3 = distr2.equidistantPoints(2, 0.0);
    EXPECT_EQ(std::exp(-2), list3[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list3[1]);
}

TEST_F(DistributionsTest, DistributionLogNormalConstructorWithTwoParameter)
{
    std::unique_ptr<DistributionLogNormal> P_distr_lognormal { new DistributionLogNormal(1.0,1.0) };
    EXPECT_EQ(1.0, P_distr_lognormal->getMedian());
    EXPECT_EQ(1.0, P_distr_lognormal->getScalePar());
    EXPECT_EQ(std::exp(0.5), P_distr_lognormal->getMean());
    EXPECT_EQ(1.0/std::sqrt(M_TWOPI), P_distr_lognormal->probabilityDensity(1.0));
    EXPECT_EQ(BornAgain::DistributionLogNormalType, P_distr_lognormal->getName());

    std::vector<double> list1 = P_distr_lognormal->equidistantPoints(1, 0.0);
    EXPECT_EQ(P_distr_lognormal->getMedian(), list1[0]);

    std::vector<double> list2 = P_distr_lognormal->equidistantPoints(2, 0.0);
    EXPECT_EQ(std::exp(-2), list2[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list2[1]);
}

TEST_F(DistributionsTest, DistributionLogNormalParameters)
{
    DistributionLogNormal logNormal(2.0, 3.0);
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ(logNormal.getMedian(),
              logNormal.getParameterPool()->getParameter(BornAgain::Median).getValue());
    EXPECT_EQ(logNormal.getScalePar(),
              logNormal.getParameterPool()->getParameter(BornAgain::ScaleParameter).getValue());
    */
}

TEST_F(DistributionsTest, DistributionLogNormalClone)
{
    std::unique_ptr<DistributionLogNormal> P_distr_lognormal { new DistributionLogNormal(1.0, 1.0) };
    std::unique_ptr<DistributionLogNormal> P_clone { P_distr_lognormal->clone() };
    EXPECT_EQ(1.0, P_distr_lognormal->getMedian());
    EXPECT_EQ(1.0, P_distr_lognormal->getScalePar());
    EXPECT_EQ(std::exp(0.5), P_distr_lognormal->getMean());
    EXPECT_EQ(1/std::sqrt(M_TWOPI), P_distr_lognormal->probabilityDensity(1.0));
    EXPECT_EQ(BornAgain::DistributionLogNormalType, P_distr_lognormal->getName());

    std::vector<double> list1 = P_distr_lognormal->equidistantPoints(1, 0.0);
    EXPECT_EQ(P_distr_lognormal->getMedian(), list1[0]);

    std::vector<double> list2 = P_distr_lognormal->equidistantPoints(2,0.0);
    EXPECT_EQ(std::exp(-2), list2[0]);
    EXPECT_EQ(std::exp(-2) + std::exp(2) - std::exp(-2), list2[1]);
}

// -------------------------------------------------------------------------- //

TEST_F(DistributionsTest, DistributionCosineDefaultConstructor)
{
    std::unique_ptr<DistributionCosine> P_distr_cosine { new DistributionCosine() };
    EXPECT_EQ(0.0, P_distr_cosine->getMean());
    EXPECT_EQ(1.0, P_distr_cosine->getSigma());
    EXPECT_DOUBLE_EQ((1.0+std::cos(1.0))/(M_TWOPI), P_distr_cosine->probabilityDensity(1.0));
    EXPECT_EQ(0, P_distr_cosine->probabilityDensity(100.0));
    EXPECT_EQ(BornAgain::DistributionCosineType, P_distr_cosine->getName());

    std::vector<double> list1 = P_distr_cosine->equidistantPoints(1, 0.0);
    EXPECT_EQ(P_distr_cosine->getMean(), list1[0]);

    std::vector<double> list2 = P_distr_cosine->equidistantPoints(2, 0.0);
    EXPECT_EQ(-M_PI, list2[0]);
    EXPECT_EQ(M_PI, list2[1]);
}

TEST_F(DistributionsTest, DistributionCosineConstructor)
{
    // When sigma == 0.0, only one sample is generated (the mean):
    DistributionCosine distr1(1.0, 0.0);
    std::vector<double> list1 = distr1.equidistantPoints(5, 0.0);
    EXPECT_EQ(size_t(1), list1.size());
    EXPECT_EQ(1.0, list1[0]);

    // Test distribution with sigma > 0.0:
    DistributionCosine distr2(1.0,1.0);
    EXPECT_EQ(1.0, distr2.getMean());
    EXPECT_EQ(1.0, distr2.getSigma());
    EXPECT_EQ(2.0/(M_TWOPI), distr2.probabilityDensity(1.0));
    EXPECT_EQ(0, distr2.probabilityDensity(100.0));
    EXPECT_EQ(BornAgain::DistributionCosineType, distr2.getName());

    std::vector<double> list2 = distr2.equidistantPoints(1, 0.0);
    EXPECT_EQ(distr2.getMean(), list2[0]);

    std::vector<double> list3 = distr2.equidistantPoints(2, 0.0);
    EXPECT_EQ(1-M_PI, list3[0]);
    EXPECT_EQ(1+M_PI, list3[1]);
}

TEST_F(DistributionsTest, DistributionCosineParameters)
{
    DistributionCosine cosine(2.0, 3.0);
    /* TEMPORARILY DISABLED getParameterPool()
    EXPECT_EQ(cosine.getMean(), cosine.getParameterPool()->getParameter(BornAgain::Mean).getValue());
    EXPECT_EQ(cosine.getSigma(), cosine.getParameterPool()->getParameter(BornAgain::Sigma).getValue());
    */
}

TEST_F(DistributionsTest, DistributionCosineClone)
{
    std::unique_ptr<DistributionCosine> P_distr_cosine { new DistributionCosine(1.0,1.0) };
    std::unique_ptr<DistributionCosine> P_clone { P_distr_cosine->clone() };
    EXPECT_EQ(1.0, P_clone->getMean());
    EXPECT_EQ(1.0, P_clone->getSigma());
    EXPECT_EQ(2.0/(M_TWOPI), P_clone->probabilityDensity(1.0));
    EXPECT_EQ(0, P_distr_cosine->probabilityDensity(100.0));
    EXPECT_EQ(BornAgain::DistributionCosineType, P_clone->getName());

    std::vector<double> list1 = P_clone->equidistantPoints(1, 0.0);
    EXPECT_EQ(P_clone->getMean(), list1[0]);

    std::vector<double> list2 = P_clone->equidistantPoints(2, 0.0);
    EXPECT_EQ(1-M_PI, list2[0]);
    EXPECT_EQ(1+M_PI, list2[1]);
}

#endif // DISTRIBUTIONSTEST_H
