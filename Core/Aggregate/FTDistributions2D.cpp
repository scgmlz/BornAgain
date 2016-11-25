// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions2D.cpp
//! @brief     Implements interface class IFTDistribution2D and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FTDistributions2D.h"
#include "BornAgainNamespace.h"
#include "IntegratorReal.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include <limits>

IFTDistribution2D::IFTDistribution2D(
    double coherence_length_x, double coherence_length_y, double gamma, double delta)
    : m_coherence_length_x(coherence_length_x)
    , m_coherence_length_y(coherence_length_y)
    , m_gamma(gamma)
    , m_delta(delta)
{
}

void IFTDistribution2D::init_parameters()
{
    registerParameter(BornAgain::CoherenceLengthX, &m_coherence_length_x)
        .setUnit("nm")
        .setNonnegative();
    registerParameter(BornAgain::CoherenceLengthY, &m_coherence_length_y)
        .setUnit("nm")
        .setNonnegative();
    registerParameter(BornAgain::Gamma, &m_gamma).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
    registerParameter(BornAgain::Delta, &m_delta).setUnit("rad").setLimited(0, M_PI);
}

void IFTDistribution2D::print(std::ostream& ostr) const
{
    ostr << getName() << " " << *getParameterPool();
}


FTDistribution2DCauchy::FTDistribution2DCauchy(
    double coherence_length_x, double coherence_length_y, double gamma, double delta)
    : IFTDistribution2D(coherence_length_x, coherence_length_y, gamma, delta)
{
    setName(BornAgain::FTDistribution2DCauchyType);
    init_parameters();
}

double FTDistribution2DCauchy::evaluate(double qx, double qy) const
{
    return std::pow(1.0 + sumsq(qx, qy), -1.5);
}


FTDistribution2DGauss::FTDistribution2DGauss(
    double coherence_length_x, double coherence_length_y, double gamma, double delta)
    : IFTDistribution2D(coherence_length_x, coherence_length_y, gamma, delta)
{
    setName(BornAgain::FTDistribution2DGaussType);
    init_parameters();
}

double FTDistribution2DGauss::evaluate(double qx, double qy) const
{
    return std::exp(-sumsq(qx, qy) / 2);
}


FTDistribution2DGate::FTDistribution2DGate(
    double coherence_length_x, double coherence_length_y, double gamma, double delta)
    : IFTDistribution2D(coherence_length_x, coherence_length_y, gamma, delta)
{
    setName(BornAgain::FTDistribution2DGateType);
    init_parameters();
}

double FTDistribution2DGate::evaluate(double qx, double qy) const
{
    double scaled_q = std::sqrt(sumsq(qx, qy));
    return MathFunctions::Bessel_J1c(scaled_q) * 2.0;
}


FTDistribution2DCone::FTDistribution2DCone(
    double coherence_length_x, double coherence_length_y, double gamma, double delta)
    : IFTDistribution2D(coherence_length_x, coherence_length_y, gamma, delta)
{
    setName(BornAgain::FTDistribution2DConeType);
    init_parameters();
}

double FTDistribution2DCone::evaluate(double qx, double qy) const
{
    double scaled_q = std::sqrt(sumsq(qx, qy));
    if (scaled_q < std::numeric_limits<double>::epsilon())
        return 1.0 - 3.0 * scaled_q * scaled_q / 40.0;
    auto integrator = make_integrator_real(this, &FTDistribution2DCone::coneIntegrand2);
    double integral = integrator->integrate(0.0, scaled_q);
    return 6.0 * (MathFunctions::Bessel_J1c(scaled_q) - integral / scaled_q / scaled_q / scaled_q);
}

double FTDistribution2DCone::coneIntegrand2(double value) const
{
    return value * value * MathFunctions::Bessel_J0(value);
}


FTDistribution2DVoigt::FTDistribution2DVoigt(
    double coherence_length_x, double coherence_length_y, double eta, double gamma, double delta)
    : IFTDistribution2D(coherence_length_x, coherence_length_y, gamma, delta), m_eta(eta)
{
    setName(BornAgain::FTDistribution2DVoigtType);
    registerParameter(BornAgain::CoherenceLengthX, &m_coherence_length_x)
        .setUnit("nm")
        .setNonnegative();
    registerParameter(BornAgain::CoherenceLengthY, &m_coherence_length_y)
        .setUnit("nm")
        .setNonnegative();
    registerParameter(BornAgain::Eta, &m_eta);
    registerParameter("Gamma", &m_gamma).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
    registerParameter("Delta", &m_delta).setUnit("rad").setLimited(0, M_PI);
}

double FTDistribution2DVoigt::evaluate(double qx, double qy) const
{
    double sum_sq = sumsq(qx, qy);
    return m_eta * std::exp(-sum_sq / 2) + (1.0 - m_eta) * std::pow(1.0 + sum_sq, -1.5);
}
