// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/RangedDistributions.h
//! @brief     Defines classes representing ranged one-dimensional distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_RANGEDDISTRIBUTIONS_H
#define BORNAGAIN_CORE_PARAMETRIZATION_RANGEDDISTRIBUTIONS_H

#include "Core/Basics/ICloneable.h"
#include "Fit/Tools/RealLimits.h"
#include <memory>
#include <vector>

class IDistribution1D;
class ParameterSample;

// ************************************************************************** //
// interface class IDistribution1D
// ************************************************************************** //

//! Interface for one-dimensional ranged distributions.
//! All derived distributions
//! allow for generating samples in-place for known mean and standard deviation
//! (except for RangedDistributionLorentz which uses median and hwhm).
//! @ingroup distribution_internal

class BA_CORE_API_ RangedDistribution : public ICloneable
{
public:
    RangedDistribution();
    RangedDistribution(size_t n_samples, double sigma_factor,
                       const RealLimits& limits = RealLimits::limitless());
    //! Initializes Ranged distribution with given number of samples, sigma factor
    //! (range in standard deviations to take into account during sample generation)
    //! and limits (either RealLimits object or just min and max limits).
    //! By default _n_samples_ = 5, _sigma_factor_ = 2.0, while the limits are (-inf, +inf).
    RangedDistribution(size_t n_samples, double sigma_factor, double min, double max);
    RangedDistribution* clone() const override = 0;

    ~RangedDistribution() override;

    std::vector<ParameterSample> generateSamples(double mean, double stddev) const;
    //! Generates list of sampled values with their weights from given means and standard
    //! deviations.
    std::vector<std::vector<ParameterSample>>
    generateSamples(const std::vector<double>& mean, const std::vector<double>& stddev) const;

    //! Public interface function to underlying IDistribution1D object
    std::unique_ptr<IDistribution1D> distribution(double mean, double stddev) const;

    // getters

    //! Returns current limits of the distribution
    RealLimits limits() const { return m_limits; }
    //! Returns sigma factor to use during sampling
    double sigmaFactor() const { return m_sigma_factor; }
    //! Returns number of samples to generate
    size_t nSamples() const { return m_n_samples; }

    // setters

    void setLimits(const RealLimits& limits) { m_limits = limits; }

    //! Prints python-formatted definition of the distribution
    std::string print() const;

protected:
    //! Returns distribution name for python-formatted text.
    virtual std::string name() const = 0;
    //! Returns underlying IDistribution1D object
    virtual std::unique_ptr<IDistribution1D> distribution_impl(double mean,
                                                               double stddev) const = 0;

private:
    void checkInitialization();

    size_t m_n_samples;
    double m_sigma_factor;
    RealLimits m_limits;
};

// ************************************************************************** //
// specific distribution classes
// ************************************************************************** //

//! Uniform distribution function.
//! @ingroup paramDistribution

class BA_CORE_API_ RangedDistributionGate : public RangedDistribution
{
public:
    RangedDistributionGate();
    RangedDistributionGate(size_t n_samples, double sigma_factor,
                           const RealLimits& limits = RealLimits::limitless());
    //! Initializes Ranged distribution with given number of samples, sigma factor
    //! (range in standard deviations to take into account during sample generation)
    //! and limits (either RealLimits object or just min and max limits).
    //! By default _n_samples_ = 5, _sigma_factor_ = 2.0, while the limits are (-inf, +inf).
    RangedDistributionGate(size_t n_samples, double sigma_factor, double min, double max);

    RangedDistributionGate* clone() const override;
    ~RangedDistributionGate() override = default;

protected:
    //! Returns distribution name for python-formatted text.
    std::string name() const override;
    //! Returns underlying IDistribution1D object
    std::unique_ptr<IDistribution1D> distribution_impl(double mean, double stddev) const override;
};

//! Lorentz distribution with median and hwhm.
//! @ingroup paramDistribution

