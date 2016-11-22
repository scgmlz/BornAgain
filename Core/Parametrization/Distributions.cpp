// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Distributions.cpp
//! @brief     Implements classes representing distributions.
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
#include <cmath>
#include <sstream>

IDistribution1D* IDistribution1D::clone() const
{
    throw Exceptions::NotImplementedException("IDistribution1D cannot be cloned");
}

std::vector<ParameterSample> IDistribution1D::generateSamples(
    size_t nbr_samples, double sigma_factor, const RealLimits& limits) const
{
    if (nbr_samples == 0)
        throw Exceptions::OutOfBoundsException("IDistribution1D::generateSamples: number "
                                   "of generated samples must be bigger than zero");
    if (isDelta()) {
        std::vector<ParameterSample> result = { getMeanSample() };
        return result;
    }
    std::vector<double> sample_values = generateValueList( nbr_samples, sigma_factor, limits);
    return generateSamplesFromValues(sample_values);
}

std::vector<ParameterSample> IDistribution1D::generateSamples(
    size_t nbr_samples, double xmin, double xmax) const
{
    if (nbr_samples == 0)
        throw Exceptions::OutOfBoundsException("IDistribution1D::generateSamples: number "
                                   "of generated samples must be bigger than zero");
    if (isDelta()) {
        std::vector<ParameterSample> result = { getMeanSample() };
        return result;
    }
    std::vector<double> sample_values = generateValues(nbr_samples, xmin, xmax);
    return generateSamplesFromValues(sample_values);
}

//! Interface
std::vector<double> IDistribution1D::generateValues(
    size_t nbr_samples, double xmin, double xmax) const
{
    std::vector<double> result;
    if (nbr_samples < 2 || xmin == xmax) {
        result.push_back(getMean());
    } else {
        result.resize(nbr_samples);
        for (size_t i=0; i<nbr_samples; ++i) {
            result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
        }
    }
    return result;
}

ParameterSample IDistribution1D::getMeanSample() const
{
    ParameterSample result;
    result.value = getMean();
    result.weight = 1.0;
    return result;
}

void IDistribution1D::SignalBadInitialization(std::string distribution_name)
{
    throw Exceptions::ClassInitializationException(
        distribution_name +": not correctly initialized");
}

void IDistribution1D::adjustMinMaxForLimits(
    double& xmin, double& xmax, const RealLimits& limits) const
{
    if(limits.hasLowerLimit() && xmin < limits.getLowerLimit()) xmin = limits.getLowerLimit();
    if(limits.hasUpperLimit() && xmax > limits.getUpperLimit()) xmax = limits.getUpperLimit();
    if(xmin > xmax) {
        std::ostringstream ostr;
        ostr << "IDistribution1D::adjustMinMaxForLimits() -> Error. Can't' adjust ";
        ostr << "xmin:" << xmin << " xmax:" << xmax << " for given limits " << limits << std::endl;
        throw Exceptions::DomainErrorException(ostr.str());
    }
}

std::vector<ParameterSample> IDistribution1D::generateSamplesFromValues(
    const std::vector<double>& sample_values) const
{
    std::vector<ParameterSample> result;
    result.resize(sample_values.size());
    double norm_factor = 0.0;
    for (size_t i=0; i<sample_values.size(); ++i) {
        double pdf = probabilityDensity(sample_values[i]);
        result[i].value = sample_values[i];
        result[i].weight = pdf;
        norm_factor += pdf;
    }
    if (norm_factor <= 0.0)
        throw Exceptions::RuntimeErrorException("IDistribution1D::generateSamples: "
                                    "total probability must be bigger than zero");
    for (size_t i=0; i<sample_values.size(); ++i) {
        result[i].weight /= norm_factor;
    }
    return result;
}

// ---------------------------------------------------------------------------------------------- //

DistributionGate::DistributionGate() : m_min(0.0), m_max(1.0)
{
    setName(BornAgain::DistributionGateType);
    checkInitialization();
    init_parameters();
}

DistributionGate::DistributionGate(double min, double max) : m_min(min), m_max(max)
{
    setName(BornAgain::DistributionGateType);
    checkInitialization();
    init_parameters();
}

