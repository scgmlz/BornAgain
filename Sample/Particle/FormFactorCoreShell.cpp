//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/FormFactorCoreShell.cpp
//! @brief     Implements class FormFactorCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Particle/FormFactorCoreShell.h"

FormFactorCoreShell::FormFactorCoreShell(IFormFactor* core, IFormFactor* shell)
    : m_core(core), m_shell(shell) {
    setName("FormFactorCoreShell");
}

FormFactorCoreShell::~FormFactorCoreShell() = default;

FormFactorCoreShell* FormFactorCoreShell::clone() const {
    return new FormFactorCoreShell(m_core->clone(), m_shell->clone());
}

double FormFactorCoreShell::radialExtension() const {
    return m_shell->radialExtension();
}

double FormFactorCoreShell::bottomZ(const IRotation& rotation) const {
    return m_shell->bottomZ(rotation);
}

double FormFactorCoreShell::topZ(const IRotation& rotation) const {
    return m_shell->topZ(rotation);
}

void FormFactorCoreShell::setAmbientMaterial(const Material& material) {
    m_shell->setAmbientMaterial(material);
}

complex_t FormFactorCoreShell::evaluate(const WavevectorInfo& wavevectors) const {
    return m_shell->evaluate(wavevectors) + m_core->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorCoreShell::evaluatePol(const WavevectorInfo& wavevectors) const {
    return m_shell->evaluatePol(wavevectors) + m_core->evaluatePol(wavevectors);
}
