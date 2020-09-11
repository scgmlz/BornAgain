// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/IDistribution1DSampler.cpp
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Correlations/IDistribution1DSampler.h"
#include <random>

IDistribution1DSampler::~IDistribution1DSampler() = default;

double Distribution1DCauchySampler::randomSample() const
{
    // BornAgain Cauchy Distribution = std library Exponential distribution
    std::random_device rd;  // random device class instance
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::exponential_distribution<double> expDist(m_lambda);
    double value = expDist(gen);

    std::bernoulli_distribution bernoulliDist(0.5);
    bool sign = bernoulliDist(gen);

    if (sign == true)
        return value;
    else
        return -value;
}

double Distribution1DGaussSampler::randomSample() const
{
    // BornAgain Gauss Distribution = std library Normal distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> normalDist(m_mean, m_stddev);

    return normalDist(gen);
}

double Distribution1DGateSampler::randomSample() const
{
    // BornAgain Gate Distribution = std library Uniform distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> uniformDist(m_a, m_b);

    return uniformDist(gen);
}

double Distribution1DTriangleSampler::randomSample() const
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // generate a cdf value between 0 and 1
    std::uniform_real_distribution<> uniformDist(0.0, 1.0);
    double cdf_value = uniformDist(gen);

    // solve for x by inverting the cdf of Triangle Distribution
    if (cdf_value <= 0.5)
        return (-m_omega + m_omega * std::sqrt(2 * cdf_value));
    else
        return (m_omega - m_omega * std::sqrt(2 * (1 - cdf_value)));
}

double Distribution1DCosineSampler::randomSample() const
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // generate a cdf value between 0 and 1
    std::uniform_real_distribution<> uniformDist(0.0, 1.0);
    double cdf_value = uniformDist(gen);

    // solve for x from the cdf of Cosine Distribution using Newton-Raphson method
    double func = 0.0, funcDeriv = 0.0, x = 0.0;

    // initial guess for x
    if (cdf_value <= 0.5)
        x = -m_omega / 2;
    else
        x = m_omega / 2;

    bool convergedSoln = false;
    while (!convergedSoln) {
        func = x + m_omega / M_PI * std::sin(M_PI * x / m_omega) + m_omega * (1 - 2 * cdf_value);
        funcDeriv = 1 + std::cos(M_PI * x / m_omega);

        x = x - func / funcDeriv;

        if (std::abs(func / funcDeriv) < 0.001)
            convergedSoln = true;
    }

    return x;
}