class BA_CORE_API_ RangedDistributionLorentz : public RangedDistribution
{
public:
    RangedDistributionLorentz();
    RangedDistributionLorentz(size_t n_samples, double hwhm_factor,
                              const RealLimits& limits = RealLimits::limitless());
    //! Initializes Ranged distribution with given number of samples, sigma factor
    //! (range in standard deviations to take into account during sample generation)
    //! and limits (either RealLimits object or just min and max limits).
    //! By default _n_samples_ = 5, _hwhm_factor_ = 2.0, while the limits are (-inf, +inf).
    RangedDistributionLorentz(size_t n_samples, double hwhm_factor, double min, double max);

    RangedDistributionLorentz* clone() const override;
    ~RangedDistributionLorentz() override = default;

protected:
    //! Returns distribution name for python-formatted text.
    std::string name() const override;
    //! Returns underlying IDistribution1D object
    std::unique_ptr<IDistribution1D> distribution_impl(double median, double hwhm) const override;
};

//! Gaussian distribution with standard deviation std_dev.
//! @ingroup paramDistribution

class BA_CORE_API_ RangedDistributionGaussian : public RangedDistribution
{
public:
    RangedDistributionGaussian();
    RangedDistributionGaussian(size_t n_samples, double sigma_factor,
                               const RealLimits& limits = RealLimits::limitless());
    //! Initializes Ranged distribution with given number of samples, sigma factor
    //! (range in standard deviations to take into account during sample generation)
    //! and limits (either RealLimits object or just min and max limits).
    //! By default _n_samples_ = 5, _sigma_factor_ = 2.0, while the limits are (-inf, +inf).
    RangedDistributionGaussian(size_t n_samples, double sigma_factor, double min, double max);

    RangedDistributionGaussian* clone() const override;
    ~RangedDistributionGaussian() override = default;

protected:
    //! Returns distribution name for python-formatted text.
    std::string name() const override;
    //! Returns underlying IDistribution1D object
    std::unique_ptr<IDistribution1D> distribution_impl(double mean, double stddev) const override;
};

//! Log-normal distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ RangedDistributionLogNormal : public RangedDistribution
{
public:
    RangedDistributionLogNormal();
    RangedDistributionLogNormal(size_t n_samples, double sigma_factor,
                                const RealLimits& limits = RealLimits::limitless());
    //! Initializes Ranged distribution with given number of samples, sigma factor
    //! (range in standard deviations to take into account during sample generation)
    //! and limits (either RealLimits object or just min and max limits).
    //! By default _n_samples_ = 5, _sigma_factor_ = 2.0, while the limits are (-inf, +inf).
    RangedDistributionLogNormal(size_t n_samples, double sigma_factor, double min, double max);

    RangedDistributionLogNormal* clone() const override;
    ~RangedDistributionLogNormal() override = default;

protected:
    //! Returns distribution name for python-formatted text.
    std::string name() const override;
    //! Returns underlying IDistribution1D object
    std::unique_ptr<IDistribution1D> distribution_impl(double mean, double stddev) const override;
};

//! Cosine distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ RangedDistributionCosine : public RangedDistribution
{
public:
    RangedDistributionCosine();
    RangedDistributionCosine(size_t n_samples, double sigma_factor,
                             const RealLimits& limits = RealLimits::limitless());
    //! Initializes Ranged distribution with given number of samples, sigma factor
    //! (range in standard deviations to take into account during sample generation)
    //! and limits (either RealLimits object or just min and max limits).
    //! By default _n_samples_ = 5, _sigma_factor_ = 2.0, while the limits are (-inf, +inf).
    RangedDistributionCosine(size_t n_samples, double sigma_factor, double min, double max);

    RangedDistributionCosine* clone() const override;
    ~RangedDistributionCosine() override = default;

protected:
    //! Returns distribution name for python-formatted text.
    std::string name() const override;
    //! Returns underlying IDistribution1D object
    std::unique_ptr<IDistribution1D> distribution_impl(double mean, double stddev) const override;
};

inline std::ostream& operator<<(std::ostream& os, const RangedDistribution& distribution)
{
    return os << distribution.print();
}

#endif // BORNAGAIN_CORE_PARAMETRIZATION_RANGEDDISTRIBUTIONS_H
