// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Distributions.h
//! @brief     Defines classes representing one-dimensional distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include "IParameterized.h"
#include "RealLimits.h"
#include <vector>

class ParameterSample;

// ************************************************************************** //
// interface class IDistribution1D
// ************************************************************************** //

//! Interface for one-dimensional distributions.
//! @ingroup distribution_internal

class BA_CORE_API_ IDistribution1D : public IParameterized
{
public:
    IDistribution1D() {}
    virtual ~IDistribution1D() {}

    virtual IDistribution1D* clone() const = 0;

    //! Returns the distribution-specific probability density for value x.
    virtual double probabilityDensity(double x) const = 0;

    //! Returns the distribution-specific mean.
    virtual double getMean() const = 0;

    //! Returns equidistant samples, using intrinsic parameters, weighted with probabilityDensity().
    std::vector<ParameterSample> equidistantSamples(
        size_t nbr_samples, double sigma_factor = 0.,
        const RealLimits& limits = RealLimits()) const;

    //! Returns equidistant samples from xmin to xmax, weighted with probabilityDensity().
    std::vector<ParameterSample>
    equidistantSamplesInRange(size_t nbr_samples, double xmin, double xmax) const;

    //! Returns equidistant interpolation points, with range computed in distribution-specific
    //! way from mean and width parameter, taking into account limits and sigma_factor.
    virtual std::vector<double> equidistantPoints(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const = 0;

    //! Returns equidistant interpolation points from xmin to xmax.
    virtual std::vector<double>
    equidistantPointsInRange(size_t nbr_samples, double xmin, double xmax) const;

    //! Returns true if the distribution is in the limit case of a Dirac delta distribution.
    virtual bool isDelta() const = 0;

protected:
    //! this function is called during bad initialization of a subclass
    static void SignalBadInitialization(std::string distribution_name);

    //! modifies xmin and xmax if they are outside of limits
    void adjustMinMaxForLimits(double& xmin, double& xmax, const RealLimits& limits) const;

    //! Returns weighted samples from given interpolation points and probabilityDensity().
    std::vector<ParameterSample>
    generateSamplesFromValues(const std::vector<double>& sample_values) const;
};


// ************************************************************************** //
// specific distribution classes
// ************************************************************************** //

//! Uniform distribution function with half width hwhm.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionGate : public IDistribution1D
{
public:
    DistributionGate() : DistributionGate(0., 1.) {}
    DistributionGate(double min, double max);
    virtual ~DistributionGate() {}

    DistributionGate* clone() const final { return new DistributionGate(m_min, m_max); }

    double probabilityDensity(double x) const final;
    double getMean() const final { return (m_min + m_max) / 2.0; }
    double getMin() const { return m_min; }
    double getMax() const { return m_max; }

    //! Returns list of sample values
    virtual std::vector<double> equidistantPoints(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_min;
    double m_max;
};


//! Lorentz distribution with half width hwhm.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionLorentz : public IDistribution1D
{
public:
    DistributionLorentz() : DistributionLorentz(0., 1.) {}
    DistributionLorentz(double mean, double hwhm);
    virtual ~DistributionLorentz() {}

    DistributionLorentz* clone() const final { return new DistributionLorentz(m_mean, m_hwhm); }

    double probabilityDensity(double x) const final;
    double getMean() const final { return m_mean; }
    double getHWHM() const { return m_hwhm; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_hwhm;
};


//! Gaussian distribution with standard deviation std_dev.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionGaussian : public IDistribution1D
{
public:
    DistributionGaussian() : DistributionGaussian(0., 1.) {}
    DistributionGaussian(double mean, double std_dev);
    virtual ~DistributionGaussian() {}

    DistributionGaussian* clone() const final
    {
        return new DistributionGaussian(m_mean, m_std_dev);
    }

    double probabilityDensity(double x) const final;
    double getMean() const final { return m_mean; }
    double getStdDev() const { return m_std_dev; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_std_dev;
};


//! Log-normal distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionLogNormal : public IDistribution1D
{
public:
    DistributionLogNormal(double scale_param) : DistributionLogNormal(1., scale_param) {}
    DistributionLogNormal(double median, double scale_param);
    virtual ~DistributionLogNormal() {}

    DistributionLogNormal* clone() const final
    {
        return new DistributionLogNormal(m_median, m_scale_param);
    }

    double probabilityDensity(double x) const final;
    double getMean() const final;
    double getMedian() const { return m_median; }
    double getScalePar() const { return m_scale_param; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_median;
    double m_scale_param;
};


//! Cosine distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionCosine : public IDistribution1D
{
public:
    DistributionCosine() : DistributionCosine(0., 1.) {}
    DistributionCosine(double mean, double sigma);
    virtual ~DistributionCosine() {}

    DistributionCosine* clone() const final { return new DistributionCosine(m_mean, m_sigma); }

    double probabilityDensity(double x) const final;
    double getMean() const final { return m_mean; }
    double getSigma() const { return m_sigma; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_sigma;
};

#endif // DISTRIBUTIONS_H
