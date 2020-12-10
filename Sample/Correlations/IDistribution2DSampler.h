//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Correlations/IDistribution2DSampler.h
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_CORRELATIONS_IDISTRIBUTION2DSAMPLER_H
#define BORNAGAIN_SAMPLE_CORRELATIONS_IDISTRIBUTION2DSAMPLER_H

#include <utility>

class IDistribution2DSampler {
public:
    IDistribution2DSampler() {}
    virtual ~IDistribution2DSampler();

    virtual std::pair<double, double> randomSample() const = 0;
};

class Distribution2DCauchySampler : public IDistribution2DSampler {
public:
    Distribution2DCauchySampler(double omega_x, double omega_y)
        : m_omega_x(omega_x), m_omega_y(omega_y) {}
    std::pair<double, double> randomSample() const final;

private:
    double m_omega_x, m_omega_y;
};

class Distribution2DGaussSampler : public IDistribution2DSampler {
public:
    Distribution2DGaussSampler(double omega_x, double omega_y)
        : m_omega_x(omega_x), m_omega_y(omega_y) {}
    std::pair<double, double> randomSample() const final;

private:
    double m_omega_x, m_omega_y;
};

class Distribution2DGateSampler : public IDistribution2DSampler {
public:
    Distribution2DGateSampler(double omega_x, double omega_y)
        : m_omega_x(omega_x), m_omega_y(omega_y) {}
    std::pair<double, double> randomSample() const final;

private:
    double m_omega_x, m_omega_y;
};

class Distribution2DConeSampler : public IDistribution2DSampler {
public:
    Distribution2DConeSampler(double omega_x, double omega_y)
        : m_omega_x(omega_x), m_omega_y(omega_y) {}
    std::pair<double, double> randomSample() const final;

private:
    double m_omega_x, m_omega_y;
};

#endif // BORNAGAIN_SAMPLE_CORRELATIONS_IDISTRIBUTION2DSAMPLER_H
#endif // USER_API
