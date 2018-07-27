// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDecayFunctions.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FTDecayFunctions.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "ParameterPool.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include <algorithm>

//===============1D======================

IFTDecayFunction1D::IFTDecayFunction1D(double decay_length)
    : m_decay_length(decay_length)
{}

void IFTDecayFunction1D::register_decay_length()
{
    registerParameter(BornAgain::DecayLength, &m_decay_length);
}

FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double decay_length)
    : IFTDecayFunction1D(decay_length)
{
    setName(BornAgain::FTDecayFunction1DCauchyType);
    register_decay_length();
}

FTDecayFunction1DCauchy* FTDecayFunction1DCauchy::clone() const
{
    return new FTDecayFunction1DCauchy(m_decay_length);
}

double FTDecayFunction1DCauchy::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_decay_length * 2.0 / (1.0 + sum_sq);
}

FTDecayFunction1DGauss::FTDecayFunction1DGauss(double decay_length)
    : IFTDecayFunction1D(decay_length)
{
    setName(BornAgain::FTDecayFunction1DGaussType);
    register_decay_length();
}

FTDecayFunction1DGauss* FTDecayFunction1DGauss::clone() const
{
    return new FTDecayFunction1DGauss(m_decay_length);
}

double FTDecayFunction1DGauss::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_decay_length * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0);
}

FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double decay_length)
    : IFTDecayFunction1D(decay_length)
{
    setName(BornAgain::FTDecayFunction1DTriangleType);
    register_decay_length();
}

FTDecayFunction1DTriangle* FTDecayFunction1DTriangle::clone() const
{
    return new FTDecayFunction1DTriangle(m_decay_length);
}

double FTDecayFunction1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q * m_decay_length / 2.0);
    return m_decay_length * sincqw2 * sincqw2;
}

FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double decay_length, double eta)
    : IFTDecayFunction1D(decay_length), m_eta(eta)
{
    setName(BornAgain::FTDecayFunction1DVoigtType);
    register_decay_length();
    registerParameter(BornAgain::Eta, &m_eta);
}

FTDecayFunction1DVoigt* FTDecayFunction1DVoigt::clone() const
{
    return new FTDecayFunction1DVoigt(m_decay_length, m_eta);
}

double FTDecayFunction1DVoigt::evaluate(double q) const
{
    double sum_sq = q * q * m_decay_length * m_decay_length;
    return m_eta * m_decay_length * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0)
           + (1.0 - m_eta) * m_decay_length * 2.0 / (1.0 + sum_sq);
}

/* Commented out decay functions: see header for rationale
FTDecayFunction1DGate::FTDecayFunction1DGate(double omega)
    : IFTDecayFunction1D(omega)
{
    setName(BornAgain::FTDecayFunction1DGateType);
    init_parameters();
}

double FTDecayFunction1DGate::evaluate(double q) const
{
    return 2.0*m_omega*MathFunctions::Sinc(q*m_omega);
}

FTDecayFunction1DCosine::FTDecayFunction1DCosine(double omega)
    : IFTDecayFunction1D(omega)
{
    setName(BornAgain::FTDecayFunction1DCosineType);
    init_parameters();
}

double FTDecayFunction1DCosine::evaluate(double q) const
{
    double qw = std::abs(q*m_omega);
    if (std::abs(qw/M_PI-1.0) < std::numeric_limits<double>::epsilon()) {
        return m_omega/2.0;
    }
    else {
        return m_omega*MathFunctions::Sinc(qw)/(1.0-qw*qw/M_PI/M_PI);
    }
}
*/

//==============2D====================

//! Constructor of two-dimensional decay function in reciprocal space.
//! @param decay_length_x: the decay length in nanometers along x-axis of the distribution
//! @param decay_length_y: the decay length in nanometers along y-axis of the distribution
//! @param gamma: distribution orientation with respect to the corresponding lattice vector
//! in radians
IFTDecayFunction2D::IFTDecayFunction2D(double decay_length_x, double decay_length_y, double gamma)
    : m_decay_length_x(decay_length_x), m_decay_length_y(decay_length_y), m_gamma(gamma)
{}

