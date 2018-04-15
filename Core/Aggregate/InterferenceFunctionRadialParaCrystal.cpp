// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionRadialParaCrystal.cpp
//! @brief     Implements class InterferenceFunctionRadialParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunctionRadialParaCrystal.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include <limits>

//! Constructor of interference function of radial paracrystal.
//! @param peak_distance: average distance to the next neighbor in nanometers
//! @param damping_length: the damping (coherence) length of the paracrystal in nanometers
InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal(
        double peak_distance, double damping_length)
    : m_peak_distance(peak_distance)
    , m_damping_length(damping_length)
    , m_use_damping_length(true)
    , m_kappa(0.0)
    , m_domain_size(0.0)
{
    setName(BornAgain::InterferenceFunctionRadialParaCrystalType);
    if (m_damping_length==0.0)
        m_use_damping_length = false;
    init_parameters();
}

void InterferenceFunctionRadialParaCrystal::init_parameters()
{
    registerParameter(BornAgain::PeakDistance, &m_peak_distance).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::DampingLength, &m_damping_length).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::SizeSpaceCoupling, &m_kappa).setNonnegative();
    registerParameter(BornAgain::DomainSize, &m_domain_size).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
}

InterferenceFunctionRadialParaCrystal* InterferenceFunctionRadialParaCrystal::clone() const {
    InterferenceFunctionRadialParaCrystal* result =
        new InterferenceFunctionRadialParaCrystal(
            m_peak_distance, m_damping_length);
    result->setDomainSize(domainSize());
    result->setKappa(m_kappa);
    if (mP_pdf)
        result->setProbabilityDistribution(*mP_pdf);
    return result;
}

//! Sets size spacing coupling parameter of the Size Spacing Correlation Approximation.
//! @param size spacing coupling parameter
void InterferenceFunctionRadialParaCrystal::setKappa(double kappa)
{
    m_kappa = kappa;
}

double InterferenceFunctionRadialParaCrystal::kappa() const
{
    return m_kappa;
}

//! Sets domain size (finite size corrections).
//! @param size: size of coherence domain along the lattice main axis in nanometers

void InterferenceFunctionRadialParaCrystal::setDomainSize(double size)
{
    m_domain_size = size;
}

double InterferenceFunctionRadialParaCrystal::evaluate(const kvector_t q) const
{
    if (!mP_pdf)
        throw Exceptions::NullPointerException("InterferenceFunctionRadialParaCrystal::"
                "evaluate() -> Error! Probability distribution for "
                "interference function not properly initialized");
    double result=0.0;
    double qxr = q.x();
    double qyr = q.y();
    double qpar = std::sqrt(qxr*qxr + qyr*qyr);
    int n = (int)std::abs(m_domain_size/m_peak_distance);
    double nd = (double)n;
    complex_t fp = FTPDF(qpar);
    if (n<1) {
        result = ((1.0 + fp)/(1.0 - fp)).real();
    } else {
        if (std::norm(1.0-fp) < std::numeric_limits<double>::epsilon() ) {
            result = nd;
        }
        // for (1-fp)*nd small, take the series expansion to second order in nd*(1-fp)
        else if (std::abs(1.0-fp)*nd < 2e-4) {
            complex_t intermediate = (nd-1.0)/2.0 + (nd*nd-1.0)*(fp-1.0)/6.0
                    + (nd*nd*nd-2.0*nd*nd-nd+2.0)*(fp-1.0)*(fp-1.0)/24.0;
            result = 1.0 + 2.0*intermediate.real();
        }
        else {
            complex_t tmp;
            if (std::abs(fp)==0.0
             || std::log(std::abs(fp))*nd < std::log(std::numeric_limits<double>::min())) {
                            tmp = 0.0;
            } else {
                tmp = std::pow(fp,n);
            }
            complex_t intermediate = fp/(1.0-fp) - fp*(1.0-tmp)/nd/(1.0-fp)/(1.0-fp);
            result = 1.0 + 2.0*intermediate.real();
        }
    }
    return result;
}

complex_t InterferenceFunctionRadialParaCrystal::FTPDF(double qpar) const
{
    complex_t phase = exp_I(qpar*m_peak_distance);
    double amplitude = mP_pdf->evaluate(qpar);
    complex_t result = phase*amplitude;
    if (m_use_damping_length)
        result *= std::exp(-m_peak_distance/m_damping_length);
    return result;
}

//! Sets one-dimensional probability distribution.
//! @param pdf: probability distribution (Fourier transform of probability density)

void InterferenceFunctionRadialParaCrystal::setProbabilityDistribution(const IFTDistribution1D &pdf)
{
    mP_pdf.reset(pdf.clone());
    registerChild(mP_pdf.get());
}

std::vector<const INode*> InterferenceFunctionRadialParaCrystal::getChildren() const
{
    return std::vector<const INode*>() << mP_pdf;
}
