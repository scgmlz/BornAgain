// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorGauss.cpp
//! @brief     Implements class FormFactorGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorGauss.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include <limits>

FormFactorGauss::FormFactorGauss(double length) : FormFactorGauss(length, length) {}

FormFactorGauss::FormFactorGauss(double width, double height)
{
    m_width = width;
    m_height = height;
    setName(BornAgain::FFGaussType);
    registerParameter(BornAgain::Width, &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    m_max_ql = std::sqrt(-4 * M_PI * std::log(std::numeric_limits<double>::min()) / 3);
}

complex_t FormFactorGauss::evaluate_for_q(const cvector_t q) const
{
    complex_t qzHdiv2 = m_height * q.z() / 2.0;
    double qzh = q.z().real() * m_height;
    if (std::abs(qzh) > m_max_ql)
        return 0.0;
    double qxr = q.x().real() * m_width;
    if (std::abs(qxr) > m_max_ql)
        return 0.0;
    double qyr = q.y().real() * m_width;
    if (std::abs(qyr) > m_max_ql)
        return 0.0;

    return exp_I(qzHdiv2) * m_height * m_width * m_width
        * std::exp(-(qxr * qxr + qyr * qyr + qzh * qzh) / 4.0 / M_PI);
}
