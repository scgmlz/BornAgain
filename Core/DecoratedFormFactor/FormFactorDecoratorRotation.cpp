// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorRotation.cpp
//! @brief     Implements class FormFactorDecoratorRotation
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorRotation.h"
#include "BornAgainNamespace.h"
#include "ISampleVisitor.h"
#include "WavevectorInfo.h"
#include <memory>

FormFactorDecoratorRotation::FormFactorDecoratorRotation(
    const IFormFactor& form_factor, const IRotation& rotation)
    : IFormFactorDecorator(form_factor)
{
    setName(BornAgain::FormFactorDecoratorRotationType);
    m_transform = rotation.getTransform3D();
}

FormFactorDecoratorRotation* FormFactorDecoratorRotation::clone() const
{
    return new FormFactorDecoratorRotation(*mp_form_factor, m_transform);
}

complex_t FormFactorDecoratorRotation::evaluate(const WavevectorInfo& wavevectors) const
{
    WavevectorInfo rotated_wavevectors = rotate_wavevectors(wavevectors);
    return mp_form_factor->evaluate(rotated_wavevectors);
}

Eigen::Matrix2cd FormFactorDecoratorRotation::evaluatePol(const WavevectorInfo& wavevectors) const
{
    WavevectorInfo rotated_wavevectors = rotate_wavevectors(wavevectors);
    return mp_form_factor->evaluatePol(rotated_wavevectors);
}

FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor& form_factor,
                                                         const Transform3D& transform)
    : IFormFactorDecorator(form_factor)
{
    setName(BornAgain::FormFactorDecoratorRotationType);
    m_transform = transform;
}

WavevectorInfo FormFactorDecoratorRotation::rotate_wavevectors(
        const WavevectorInfo& wavevectors) const
{
    cvector_t rotated_ki = m_transform.transformedInverse(wavevectors.getKi());
    cvector_t rotated_kf = m_transform.transformedInverse(wavevectors.getKf());
    double wavelength = wavevectors.getWavelength();
    return WavevectorInfo(rotated_ki, rotated_kf, wavelength);
}
