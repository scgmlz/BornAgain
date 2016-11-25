// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Distributions.cpp
//! @brief     Implements classes representing one-dimensional distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Distributions.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "ParameterSample.h"
#include <cmath>
#include <sstream>


// ************************************************************************** //
// class IDistribution1D
// ************************************************************************** //

//! Returns equidistant samples, using intrinsic parameters, weighted with probabilityDensity().

std::vector<ParameterSample> IDistribution1D::equidistantSamples(
    size_t nbr_samples, double sigma_factor, const RealLimits& limits) const
{
    if (nbr_samples == 0)
        throw Exceptions::OutOfBoundsException(
            "IDistribution1D::generateSamples: "
            "number of generated samples must be bigger than zero");
    if (isDelta())
        return { ParameterSample(getMean()) };
    return generateSamplesFromValues(equidistantPoints(nbr_samples, sigma_factor, limits));
}

//! Returns equidistant samples from xmin to xmax, weighted with probabilityDensity().

std::vector<ParameterSample>
IDistribution1D::equidistantSamplesInRange(size_t nbr_samples, double xmin, double xmax) const
{
    if (nbr_samples == 0)
        throw Exceptions::OutOfBoundsException(
            "IDistribution1D::generateSamples: "
            "number of generated samples must be bigger than zero");
    if (isDelta())
        return { ParameterSample(getMean()) };
    return generateSamplesFromValues(equidistantPointsInRange(nbr_samples, xmin, xmax));
}

//! Returns equidistant interpolation points from xmin to xmax.

std::vector<double>
IDistribution1D::equidistantPointsInRange(size_t nbr_samples, double xmin, double xmax) const
{
    if (nbr_samples < 2 || xmin == xmax)
        return { getMean() };
    std::vector<double> result(nbr_samples);
    for (size_t i = 0; i < nbr_samples; ++i)
        result[i] = xmin + i * (xmax - xmin) / (nbr_samples - 1.0);
    return result;
}

void IDistribution1D::SignalBadInitialization(std::string distribution_name)
{
    throw Exceptions::ClassInitializationException(
        distribution_name + ": not correctly initialized");
}

void IDistribution1D::adjustMinMaxForLimits(
    double& xmin, double& xmax, const RealLimits& limits) const
{
    if (limits.hasLowerLimit() && xmin < limits.getLowerLimit())
        xmin = limits.getLowerLimit();
    if (limits.hasUpperLimit() && xmax > limits.getUpperLimit())
        xmax = limits.getUpperLimit();
    if (xmin > xmax) {
        std::ostringstream ostr;
        ostr << "IDistribution1D::adjustMinMaxForLimits() -> Error. Can't' adjust ";
        ostr << "xmin:" << xmin << " xmax:" << xmax << " for given limits " << limits << std::endl;
        throw Exceptions::DomainErrorException(ostr.str());
    }
}

//! Returns weighted samples from given interpolation points and probabilityDensity().

std::vector<ParameterSample>
IDistribution1D::generateSamplesFromValues(const std::vector<double>& sample_values) const
{
    std::vector<ParameterSample> result;
    double norm_factor = 0.0;
    for (double value : sample_values) {
        double pdf = probabilityDensity(value);
        result.push_back(ParameterSample(value, pdf));
        norm_factor += pdf;
    }
    if (norm_factor <= 0.0)
        throw Exceptions::RuntimeErrorException("IDistribution1D::generateSamples: "
                                                "total probability must be bigger than zero");
    for (ParameterSample& sample : result)
        sample.weight /= norm_factor;
    return result;
}


// ************************************************************************** //
// class DistributionGate
// ************************************************************************** //

DistributionGate::DistributionGate(double min, double max) : m_min(min), m_max(max)
{
    setName(BornAgain::DistributionGateType);
    checkInitialization();
    init_parameters();
}

double DistributionGate::probabilityDensity(double x) const
{
    if (x < m_min || x > m_max)
        return 0.0;
    if (m_min == m_max)
        return 1.0;
    return 1.0 / (m_max - m_min);
}

std::vector<double>
DistributionGate::equidistantPoints(size_t nbr_samples, double, const RealLimits&) const
{
    return equidistantPointsInRange(nbr_samples, m_min, m_max);
}

void DistributionGate::init_parameters()
{
    registerParameter(BornAgain::Minimum, &m_min);
    registerParameter(BornAgain::Maximum, &m_max);
}

bool DistributionGate::isDelta() const { return m_max == m_min; }

bool DistributionGate::checkInitialization() const
{
    if (m_max < m_min) {
        SignalBadInitialization(BornAgain::DistributionGateType);
        return false;
    }
    return true;
}


// ************************************************************************** //
// class DistributionLorentz
// ************************************************************************** //

DistributionLorentz::DistributionLorentz(double mean, double hwhm) : m_mean(mean), m_hwhm(hwhm)
{
    setName(BornAgain::DistributionLorentzType);
    checkInitialization();
    init_parameters();
}

double DistributionLorentz::probabilityDensity(double x) const
{
    if (m_hwhm == 0.0)
        return x == m_mean ? 1.0 : 0.0;
    return m_hwhm / (m_hwhm * m_hwhm + (x - m_mean) * (x - m_mean)) / M_PI;
}

