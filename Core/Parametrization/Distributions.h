// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Distributions.h
//! @brief     Defines classes representing one-dimensional distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_DISTRIBUTIONS_H
#define BORNAGAIN_CORE_PARAMETRIZATION_DISTRIBUTIONS_H

#include "Core/Basics/ICloneable.h"
#include "Core/Parametrization/INode.h"
#include "Fit/Tools/RealLimits.h"
#include <vector>

class ParameterSample;

// ************************************************************************** //
// interface IDistribution1D
// ************************************************************************** //

//! Interface for one-dimensional distributions.
//! @ingroup distribution_internal

class BA_CORE_API_ IDistribution1D : public ICloneable, public INode
{
public:
    IDistribution1D(const NodeMeta& meta, const std::vector<double>& PValues);

    virtual IDistribution1D* clone() const = 0;

    //! Returns the distribution-specific probability density for value x.
    virtual double probabilityDensity(double x) const = 0;

    //! Returns the distribution-specific mean.
    virtual double getMean() const = 0;

    //! Returns equidistant samples, using intrinsic parameters, weighted with probabilityDensity().
    std::vector<ParameterSample> equidistantSamples(size_t nbr_samples, double sigma_factor = 0.,
                                                    const RealLimits& limits = RealLimits()) const;

    //! Returns equidistant samples from xmin to xmax, weighted with probabilityDensity().
    std::vector<ParameterSample> equidistantSamplesInRange(size_t nbr_samples, double xmin,
                                                           double xmax) const;

    //! Returns equidistant interpolation points, with range computed in distribution-specific
    //! way from mean and width parameter, taking into account limits and sigma_factor.
    virtual std::vector<double>
    equidistantPoints(size_t nbr_samples, double sigma_factor,
                      const RealLimits& limits = RealLimits()) const = 0;

    //! Returns equidistant interpolation points from xmin to xmax.
    virtual std::vector<double> equidistantPointsInRange(size_t nbr_samples, double xmin,
                                                         double xmax) const;

    //! Returns true if the distribution is in the limit case of a Dirac delta distribution.
    virtual bool isDelta() const = 0;

    //! Sets distribution units.
    virtual void setUnits(const std::string& units);

protected:
    //! modifies xmin and xmax if they are outside of limits
    void adjustMinMaxForLimits(double& xmin, double& xmax, const RealLimits& limits) const;

    //! Returns weighted samples from given interpolation points and probabilityDensity().
    std::vector<ParameterSample>
    generateSamplesFromValues(const std::vector<double>& sample_values) const;
};

// ************************************************************************** //
// class DistributionGate
// ************************************************************************** //

//! Uniform distribution function with half width hwhm.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionGate : public IDistribution1D
{
public:
    DistributionGate(const std::vector<double> P);
    DistributionGate(double min, double max);
    DistributionGate();

    DistributionGate* clone() const final { return new DistributionGate(m_min, m_max); }

    double probabilityDensity(double x) const final;
    double getMean() const final { return (m_min + m_max) / 2.0; }
    double getMin() const { return m_min; }
    double getMax() const { return m_max; }

    //! Returns list of sample values
    virtual std::vector<double> equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                  const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    const double& m_min;
    const double& m_max;
};

// ************************************************************************** //
// class DistributionLorentz
// ************************************************************************** //

//! Lorentz distribution with half width hwhm.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionLorentz : public IDistribution1D
{
public:
    DistributionLorentz(const std::vector<double> P);
    DistributionLorentz(double mean, double hwhm);
    DistributionLorentz();

    DistributionLorentz* clone() const final { return new DistributionLorentz(m_mean, m_hwhm); }

    double probabilityDensity(double x) const final;
    double getMean() const final { return m_mean; }
    double getHWHM() const { return m_hwhm; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                  const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    const double& m_mean;
    const double& m_hwhm;
};

// ************************************************************************** //
// class Distribution
// ************************************************************************** //

//! Gaussian distribution with standard deviation std_dev.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionGaussian : public IDistribution1D
{
public:
    DistributionGaussian(const std::vector<double> P);
    DistributionGaussian(double mean, double std_dev);
    DistributionGaussian();

    DistributionGaussian* clone() const final
    {
        return new DistributionGaussian(m_mean, m_std_dev);
    }

    double probabilityDensity(double x) const final;
    double getMean() const final { return m_mean; }
    double getStdDev() const { return m_std_dev; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                  const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    const double& m_mean;
    const double& m_std_dev;
};

// ************************************************************************** //
// class DistributionLogNormal
// ************************************************************************** //

//! Log-normal distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionLogNormal : public IDistribution1D
{
public:
    DistributionLogNormal(const std::vector<double> P);
    DistributionLogNormal(double median, double scale_param);
    DistributionLogNormal() = delete;

    DistributionLogNormal* clone() const final
    {
        return new DistributionLogNormal(m_median, m_scale_param);
    }

    double probabilityDensity(double x) const final;
    double getMean() const final;
    double getMedian() const { return m_median; }
    double getScalePar() const { return m_scale_param; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                  const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    virtual void setUnits(const std::string& units);

private:
    const double& m_median;
    const double& m_scale_param;
};

// ************************************************************************** //
// class DistributionCosine
// ************************************************************************** //

//! Cosine distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionCosine : public IDistribution1D
{
public:
    DistributionCosine(const std::vector<double> P);
    DistributionCosine(double mean, double sigma);
    DistributionCosine();

    DistributionCosine* clone() const final { return new DistributionCosine(m_mean, m_sigma); }

    double probabilityDensity(double x) const final;
    double getMean() const final { return m_mean; }
    double getSigma() const { return m_sigma; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                  const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    const double& m_mean;
    const double& m_sigma;
};

// ************************************************************************** //
// class DistributionTrapezoid
// ************************************************************************** //

//! Trapezoidal distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionTrapezoid : public IDistribution1D
{
public:
    DistributionTrapezoid(const std::vector<double> P);
    DistributionTrapezoid(double center, double left, double middle, double right);
    DistributionTrapezoid();

    DistributionTrapezoid* clone() const final
    {
        return new DistributionTrapezoid(m_center, m_left, m_middle, m_right);
    }

    double probabilityDensity(double x) const final;
    double getMean() const final { return m_center; }
    double getLeftWidth() const { return m_left; }
    double getMiddleWidth() const { return m_middle; }
    double getRightWidth() const { return m_right; }

    //! generate list of sample values
    virtual std::vector<double> equidistantPoints(size_t nbr_samples, double sigma_factor,
                                                  const RealLimits& limits = RealLimits()) const;

    bool isDelta() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

private:
    void adjustLimitsToNonZeroSamples(double& min, double& max, size_t nbr_samples) const;
    const double& m_center;
    const double& m_left;
    const double& m_middle;
    const double& m_right;
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_DISTRIBUTIONS_H
