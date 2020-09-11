// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/FormFactorDecoratorRotation.cpp
//! @brief     Implements class FormFactorDecoratorRotation
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Scattering/FormFactorDecoratorRotation.h"
#include "Core/Vector/WavevectorInfo.h"
#include <memory>

FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor& form_factor,
                                                         const IRotation& rotation)
    : IFormFactorDecorator(form_factor)
{
    setName("FormFactorDecoratorRotation");
    m_transform = rotation.getTransform3D();
}

FormFactorDecoratorRotation* FormFactorDecoratorRotation::clone() const
{
    return new FormFactorDecoratorRotation(*mp_form_factor, m_transform);
}

double FormFactorDecoratorRotation::bottomZ(const IRotation& rotation) const
{
    Transform3D transform = rotation.getTransform3D();
    std::unique_ptr<IRotation> P_total_rotation(IRotation::createRotation(transform * m_transform));
    return mp_form_factor->bottomZ(*P_total_rotation);
}

double FormFactorDecoratorRotation::topZ(const IRotation& rotation) const
{
    Transform3D transform = rotation.getTransform3D();
    std::unique_ptr<IRotation> P_total_rotation(IRotation::createRotation(transform * m_transform));
    return mp_form_factor->topZ(*P_total_rotation);
}

complex_t FormFactorDecoratorRotation::evaluate(const WavevectorInfo& wavevectors) const
{
    return mp_form_factor->evaluate(wavevectors.transformed(m_transform.getInverse()));
}

Eigen::Matrix2cd FormFactorDecoratorRotation::evaluatePol(const WavevectorInfo& wavevectors) const
{
    return mp_form_factor->evaluatePol(wavevectors.transformed(m_transform.getInverse()));
}

FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor& form_factor,
                                                         const Transform3D& transform)
    : IFormFactorDecorator(form_factor), m_transform(transform)
{
    setName("FormFactorDecoratorRotation");
}