std::vector<double> DistributionLorentz::equidistantPoints(
    size_t nbr_samples, double sigma_factor, const RealLimits& limits) const
{
    if (sigma_factor <= 0.0)
        sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor * m_hwhm;
    double xmax = m_mean + sigma_factor * m_hwhm;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

void DistributionLorentz::init_parameters()
{
    registerParameter(BornAgain::Mean, &m_mean);
    registerParameter(BornAgain::HWHM, &m_hwhm);
}

bool DistributionLorentz::isDelta() const { return m_hwhm == 0.0; }

bool DistributionLorentz::checkInitialization() const
{
    if (m_hwhm < 0.0) {
        SignalBadInitialization(BornAgain::DistributionLorentzType);
        return false;
    }
    return true;
}


// ************************************************************************** //
// class DistributionGaussian
// ************************************************************************** //

DistributionGaussian::DistributionGaussian(double mean, double std_dev)
    : m_mean(mean), m_std_dev(std_dev)
{
    setName(BornAgain::DistributionGaussianType);
    checkInitialization();
    init_parameters();
}

double DistributionGaussian::probabilityDensity(double x) const
{
    if (m_std_dev == 0.0)
        return x == m_mean ? 1.0 : 0.0;
    double exponential = std::exp(-(x - m_mean) * (x - m_mean) / (2.0 * m_std_dev * m_std_dev));
    return exponential / m_std_dev / std::sqrt(M_TWOPI);
}

std::vector<double> DistributionGaussian::equidistantPoints(
    size_t nbr_samples, double sigma_factor, const RealLimits& limits) const
{
    if (sigma_factor <= 0.0)
        sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor * m_std_dev;
    double xmax = m_mean + sigma_factor * m_std_dev;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

void DistributionGaussian::init_parameters()
{
    registerParameter(BornAgain::Mean, &m_mean);
    registerParameter(BornAgain::StdDeviation, &m_std_dev);
}

bool DistributionGaussian::isDelta() const { return m_std_dev == 0.0; }

bool DistributionGaussian::checkInitialization() const
{
    if (m_std_dev < 0.0) {
        SignalBadInitialization(BornAgain::DistributionGaussianType);
        return false;
    }
    return true;
}


// ************************************************************************** //
// class DistributionLogNormal
// ************************************************************************** //

DistributionLogNormal::DistributionLogNormal(double median, double scale_param)
    : m_median(median), m_scale_param(scale_param)
{
    setName(BornAgain::DistributionLogNormalType);
    checkInitialization();
    init_parameters();
}

double DistributionLogNormal::probabilityDensity(double x) const
{
    if (m_scale_param == 0.0)
        return x == m_median ? 1.0 : 0.0;
    double t = std::log(x / m_median) / m_scale_param;
    return std::exp(-t * t / 2.0) / (x * m_scale_param * std::sqrt(M_TWOPI));
}

double DistributionLogNormal::getMean() const
{
    double exponent = m_scale_param * m_scale_param / 2.0;
    return m_median * std::exp(exponent);
}

std::vector<double> DistributionLogNormal::equidistantPoints(
    size_t nbr_samples, double sigma_factor, const RealLimits& limits) const
{
    if (nbr_samples < 2) {
        std::vector<double> result;
        result.push_back(m_median);
        return result;
    }
    if (sigma_factor <= 0.0)
        sigma_factor = 2.0;
    double xmin = m_median * std::exp(-sigma_factor * m_scale_param);
    double xmax = m_median * std::exp(sigma_factor * m_scale_param);
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

void DistributionLogNormal::init_parameters()
{
    registerParameter(BornAgain::Median, &m_median);
    registerParameter(BornAgain::ScaleParameter, &m_scale_param);
}

bool DistributionLogNormal::isDelta() const { return m_scale_param == 0.0; }

bool DistributionLogNormal::checkInitialization() const
{
    if (m_scale_param < 0.0 || m_median <= 0.0) {
        SignalBadInitialization(BornAgain::DistributionLogNormalType);
        return false;
    }
    return true;
}


// ************************************************************************** //
// class DistributionCosine
// ************************************************************************** //

DistributionCosine::DistributionCosine(double mean, double sigma) : m_mean(mean), m_sigma(sigma)
{
    setName(BornAgain::DistributionCosineType);
    checkInitialization();
    init_parameters();
}

double DistributionCosine::probabilityDensity(double x) const
{
    if (m_sigma == 0.0)
        return x == m_mean ? 1.0 : 0.0;
    if (std::abs(x - m_mean) > M_PI * m_sigma)
        return 0.0;
    return (1.0 + std::cos((x - m_mean) / m_sigma)) / (m_sigma * M_TWOPI);
}

std::vector<double> DistributionCosine::equidistantPoints(
    size_t nbr_samples, double sigma_factor, const RealLimits& limits) const
{
    if (sigma_factor <= 0.0 || sigma_factor > 2.0)
        sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor * m_sigma * M_PI_2;
    double xmax = m_mean + sigma_factor * m_sigma * M_PI_2;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

void DistributionCosine::init_parameters()
{
    registerParameter(BornAgain::Mean, &m_mean);
    registerParameter(BornAgain::Sigma, &m_sigma);
}

bool DistributionCosine::isDelta() const { return m_sigma == 0.0; }

bool DistributionCosine::checkInitialization() const
{
    if (m_sigma < 0.0) {
        SignalBadInitialization(BornAgain::DistributionCosineType);
        return false;
    }
    return true;
}
