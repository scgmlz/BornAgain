// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorPositionFactor.cpp
//! @brief     Implements class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorPositionFactor.h"
#include "BornAgainNamespace.h"
#include "ISampleVisitor.h"
#include "WavevectorInfo.h"

FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(
    const IFormFactor& form_factor, const kvector_t& position)
    : IFormFactorDecorator(form_factor), m_position(position)
{
    setName(BornAgain::FormFactorDecoratorPositionFactorType);
}

complex_t FormFactorDecoratorPositionFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    return getPositionFactor(wavevectors) * mp_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd
FormFactorDecoratorPositionFactor::evaluatePol(const WavevectorInfo& wavevectors) const
{
    return getPositionFactor(wavevectors) * mp_form_factor->evaluatePol(wavevectors);
}

complex_t
FormFactorDecoratorPositionFactor::getPositionFactor(const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    return exp_I(m_position.dot(q));
}
