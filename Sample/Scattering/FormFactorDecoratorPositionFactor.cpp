//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/FormFactorDecoratorPositionFactor.cpp
//! @brief     Implements class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Scattering/FormFactorDecoratorPositionFactor.h"
#include "Sample/Material/WavevectorInfo.h"
#include "Sample/Scattering/Rotations.h"

FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(const IFormFactor& ff,
                                                                     const kvector_t& position)
    : IFormFactorDecorator(ff), m_position(position) {
    setName("FormFactorDecoratorPositionFactor");
}

double FormFactorDecoratorPositionFactor::bottomZ(const IRotation& rotation) const {
    kvector_t rotated_translation = rotation.transformed(m_position);
    return m_ff->bottomZ(rotation) + rotated_translation.z();
}

double FormFactorDecoratorPositionFactor::topZ(const IRotation& rotation) const {
    kvector_t rotated_translation = rotation.transformed(m_position);
    return m_ff->topZ(rotation) + rotated_translation.z();
}

complex_t FormFactorDecoratorPositionFactor::evaluate(const WavevectorInfo& wavevectors) const {
    return getPositionFactor(wavevectors) * m_ff->evaluate(wavevectors);
}

Eigen::Matrix2cd
FormFactorDecoratorPositionFactor::evaluatePol(const WavevectorInfo& wavevectors) const {
    return getPositionFactor(wavevectors) * m_ff->evaluatePol(wavevectors);
}

complex_t
FormFactorDecoratorPositionFactor::getPositionFactor(const WavevectorInfo& wavevectors) const {
    cvector_t q = wavevectors.getQ();
    return exp_I(m_position.dot(q));
}
