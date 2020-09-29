// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/FTDistributions1D.h
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_CORRELATIONS_FTDISTRIBUTIONS1D_H
#define BORNAGAIN_CORE_CORRELATIONS_FTDISTRIBUTIONS1D_H

#include "Core/Basics/ICloneable.h"
#include "Core/Correlations/IDistribution1DSampler.h"
#include "Core/Parametrization/INode.h"

//! Interface for a one-dimensional distribution, with normalization adjusted so that
//! the Fourier transform evaluate(q) is a decay function that starts at evaluate(0)=1.
//! @ingroup distribution_internal

class IFTDistribution1D : public ICloneable, public INode
{
public:
    IFTDistribution1D(const NodeMeta& meta, const std::vector<double>& PValues);

    virtual IFTDistribution1D* clone() const = 0;

    //! Returns Fourier transform of this distribution;
    //! is a decay function starting at evaluate(0)=1.
    virtual double evaluate(double q) const = 0;

    double omega() const { return m_omega; }

    //! Returns the negative of the second order derivative in q space around q=0
    virtual double qSecondDerivative() const = 0;

#ifndef SWIG
    virtual std::unique_ptr<IDistribution1DSampler> createSampler() const = 0;
#endif

protected:
    const double& m_omega;
};

//! Exponential IFTDistribution1D exp(-|omega*x|);
//! its Fourier transform evaluate(q) is a Cauchy-Lorentzian starting at evaluate(0)=1.
//! @ingroup distributionFT

class FTDistribution1DCauchy : public IFTDistribution1D
{
public:
    FTDistribution1DCauchy(const std::vector<double> P);
    FTDistribution1DCauchy(double omega);

    FTDistribution1DCauchy* clone() const override final;
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }
    double evaluate(double q) const override final;

    double qSecondDerivative() const override final;
#ifndef SWIG
    std::unique_ptr<IDistribution1DSampler> createSampler() const override final;
#endif
};

//! Gaussian IFTDistribution1D;
//! its Fourier transform evaluate(q) is a Gaussian starting at evaluate(0)=1.
//! @ingroup distributionFT

class FTDistribution1DGauss : public IFTDistribution1D
{
public:
    FTDistribution1DGauss(const std::vector<double> P);
    FTDistribution1DGauss(double omega);

    FTDistribution1DGauss* clone() const override final;
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }
    double evaluate(double q) const override final;

    double qSecondDerivative() const override final;
#ifndef SWIG
    std::unique_ptr<IDistribution1DSampler> createSampler() const override final;
#endif
};

//! Square gate IFTDistribution1D;
//! its Fourier transform evaluate(q) is a sinc function starting at evaluate(0)=1.
//! @ingroup distributionFT

class FTDistribution1DGate : public IFTDistribution1D
{
public:
    FTDistribution1DGate(const std::vector<double> P);
    FTDistribution1DGate(double omega);

    FTDistribution1DGate* clone() const override final;
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }
    double evaluate(double q) const override final;

    double qSecondDerivative() const override final;
#ifndef SWIG
    std::unique_ptr<IDistribution1DSampler> createSampler() const override final;
#endif
};

//! Triangle IFTDistribution1D [1-|x|/omega if |x|<omega, and 0 otherwise];
//! its Fourier transform evaluate(q) is a squared sinc function starting at evaluate(0)=1.
//! @ingroup distributionFT

class FTDistribution1DTriangle : public IFTDistribution1D
{
public:
    FTDistribution1DTriangle(const std::vector<double> P);
    FTDistribution1DTriangle(double omega);

    FTDistribution1DTriangle* clone() const override final;
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }
    double evaluate(double q) const override final;

    double qSecondDerivative() const override final;
#ifndef SWIG
    std::unique_ptr<IDistribution1DSampler> createSampler() const override final;
#endif
};

//! IFTDistribution1D consisting of one cosine wave
//! [1+cos(pi*x/omega) if |x|<omega, and 0 otherwise];
//! its Fourier transform evaluate(q) starts at evaluate(0)=1.
//! @ingroup distributionFT

class FTDistribution1DCosine : public IFTDistribution1D
{
public:
    FTDistribution1DCosine(const std::vector<double> P);
    FTDistribution1DCosine(double omega);

    FTDistribution1DCosine* clone() const override final;
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }
    double evaluate(double q) const override final;

    double qSecondDerivative() const override final;
#ifndef SWIG
    std::unique_ptr<IDistribution1DSampler> createSampler() const override final;
#endif
};

//! IFTDistribution1D that provides a Fourier transform evaluate(q) in form
//! of a pseudo-Voigt decay function eta*Gauss + (1-eta)*Cauchy, with both components
//! starting at 1 for q=0.
//! @ingroup distributionFT

class FTDistribution1DVoigt : public IFTDistribution1D
{
public:
    //! Constructor of one-dimensional pseudo-Voigt probability distribution.
    //! @param omega: half-width of the distribution in nanometers
    //! @param eta: parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)
    FTDistribution1DVoigt(const std::vector<double> P);
    FTDistribution1DVoigt(double omega, double eta);

    FTDistribution1DVoigt* clone() const override final;
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }
    double evaluate(double q) const override final;
    double eta() const { return m_eta; }

    double qSecondDerivative() const override final;
#ifndef SWIG
    std::unique_ptr<IDistribution1DSampler> createSampler() const override final;
#endif

protected:
    const double& m_eta;
};

#endif // BORNAGAIN_CORE_CORRELATIONS_FTDISTRIBUTIONS1D_H
