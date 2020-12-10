//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/FormFactorDecoratorRotation.cpp
//! @brief     Implements class FormFactorDecoratorRotation
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Scattering/FormFactorDecoratorRotation.h"
#include "Sample/Material/WavevectorInfo.h"
#include "Sample/Scattering/Rotations.h"
#include <memory>

FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor& ff,
                                                         const IRotation& rotation)
    : IFormFactorDecorator(ff) {
    setName("FormFactorDecoratorRotation");
    m_transform = rotation.getTransform3D();
}

FormFactorDecoratorRotation* FormFactorDecoratorRotation::clone() const {
    return new FormFactorDecoratorRotation(*m_ff, m_transform);
}

double FormFactorDecoratorRotation::bottomZ(const IRotation& rotation) const {
    Transform3D transform = rotation.getTransform3D();
    std::unique_ptr<IRotation> total_rotation(IRotation::createRotation(transform * m_transform));
    return m_ff->bottomZ(*total_rotation);
}

double FormFactorDecoratorRotation::topZ(const IRotation& rotation) const {
    Transform3D transform = rotation.getTransform3D();
    std::unique_ptr<IRotation> total_rotation(IRotation::createRotation(transform * m_transform));
    return m_ff->topZ(*total_rotation);
}

complex_t FormFactorDecoratorRotation::evaluate(const WavevectorInfo& wavevectors) const {
    return m_ff->evaluate(wavevectors.transformed(m_transform.getInverse()));
}

Eigen::Matrix2cd FormFactorDecoratorRotation::evaluatePol(const WavevectorInfo& wavevectors) const {
    return m_ff->evaluatePol(wavevectors.transformed(m_transform.getInverse()));
}

FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor& ff,
                                                         const Transform3D& transform)
    : IFormFactorDecorator(ff), m_transform(transform) {
    setName("FormFactorDecoratorRotation");
}
