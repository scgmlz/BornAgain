// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/FTDecay2D.h
//! @brief     Defines classes IFTDecayFunction1D, IFTDecayFunction2D,
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_CORRELATIONS_FTDECAY2D_H
#define BORNAGAIN_CORE_CORRELATIONS_FTDECAY2D_H

#include "Core/Basics/ICloneable.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/INode.h"
#include <utility>

//! Interface for two-dimensional decay function in reciprocal space.
//! @ingroup decayFT_internal
class BA_CORE_API_ IFTDecayFunction2D : public ICloneable, public INode
{
public:
    IFTDecayFunction2D(const NodeMeta& meta, const std::vector<double>& PValues);

    virtual IFTDecayFunction2D* clone() const = 0;

    //! get decay length in distribution's X-direction
    double decayLengthX() const { return m_decay_length_x; }
    //! get decay length in distribution's  Y-direction
    double decayLengthY() const { return m_decay_length_y; }
    //! get angle between first lattice vector and X-axis of distribution (both in direct space)
    double gamma() const { return m_gamma; }

    //! evaluate Fourier transformed decay function for q in X,Y coordinates
    virtual double evaluate(double qx, double qy) const = 0;

    //! transform back to a*, b* basis:
    std::pair<double, double> boundingReciprocalLatticeCoordinates(double qX, double qY, double a,
                                                                   double b, double alpha) const;

protected:
    const double& m_decay_length_x;
    const double& m_decay_length_y;
    const double& m_gamma;

private:
    //! transform reciprocal coordinate system of this decay function to the reciprocal
    //! lattice system
    std::pair<double, double> transformToRecLatticeCoordinates(double qX, double qY, double a,
                                                               double b, double alpha) const;
};

//! Two-dimensional Cauchy decay function in reciprocal space;
//! corresponds to exp(-r) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup decayFT
class BA_CORE_API_ FTDecayFunction2DCauchy : public IFTDecayFunction2D
{
public:
    FTDecayFunction2DCauchy(const std::vector<double> P);
    FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y, double gamma);

    FTDecayFunction2DCauchy* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
};

//! Two-dimensional Gauss decay function in reciprocal space;
//! corresponds to exp(-r^2/2) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup decayFT
class BA_CORE_API_ FTDecayFunction2DGauss : public IFTDecayFunction2D
{
public:
    FTDecayFunction2DGauss(const std::vector<double> P);
    FTDecayFunction2DGauss(double decay_length_x, double decay_length_y, double gamma);

    FTDecayFunction2DGauss* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
};

//! Two-dimensional pseudo-Voigt decay function in reciprocal space;
//! corresponds to eta*Gauss + (1-eta)*Cauchy.
//! @ingroup decayFT
class BA_CORE_API_ FTDecayFunction2DVoigt : public IFTDecayFunction2D
{
public:
    FTDecayFunction2DVoigt(const std::vector<double> P);
    FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y, double gamma, double eta);

    FTDecayFunction2DVoigt* clone() const;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
    double eta() const { return m_eta; }

protected:
    const double& m_eta;
};

#endif // BORNAGAIN_CORE_CORRELATIONS_FTDECAY2D_H
