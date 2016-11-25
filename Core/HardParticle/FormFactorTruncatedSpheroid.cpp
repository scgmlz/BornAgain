// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedSpheroid.cpp
//! @brief     Implements class FormFactorTruncatedSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTruncatedSpheroid.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"
#include <limits>

FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(
    double radius, double height, double height_flattening)
    : m_radius(radius), m_height(height), m_height_flattening(height_flattening)
{
    setName(BornAgain::FFTruncatedSpheroidType);
    check_initialization();
    registerParameter(BornAgain::Radius, &m_radius).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::HeightFlattening, &m_height_flattening).setNonnegative();
    mP_integrator = make_integrator_complex(this, &FormFactorTruncatedSpheroid::Integrand);
}

bool FormFactorTruncatedSpheroid::check_initialization() const
{
    bool result(true);
    if (m_height > 2. * m_radius * m_height_flattening) {
        std::ostringstream ostr;
        ostr << "::FormFactorTruncatedSphere() -> Error in class initialization with parameters ";
        ostr << " radius:" << m_radius;
        ostr << " height:" << m_height;
        ostr << " height_flattening:" << m_height_flattening << "\n\n";
        ostr << "Check for 'height <= 2.*radius*height_flattening' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

//! Integrand for complex formfactor.
complex_t FormFactorTruncatedSpheroid::Integrand(double Z) const
{
    double R = m_radius;
    double fp = m_height_flattening;

    double Rz = std::sqrt(R * R - Z * Z / (fp * fp));
    complex_t qrRz = std::sqrt(m_q.x() * m_q.x() + m_q.y() * m_q.y()) * Rz;
    complex_t J1_qrRz_div_qrRz = MathFunctions::Bessel_J1c(qrRz);

    return Rz * Rz * J1_qrRz_div_qrRz * std::exp(complex_t(0.0, 1.0) * m_q.z() * Z);
}

complex_t FormFactorTruncatedSpheroid::evaluate_for_q(const cvector_t q) const
{
    double H = m_height;
    double R = m_radius;
    double fp = m_height_flattening;
    m_q = q;

    if (std::abs(m_q.mag()) <= std::numeric_limits<double>::epsilon())
        return M_PI * R * H * H / fp * (1. - H / (3. * fp * R));
    complex_t z_part = std::exp(complex_t(0.0, 1.0) * m_q.z() * (H - fp * R));
    return M_TWOPI * z_part * mP_integrator->integrate(fp * R - H, fp * R);
}
