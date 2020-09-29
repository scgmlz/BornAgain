// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/FTDistributions2D.h
//! @brief     Defines interface class IFTDistribution2D, and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_CORRELATIONS_FTDISTRIBUTIONS2D_H
#define BORNAGAIN_CORE_CORRELATIONS_FTDISTRIBUTIONS2D_H

#include "Core/Basics/ICloneable.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Correlations/IDistribution2DSampler.h"
#include "Core/Parametrization/INode.h"

//! Interface for two-dimensional distributions in Fourier space.
//! @ingroup distribution_internal

class IFTDistribution2D : public ICloneable, public INode
{
public:
    IFTDistribution2D(const NodeMeta& meta, const std::vector<double>& PValues);

    IFTDistribution2D* clone() const = 0;

    double omegaX() const { return m_omega_x; }
    double omegaY() const { return m_omega_y; }
    double gamma() const { return m_gamma; }

    //! Angle in direct space between X- and Y-axis of distribution.
    double delta() const { return M_PI_2; }

    //! evaluate Fourier transformed distribution for q in X,Y coordinates
    //! the original distribution (in real space) is assumed to be normalized:
    //! total integral is equal to 1
    virtual double evaluate(double qx, double qy) const = 0;

#ifndef SWIG
    virtual std::unique_ptr<IDistribution2DSampler> createSampler() const = 0;
#endif

protected:
    double sumsq(double qx, double qy) const;

    const double& m_omega_x;
    const double& m_omega_y;
    const double& m_gamma;
};

//! Two-dimensional Cauchy distribution in Fourier space;
//! corresponds to a normalized exp(-r) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class FTDistribution2DCauchy : public IFTDistribution2D
{
public:
    FTDistribution2DCauchy(const std::vector<double> P);
    FTDistribution2DCauchy(double omega_x, double omega_y, double gamma);

    FTDistribution2DCauchy* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif
};

//! Two-dimensional Gauss distribution in Fourier space;
//! corresponds to normalized exp(-r^2/2) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class FTDistribution2DGauss : public IFTDistribution2D
{
public:
    FTDistribution2DGauss(const std::vector<double> P);
    FTDistribution2DGauss(double omega_x, double omega_y, double gamma);

    FTDistribution2DGauss* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif
};

//! Two-dimensional gate distribution in Fourier space;
//! corresponds to normalized constant if r<1 (and 0 otherwise) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class FTDistribution2DGate : public IFTDistribution2D
{
public:
    FTDistribution2DGate(const std::vector<double> P);
    FTDistribution2DGate(double omega_x, double omega_y, double gamma);

    FTDistribution2DGate* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif
};

//! Two-dimensional cone distribution in Fourier space;
//! corresponds to 1-r if r<1 (and 0 otherwise) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class FTDistribution2DCone : public IFTDistribution2D
{
public:
    FTDistribution2DCone(const std::vector<double> P);
    FTDistribution2DCone(double omega_x, double omega_y, double gamma);

    FTDistribution2DCone* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif
};

//! Two-dimensional Voigt distribution in Fourier space;
//! corresponds to eta*Gauss + (1-eta)*Cauchy
//! @ingroup distributionFT

class FTDistribution2DVoigt : public IFTDistribution2D
{
public:
    FTDistribution2DVoigt(const std::vector<double> P);
    FTDistribution2DVoigt(double omega_x, double omega_y, double gamma, double eta);

    FTDistribution2DVoigt* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
    double eta() const { return m_eta; }
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif

protected:
    const double& m_eta;
};

#endif // BORNAGAIN_CORE_CORRELATIONS_FTDISTRIBUTIONS2D_H
