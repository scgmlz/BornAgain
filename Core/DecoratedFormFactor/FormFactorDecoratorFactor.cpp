// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorFactor.cpp
//! @brief     Implements class FormFactorDecoratorFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorFactor.h"
#include "BornAgainNamespace.h"

FormFactorDecoratorFactor::FormFactorDecoratorFactor(
    const IFormFactor& form_factor, const complex_t factor)
    : IFormFactorDecorator(form_factor), m_factor(factor)
{
    setName(BornAgain::FormFactorDecoratorFactorType);
}

complex_t FormFactorDecoratorFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    return m_factor * mp_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorDecoratorFactor::evaluatePol(const WavevectorInfo& wavevectors) const
{
    return m_factor * mp_form_factor->evaluatePol(wavevectors);
}
