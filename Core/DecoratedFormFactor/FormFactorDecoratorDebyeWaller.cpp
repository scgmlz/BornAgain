// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorDebyeWaller.cpp
//! @brief     Implements class FormFactorDecoratorDebyeWaller.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorDebyeWaller.h"
#include "BornAgainNamespace.h"
#include "ISampleVisitor.h"
#include "RealParameter.h"
#include "WavevectorInfo.h"

FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(
    const IFormFactor& form_factor, double dw_h_factor, double dw_r_factor)
    : IFormFactorDecorator(form_factor), m_h_dw_factor(dw_h_factor), m_r_dw_factor(dw_r_factor)
{
    setName(BornAgain::FormFactorDecoratorDebyeWallerType);
    registerParameter(BornAgain::HeightDWFactor, &m_h_dw_factor).setPositive();
    registerParameter(BornAgain::RadiusDWFactor, &m_r_dw_factor).setPositive();
}

FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(
    const IFormFactor& form_factor, double dw_factor)
    : IFormFactorDecorator(form_factor), m_h_dw_factor(dw_factor), m_r_dw_factor(dw_factor)
{
    setName(BornAgain::FormFactorDecoratorDebyeWallerType);
    registerParameter(BornAgain::HeightDWFactor, &m_h_dw_factor).setPositive();
    registerParameter(BornAgain::RadiusDWFactor, &m_r_dw_factor).setPositive();
}

complex_t FormFactorDecoratorDebyeWaller::evaluate(const WavevectorInfo& wavevectors) const
{
    double dw = getDWFactor(wavevectors);
    return dw * mp_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd
FormFactorDecoratorDebyeWaller::evaluatePol(const WavevectorInfo& wavevectors) const
{
    double dw = getDWFactor(wavevectors);
    return dw * mp_form_factor->evaluatePol(wavevectors);
}

double FormFactorDecoratorDebyeWaller::getDWFactor(const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    double qr2 = std::norm(q.x()) + std::norm(q.y());
    double qz2 = std::norm(q.z());
    double dw = std::exp(-qz2 * m_h_dw_factor - qr2 * m_r_dw_factor);
    return dw;
}