double DistributionGate::probabilityDensity(double x) const
{
    if (x < m_min || x > m_max) return 0.0;
    if (m_min == m_max) return 1.0;
    return 1.0/(m_max-m_min);
}

std::vector<double> DistributionGate::generateValueList(size_t nbr_samples,
        double, const RealLimits&) const
{
    return generateValues(nbr_samples, m_min, m_max);
}

void DistributionGate::init_parameters()
{
    registerParameter(BornAgain::Minimum, &m_min);
    registerParameter(BornAgain::Maximum, &m_max);
}

bool DistributionGate::isDelta() const
{
    return m_max == m_min;
}

bool DistributionGate::checkInitialization() const
{
    bool result = true;
    if (m_max < m_min) result = false;
    if (!result) SignalBadInitialization(BornAgain::DistributionGateType);
    return result;
}

// ---------------------------------------------------------------------------------------------- //

DistributionLorentz::DistributionLorentz() : m_mean(0.0), m_hwhm(1.0)
{
    setName(BornAgain::DistributionLorentzType);
    checkInitialization();
    init_parameters();
}

DistributionLorentz::DistributionLorentz(double mean, double hwhm) : m_mean(mean), m_hwhm(hwhm)
{
    setName(BornAgain::DistributionLorentzType);
    checkInitialization();
    init_parameters();
}

double DistributionLorentz::probabilityDensity(double x) const
{
    if (m_hwhm == 0.0) return x==m_mean ? 1.0 : 0.0;
    return m_hwhm/(m_hwhm*m_hwhm + (x-m_mean)*(x-m_mean))/M_PI;
}

std::vector<double> DistributionLorentz::generateValueList(size_t nbr_samples,
        double sigma_factor, const RealLimits& limits) const
{
    if (sigma_factor <= 0.0) sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor*m_hwhm;
    double xmax = m_mean + sigma_factor*m_hwhm;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return generateValues(nbr_samples, xmin, xmax);
}

void DistributionLorentz::init_parameters()
{
    registerParameter(BornAgain::Mean, &m_mean);
    registerParameter(BornAgain::HWHM, &m_hwhm);
}

bool DistributionLorentz::isDelta() const
{
    return m_hwhm == 0.0;
}

bool DistributionLorentz::checkInitialization() const
{
    bool result = true;
    if (m_hwhm < 0.0) result = false;
    if (!result) SignalBadInitialization(BornAgain::DistributionLorentzType);
    return result;
}

// ---------------------------------------------------------------------------------------------- //

DistributionGaussian::DistributionGaussian()
    : m_mean(0.0)
    , m_std_dev(1.0)
{
    setName(BornAgain::DistributionGaussianType);
    checkInitialization();
    init_parameters();
}

DistributionGaussian::DistributionGaussian(double mean, double std_dev)
    : m_mean(mean)
    , m_std_dev(std_dev)
{
    setName(BornAgain::DistributionGaussianType);
    checkInitialization();
    init_parameters();
}

double DistributionGaussian::probabilityDensity(double x) const
{
    if (m_std_dev == 0.0) return x==m_mean ? 1.0 : 0.0;
    double exponential = std::exp(-(x-m_mean)*(x-m_mean)
            /(2.0*m_std_dev*m_std_dev));
    return exponential/m_std_dev/std::sqrt(M_TWOPI);
}

std::vector<double> DistributionGaussian::generateValueList(size_t nbr_samples,
        double sigma_factor, const RealLimits& limits) const
{
    if (sigma_factor <= 0.0) sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor*m_std_dev;
    double xmax = m_mean + sigma_factor*m_std_dev;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return generateValues(nbr_samples, xmin, xmax);
}

void DistributionGaussian::init_parameters()
{
    registerParameter(BornAgain::Mean, &m_mean);
    registerParameter(BornAgain::StdDeviation, &m_std_dev);
}

bool DistributionGaussian::isDelta() const
{
    return m_std_dev == 0.0;
}

bool DistributionGaussian::checkInitialization() const
{
    bool result = true;
    if (m_std_dev < 0.0) result = false;
    if (!result) SignalBadInitialization(BornAgain::DistributionGaussianType);
    return result;
}

