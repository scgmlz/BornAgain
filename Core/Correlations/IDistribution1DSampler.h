// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/IDistribution1DSampler.h
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_CORRELATIONS_IDISTRIBUTION1DSAMPLER_H
#define BORNAGAIN_CORE_CORRELATIONS_IDISTRIBUTION1DSAMPLER_H

class IDistribution1DSampler
{
public:
    IDistribution1DSampler() {}
    virtual ~IDistribution1DSampler();

    virtual double randomSample() const = 0;
};

class Distribution1DCauchySampler : public IDistribution1DSampler
{
public:
    Distribution1DCauchySampler(double lambda) : m_lambda(lambda) {}
    double randomSample() const final;

private:
    double m_lambda;
};

class Distribution1DGaussSampler : public IDistribution1DSampler
{
public:
    Distribution1DGaussSampler(double mean, double stddev) : m_mean(mean), m_stddev(stddev) {}
    double randomSample() const final;

private:
    double m_mean, m_stddev;
};

class Distribution1DGateSampler : public IDistribution1DSampler
{
public:
    Distribution1DGateSampler(double a, double b) : m_a(a), m_b(b) {}
    double randomSample() const final;

private:
    double m_a, m_b; // the left and right limits of the Gate (Uniform) distribution
};

class Distribution1DTriangleSampler : public IDistribution1DSampler
{
public:
    Distribution1DTriangleSampler(double omega) : m_omega(omega) {}
    double randomSample() const final;

private:
    double m_omega; // half the base of the symmetrical Triangle distribution
};

class Distribution1DCosineSampler : public IDistribution1DSampler
{
public:
    Distribution1DCosineSampler(double omega) : m_omega(omega) {}
    double randomSample() const final;

private:
    double m_omega;
};

#endif // BORNAGAIN_CORE_CORRELATIONS_IDISTRIBUTION1DSAMPLER_H
