// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDecayFunctions.cpp
//! @brief     Implements class FTDistribution2DCauchy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDecayFunctions.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "ParameterPool.h"
#include "RealParameter.h"

//===============1D======================


void IFTDecayFunction1D::print(std::ostream& ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}

void IFTDecayFunction1D::init_parameters() { registerParameter(BornAgain::Omega, &m_omega); }

FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double omega) : IFTDecayFunction1D(omega)
{
    setName(BornAgain::FTDecayFunction1DCauchyType);
    init_parameters();
}

double FTDecayFunction1DCauchy::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return m_omega * 2.0 / (1.0 + sum_sq);
}

FTDecayFunction1DGauss::FTDecayFunction1DGauss(double omega) : IFTDecayFunction1D(omega)
{
    setName(BornAgain::FTDecayFunction1DGaussType);
    init_parameters();
}

double FTDecayFunction1DGauss::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return m_omega * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0);
}

FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double omega) : IFTDecayFunction1D(omega)
{
    setName(BornAgain::FTDecayFunction1DTriangleType);
    init_parameters();
}

double FTDecayFunction1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q * m_omega / 2.0);
    return m_omega * sincqw2 * sincqw2;
}

FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double omega, double eta)
    : IFTDecayFunction1D(omega), m_eta(eta)
{
    setName(BornAgain::FTDecayFunction1DVoigtType);
    init_parameters();
}

double FTDecayFunction1DVoigt::evaluate(double q) const
{
    double sum_sq = q * q * m_omega * m_omega;
    return m_eta * m_omega * std::sqrt(M_TWOPI) * std::exp(-sum_sq / 2.0)
        + (1.0 - m_eta) * m_omega * 2.0 / (1.0 + sum_sq);
}

void FTDecayFunction1DVoigt::init_parameters()
{
    IFTDecayFunction1D::init_parameters();
    registerParameter(BornAgain::Eta, &m_eta);
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

IFTDecayFunction2D::IFTDecayFunction2D(
    double decay_length_x, double decay_length_y, double gamma, double delta)
    : m_omega_x(decay_length_x), m_omega_y(decay_length_y), m_gamma(gamma), m_delta(delta)
{
}

void IFTDecayFunction2D::transformToStarBasis(
    double qX, double qY, double alpha, double a, double b, double& qa, double& qb) const
{
    double prefactor = 1.0 / M_TWOPI; // divide by sin(m_delta)
    // for unnormalized X*,Y* basis
    qa = a * prefactor * (std::sin(m_gamma + m_delta) * qX - std::sin(m_gamma) * qY);
    qb = b * prefactor
        * (-std::sin(alpha - m_gamma - m_delta) * qX + std::sin(alpha - m_gamma) * qY);
}

void IFTDecayFunction2D::print(std::ostream& ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}

void IFTDecayFunction2D::init_parameters()
{
    registerParameter(BornAgain::DecayLengthX, &m_omega_x).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::DecayLengthY, &m_omega_y).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Gamma, &m_gamma).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
    registerParameter(BornAgain::Delta, &m_delta).setUnit("rad").setLimited(0, M_PI);
}

FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(
    double decay_length_x, double decay_length_y, double gamma, double delta)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma, delta)
{
    setName(BornAgain::FTDecayFunction2DCauchyType);
    init_parameters();
}

double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_omega_x * m_omega_x + qy * qy * m_omega_y * m_omega_y;
    return M_TWOPI * m_omega_x * m_omega_y * std::pow(1.0 + sum_sq, -1.5);
}

FTDecayFunction2DGauss::FTDecayFunction2DGauss(
    double decay_length_x, double decay_length_y, double gamma, double delta)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma, delta)
{
    setName(BornAgain::FTDecayFunction2DGaussType);
    init_parameters();
}

double FTDecayFunction2DGauss::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_omega_x * m_omega_x + qy * qy * m_omega_y * m_omega_y;
    return M_TWOPI * m_omega_x * m_omega_y * std::exp(-sum_sq / 2.0);
}

FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(
    double decay_length_x, double decay_length_y, double eta, double gamma, double delta)
    : IFTDecayFunction2D(decay_length_x, decay_length_y, gamma, delta), m_eta(eta)
{
    setName(BornAgain::FTDecayFunction2DVoigtType);
    init_parameters();
}

double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const
{
    double sum_sq = qx * qx * m_omega_x * m_omega_x + qy * qy * m_omega_y * m_omega_y;
    return M_TWOPI * m_omega_x * m_omega_y
        * (m_eta * std::exp(-sum_sq / 2.0) + (1.0 - m_eta) * std::pow(1.0 + sum_sq, -1.5));
}

void FTDecayFunction2DVoigt::init_parameters()
{
    registerParameter(BornAgain::DecayLengthX, &m_omega_x).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::DecayLengthY, &m_omega_y).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Eta, &m_eta);
    registerParameter(BornAgain::Gamma, &m_gamma).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
    registerParameter(BornAgain::Delta, &m_delta).setUnit("rad").setLimited(0, M_PI);
}