//! Calculates bounding values of reciprocal lattice coordinates that contain the centered
//! rectangle with a corner defined by qX and qY
std::pair<double, double>
IFTDecayFunction2D::boundingReciprocalLatticeCoordinates(double qX, double qY, double alpha,
                                                         double a, double b) const
{
    auto q_bounds_1 = transformToRecLatticeCoordinates(qX, qY, a, b, alpha);
    auto q_bounds_2 = transformToRecLatticeCoordinates(qX, -qY, a, b, alpha);
    double qa_max = std::max(std::abs(q_bounds_1.first), std::abs(q_bounds_2.first));
    double qb_max = std::max(std::abs(q_bounds_1.second), std::abs(q_bounds_2.second));
    return {qa_max, qb_max};
}

void IFTDecayFunction2D::register_decay_lengths()
{
    registerParameter(BornAgain::DecayLengthX, &m_decay_length_x).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::DecayLengthY, &m_decay_length_y).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
}

void IFTDecayFunction2D::register_gamma()
{
    registerParameter(BornAgain::Gamma, &m_gamma).setUnit(BornAgain::UnitsRad)
        .setLimited(-M_PI_2, M_PI_2);
}

void IFTDecayFunction2D::init_parameters()
{
    register_decay_lengths();
    register_gamma();
}

std::pair<double, double> IFTDecayFunction2D::transformToRecLatticeCoordinates(
        double qX, double qY, double a, double b, double alpha) const
{
    double qa = a * qX * std::cos(m_gamma) - a * qY * std::sin(m_gamma);
    double qb = b * qX * std::cos(alpha - m_gamma) + b * qY * std::sin(alpha - m_gamma);
    return {qa, qb};
}

FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y,
                                                 double gamma)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma)
{
    setName(BornAgain::FTDecayFunction2DCauchyType);
    init_parameters();
}

FTDecayFunction2DCauchy* FTDecayFunction2DCauchy::clone() const
{
    return new FTDecayFunction2DCauchy(m_decay_length_x, m_decay_length_y, m_gamma);
}

double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y * std::pow(1.0 + sum_sq, -1.5);
}

FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y,
                                               double gamma)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma)
{
    setName(BornAgain::FTDecayFunction2DGaussType);
    init_parameters();
}

FTDecayFunction2DGauss* FTDecayFunction2DGauss::clone() const
{
    return new FTDecayFunction2DGauss(m_decay_length_x, m_decay_length_y, m_gamma);
}

double FTDecayFunction2DGauss::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y * std::exp(-sum_sq / 2.0);
}

//! Constructor of two-dimensional pseudo-Voigt decay function in reciprocal space.
//! @param decay_length_x: the decay length in nanometers along x-axis of the distribution
//! @param decay_length_y: the decay length in nanometers along y-axis of the distribution
//! @param eta: parameter [0,1] to balance between Cauchy (eta=0.0) and Gauss (eta=1.0)
//! @param gamma: distribution orientation with respect to the first lattice vector in radians

FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y,
                                               double eta, double gamma)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma), m_eta(eta)
{
    setName(BornAgain::FTDecayFunction2DVoigtType);
    register_decay_lengths();
    registerParameter(BornAgain::Eta, &m_eta);
    register_gamma();
}

FTDecayFunction2DVoigt* FTDecayFunction2DVoigt::clone() const
{
    return new FTDecayFunction2DVoigt(m_decay_length_x, m_decay_length_y, m_eta, m_gamma);
}

double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_decay_length_x * m_decay_length_x
                    + qy * qy * m_decay_length_y * m_decay_length_y;
    return M_TWOPI * m_decay_length_x * m_decay_length_y
           * (m_eta * std::exp(-sum_sq / 2.0) + (1.0 - m_eta) * std::pow(1.0 + sum_sq, -1.5));
}
