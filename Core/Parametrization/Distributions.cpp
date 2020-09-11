// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Distributions.cpp
//! @brief     Implements classes representing one-dimensional distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/Distributions.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/RealParameter.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>

namespace
{
bool DoubleEqual(double a, double b);
}

// ************************************************************************** //
// class IDistribution1D
// ************************************************************************** //

IDistribution1D::IDistribution1D(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(meta, PValues)
{
}

//! Returns equidistant samples, using intrinsic parameters, weighted with probabilityDensity().

std::vector<ParameterSample> IDistribution1D::equidistantSamples(size_t nbr_samples,
                                                                 double sigma_factor,
                                                                 const RealLimits& limits) const
{
    if (nbr_samples == 0)
        throw Exceptions::OutOfBoundsException(
            "IDistribution1D::generateSamples: "
            "number of generated samples must be bigger than zero");
    if (isDelta())
        return {ParameterSample(getMean())};
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
        return {ParameterSample(getMean())};
    return generateSamplesFromValues(equidistantPointsInRange(nbr_samples, xmin, xmax));
}

//! Returns equidistant interpolation points from xmin to xmax.

std::vector<double> IDistribution1D::equidistantPointsInRange(size_t nbr_samples, double xmin,
                                                              double xmax) const
{
    if (nbr_samples < 2 || DoubleEqual(xmin, xmax))
        return {getMean()};
    std::vector<double> result(nbr_samples);
    for (size_t i = 0; i < nbr_samples; ++i)
        result[i] = xmin + i * (xmax - xmin) / (nbr_samples - 1.0);
    return result;
}

void IDistribution1D::setUnits(const std::string& units)
{
    for (auto* par : parameterPool()->parameters())
        par->setUnit(units);
}

void IDistribution1D::adjustMinMaxForLimits(double& xmin, double& xmax,
                                            const RealLimits& limits) const
{
    if (limits.hasLowerLimit() && xmin < limits.lowerLimit())
        xmin = limits.lowerLimit();
    if (limits.hasUpperLimit() && xmax > limits.upperLimit())
        xmax = limits.upperLimit();
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

DistributionGate::DistributionGate(const std::vector<double> P)
    : IDistribution1D(
        {"DistributionGate",
         "class_tooltip",
         {{"Min", "", "para_tooltip", -INF, +INF, 0}, {"Max", "", "para_tooltip", -INF, +INF, 0}}},
        P),
      m_min(m_P[0]), m_max(m_P[1])
{
    if (m_max < m_min)
        throw Exceptions::ClassInitializationException("DistributionGate: max<min");
}

DistributionGate::DistributionGate(double min, double max)
    : DistributionGate(std::vector<double>{min, max})
{
}

DistributionGate::DistributionGate() : DistributionGate(0., 1.) {}

double DistributionGate::probabilityDensity(double x) const
{
    if (x < m_min || x > m_max)
        return 0.0;
    if (DoubleEqual(m_min, m_max))
        return 1.0;
    return 1.0 / (m_max - m_min);
}

std::vector<double> DistributionGate::equidistantPoints(size_t nbr_samples, double /*sigma_factor*/,
                                                        const RealLimits& limits) const
{
    double xmin = m_min;
    double xmax = m_max;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

bool DistributionGate::isDelta() const
{
    return DoubleEqual(m_min, m_max);
}

// ************************************************************************** //
// class DistributionLorentz
// ************************************************************************** //

DistributionLorentz::DistributionLorentz(const std::vector<double> P)
    : IDistribution1D({"DistributionLorentz",
                       "class_tooltip",
                       {{"Mean", "", "para_tooltip", -INF, +INF, 0},
                        {"HWHM", "", "para_tooltip", -INF, +INF, 0}}},
                      P),
      m_mean(m_P[0]), m_hwhm(m_P[1])
{
    if (m_hwhm < 0.0)
        throw Exceptions::ClassInitializationException("DistributionLorentz: hwhm<0");
}

DistributionLorentz::DistributionLorentz(double mean, double hwhm)
    : DistributionLorentz(std::vector<double>{mean, hwhm})
{
}

DistributionLorentz::DistributionLorentz() : DistributionLorentz(0., 1.) {}

double DistributionLorentz::probabilityDensity(double x) const
{
    if (m_hwhm == 0.0)
        return DoubleEqual(x, m_mean) ? 1.0 : 0.0;
    return m_hwhm / (m_hwhm * m_hwhm + (x - m_mean) * (x - m_mean)) / M_PI;
}

std::vector<double> DistributionLorentz::equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                           const RealLimits& limits) const
{
    if (sigma_factor <= 0.0)
        sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor * m_hwhm;
    double xmax = m_mean + sigma_factor * m_hwhm;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

bool DistributionLorentz::isDelta() const
{
    return m_hwhm == 0.0;
}

// ************************************************************************** //
// class DistributionGaussian
// ************************************************************************** //

DistributionGaussian::DistributionGaussian(const std::vector<double> P)
    : IDistribution1D({"DistributionGaussian",
                       "class_tooltip",
                       {{"Mean", "", "para_tooltip", -INF, +INF, 0},
                        {"StdDev", "", "para_tooltip", -INF, +INF, 0}}},
                      P),
      m_mean(m_P[0]), m_std_dev(m_P[1])
{
    if (m_std_dev < 0.0)
        throw Exceptions::ClassInitializationException("DistributionGaussian: std_dev < 0");
}

DistributionGaussian::DistributionGaussian(double mean, double std_dev)
    : DistributionGaussian(std::vector<double>{mean, std_dev})
{
}

DistributionGaussian::DistributionGaussian() : DistributionGaussian(0., 1.) {}

double DistributionGaussian::probabilityDensity(double x) const
{
    if (m_std_dev == 0.0)
        return DoubleEqual(x, m_mean) ? 1.0 : 0.0;
    double exponential = std::exp(-(x - m_mean) * (x - m_mean) / (2.0 * m_std_dev * m_std_dev));
    return exponential / m_std_dev / std::sqrt(M_TWOPI);
}

std::vector<double> DistributionGaussian::equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                            const RealLimits& limits) const
{
    if (sigma_factor <= 0.0)
        sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor * m_std_dev;
    double xmax = m_mean + sigma_factor * m_std_dev;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

bool DistributionGaussian::isDelta() const
{
    return m_std_dev == 0.0;
}

// ************************************************************************** //
// class DistributionLogNormal
// ************************************************************************** //

DistributionLogNormal::DistributionLogNormal(const std::vector<double> P)
    : IDistribution1D({"DistributionLogNormal",
                       "class_tooltip",
                       {{"Median", "", "para_tooltip", -INF, +INF, 0},
                        {"ScaleParameter", "", "para_tooltip", -INF, +INF, 0}}},
                      P),
      m_median(m_P[0]), m_scale_param(m_P[1])
{
    if (m_scale_param < 0.0)
        throw Exceptions::ClassInitializationException("DistributionLogNormal: scale_param < 0");
    if (m_median <= 0.0)
        throw Exceptions::ClassInitializationException("DistributionLogNormal: median < 0");
}

DistributionLogNormal::DistributionLogNormal(double median, double scale_param)
    : DistributionLogNormal(std::vector<double>{median, scale_param})
{
}

DistributionTrapezoid::DistributionTrapezoid() : DistributionTrapezoid(0., 0., 1., 0.) {}

double DistributionLogNormal::probabilityDensity(double x) const
{
    if (m_scale_param == 0.0)
        return DoubleEqual(x, m_median) ? 1.0 : 0.0;
    double t = std::log(x / m_median) / m_scale_param;
    return std::exp(-t * t / 2.0) / (x * m_scale_param * std::sqrt(M_TWOPI));
}

double DistributionLogNormal::getMean() const
{
    double exponent = m_scale_param * m_scale_param / 2.0;
    return m_median * std::exp(exponent);
}

std::vector<double> DistributionLogNormal::equidistantPoints(size_t nbr_samples,
                                                             double sigma_factor,
                                                             const RealLimits& limits) const
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

bool DistributionLogNormal::isDelta() const
{
    return m_scale_param == 0.0;
}

void DistributionLogNormal::setUnits(const std::string& units)
{
    parameter("Median")->setUnit(units);
    // scale parameter remains unitless
}

// ************************************************************************** //
// class DistributionCosine
// ************************************************************************** //

DistributionCosine::DistributionCosine(const std::vector<double> P)
    : IDistribution1D({"DistributionCosine",
                       "class_tooltip",
                       {{"Mean", "", "para_tooltip", -INF, +INF, 0},
                        {"Sigma", "", "para_tooltip", -INF, +INF, 0}}},
                      P),
      m_mean(m_P[0]), m_sigma(m_P[1])
{
    if (m_sigma < 0.0)
        throw Exceptions::ClassInitializationException("DistributionCosine: sigma<0");
}

DistributionCosine::DistributionCosine(double mean, double sigma)
    : DistributionCosine(std::vector<double>{mean, sigma})
{
}

DistributionCosine::DistributionCosine() : DistributionCosine(0., 1.) {}

double DistributionCosine::probabilityDensity(double x) const
{
    if (m_sigma == 0.0)
        return DoubleEqual(x, m_mean) ? 1.0 : 0.0;
    if (std::abs(x - m_mean) > M_PI * m_sigma)
        return 0.0;
    return (1.0 + std::cos((x - m_mean) / m_sigma)) / (m_sigma * M_TWOPI);
}

std::vector<double> DistributionCosine::equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                          const RealLimits& limits) const
{
    if (sigma_factor <= 0.0 || sigma_factor > 2.0)
        sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor * m_sigma * M_PI_2;
    double xmax = m_mean + sigma_factor * m_sigma * M_PI_2;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

bool DistributionCosine::isDelta() const
{
    return m_sigma == 0.0;
}

// ************************************************************************** //
// class DistributionTrapezoidal
// ************************************************************************** //

DistributionTrapezoid::DistributionTrapezoid(const std::vector<double> P)
    : IDistribution1D({"DistributionTrapezoid",
                       "class_tooltip",
                       {{"Center", "", "para_tooltip", -INF, +INF, 0},
                        {"LeftWidth", "", "para_tooltip", -INF, +INF, 0},
                        {"MiddleWidth", "", "para_tooltip", -INF, +INF, 0},
                        {"RightWidth", "", "para_tooltip", -INF, +INF, 0}}},
                      P),
      m_center(m_P[0]), m_left(m_P[1]), m_middle(m_P[2]), m_right(m_P[3])
{
    if (m_left < 0.0)
        throw Exceptions::ClassInitializationException("DistributionTrapezoid: leftWidth < 0");
    if (m_middle < 0.0)
        throw Exceptions::ClassInitializationException("DistributionTrapezoid: middleWidth < 0");
    if (m_right < 0.0)
        throw Exceptions::ClassInitializationException("DistributionTrapezoid: rightWidth < 0");
}

DistributionTrapezoid::DistributionTrapezoid(double center, double left, double middle,
                                             double right)
    : DistributionTrapezoid(std::vector<double>{center, left, middle, right})
{
}

double DistributionTrapezoid::probabilityDensity(double x) const
{
    double height = 2.0 / (m_left + 2.0 * m_middle + m_right);
    double min = m_center - m_middle / 2.0 - m_left;
    if (x < min)
        return 0.0;
    if (x < min + m_left)
        return (x - min) * height / m_left;
    if (x < min + m_left + m_middle)
        return height;
    if (x < min + m_left + m_middle + m_right) {
        return height - (x - min - m_left - m_middle) * height / m_right;
    }
    return 0.0;
}

std::vector<double> DistributionTrapezoid::equidistantPoints(size_t nbr_samples, double,
                                                             const RealLimits& limits) const
{
    double xmin = m_center - m_middle / 2.0 - m_left;
    double xmax = xmin + m_left + m_middle + m_right;
    adjustLimitsToNonZeroSamples(xmin, xmax, nbr_samples);
    adjustMinMaxForLimits(xmin, xmax, limits);
    return equidistantPointsInRange(nbr_samples, xmin, xmax);
}

bool DistributionTrapezoid::isDelta() const
{
    return (m_left + m_middle + m_right) == 0.0;
}

void DistributionTrapezoid::adjustLimitsToNonZeroSamples(double& min, double& max,
                                                         size_t nbr_samples) const
{
    if (nbr_samples <= 1)
        return;
    size_t N = nbr_samples;
    if (m_left > 0.0)
        ++N;
    if (m_right > 0.0)
        ++N;
    if (N == nbr_samples)
        return;
    double step = (max - min) / (N - 1);
    if (m_left > 0.0)
        min += step;
    if (m_right > 0.0)
        max -= step;
}

namespace
{
bool DoubleEqual(double a, double b)
{
    double eps = 10.0
                 * std::max(std::abs(a) * std::numeric_limits<double>::epsilon(),
                            std::numeric_limits<double>::min());
    return std::abs(a - b) < eps;
}
} // namespace
