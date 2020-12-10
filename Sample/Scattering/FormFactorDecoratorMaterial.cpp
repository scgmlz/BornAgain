//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/FormFactorDecoratorMaterial.cpp
//! @brief     Implements class FormFactorDecoratorMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Scattering/FormFactorDecoratorMaterial.h"
#include "Base/Math/Constants.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Material/WavevectorInfo.h"

FormFactorDecoratorMaterial::FormFactorDecoratorMaterial(const IFormFactor& ff)
    : IFormFactorDecorator(ff)
    , m_material(HomogeneousMaterial())
    , m_ambient_material(HomogeneousMaterial()) {
    setName("FormFactorDecoratorMaterial");
}

FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial() = default;

FormFactorDecoratorMaterial* FormFactorDecoratorMaterial::clone() const {
    auto* result = new FormFactorDecoratorMaterial(*m_ff);
    result->setMaterial(m_material);
    result->setAmbientMaterial(m_ambient_material);
    return result;
}

void FormFactorDecoratorMaterial::setMaterial(const Material& material) {
    m_material = material;
}

void FormFactorDecoratorMaterial::setAmbientMaterial(const Material& material) {
    m_ambient_material = material;
}

complex_t FormFactorDecoratorMaterial::evaluate(const WavevectorInfo& wavevectors) const {
    return getRefractiveIndexFactor(wavevectors) * m_ff->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const WavevectorInfo& wavevectors) const {
    // the conjugated linear part of time reversal operator T
    // (T=UK with K complex conjugate operator and U is linear)
    Eigen::Matrix2cd time_reverse_conj = Eigen::Matrix2cd::Zero();
    time_reverse_conj(0, 1) = 1.0;
    time_reverse_conj(1, 0) = -1.0;
    // the interaction and time reversal taken together:
    Eigen::Matrix2cd V_eff = time_reverse_conj
                             * (m_material.polarizedSubtrSLD(wavevectors)
                                - m_ambient_material.polarizedSubtrSLD(wavevectors));
    return m_ff->evaluate(wavevectors) * V_eff;
}

complex_t
FormFactorDecoratorMaterial::getRefractiveIndexFactor(const WavevectorInfo& wavevectors) const {
    return m_material.scalarSubtrSLD(wavevectors) - m_ambient_material.scalarSubtrSLD(wavevectors);
}