// ---------------------------------------------------------------------------------------------- //

DistributionLogNormal::DistributionLogNormal(double scale_param)
    : m_median(1.0)
    , m_scale_param(scale_param)
{
    setName(BornAgain::DistributionLogNormalType);
    checkInitialization();
    init_parameters();
}

DistributionLogNormal::DistributionLogNormal(double median, double scale_param)
    : m_median(median)
    , m_scale_param(scale_param)
{
    setName(BornAgain::DistributionLogNormalType);
    checkInitialization();
    init_parameters();
}

double DistributionLogNormal::probabilityDensity(double x) const
{
    if (m_scale_param==0.0) return x==m_median ? 1.0 : 0.0;
    double t = std::log(x/m_median)/m_scale_param;
    return std::exp(-t*t/2.0)/(x*m_scale_param*std::sqrt(M_TWOPI));
}

double DistributionLogNormal::getMean() const
{
    double exponent = m_scale_param*m_scale_param/2.0;
    return m_median*std::exp(exponent);
}

std::vector<double> DistributionLogNormal::generateValueList(size_t nbr_samples,
        double sigma_factor, const RealLimits& limits) const
{
    if(nbr_samples < 2) {
        std::vector<double> result;
        result.push_back(m_median);
        return result;
    } else {
        if (sigma_factor <= 0.0) sigma_factor = 2.0;
        double xmin = m_median*std::exp(-sigma_factor*m_scale_param);
        double xmax = m_median*std::exp(sigma_factor*m_scale_param);
        adjustMinMaxForLimits(xmin, xmax, limits);
        return generateValues(nbr_samples, xmin, xmax);
    }
}

void DistributionLogNormal::init_parameters()
{
    registerParameter(BornAgain::Median, &m_median);
    registerParameter(BornAgain::ScaleParameter, &m_scale_param);
}

bool DistributionLogNormal::isDelta() const
{
    return m_scale_param == 0.0;
}

bool DistributionLogNormal::checkInitialization() const
{
    bool result = true;
    if (m_scale_param < 0.0) result = false;
    if (m_median <= 0.0) result = false;
    if (!result) SignalBadInitialization(BornAgain::DistributionLogNormalType);
    return result;
}

// ---------------------------------------------------------------------------------------------- //

DistributionCosine::DistributionCosine()
    : m_mean(0.0)
    , m_sigma(1.0)
{
    setName(BornAgain::DistributionCosineType);
    checkInitialization();
    init_parameters();
}

DistributionCosine::DistributionCosine(double mean, double sigma)
    : m_mean(mean)
    , m_sigma(sigma)
{
    setName(BornAgain::DistributionCosineType);
    checkInitialization();
    init_parameters();
}

double DistributionCosine::probabilityDensity(double x) const
{
    if (m_sigma == 0.0) return x==m_mean ? 1.0 : 0.0;
    if (std::abs(x-m_mean)>M_PI*m_sigma) return 0.0;
    return (1.0 + std::cos((x-m_mean)/m_sigma))/(m_sigma*M_TWOPI);
}

std::vector<double> DistributionCosine::generateValueList(size_t nbr_samples,
        double sigma_factor, const RealLimits& limits) const
{
    if (sigma_factor <= 0.0 || sigma_factor > 2.0) sigma_factor = 2.0;
    double xmin = m_mean - sigma_factor*m_sigma*M_PI_2;
    double xmax = m_mean + sigma_factor*m_sigma*M_PI_2;
    adjustMinMaxForLimits(xmin, xmax, limits);
    return generateValues(nbr_samples, xmin, xmax);
}

void DistributionCosine::init_parameters()
{
    registerParameter(BornAgain::Mean, &m_mean);
    registerParameter(BornAgain::Sigma, &m_sigma);
}

bool DistributionCosine::isDelta() const
{
    return m_sigma == 0.0;
}

bool DistributionCosine::checkInitialization() const
{
    bool result = true;
    if (m_sigma < 0.0) result = false;
    if (!result) SignalBadInitialization(BornAgain::DistributionCosineType);
    return result;
}
