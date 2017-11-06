// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorMaterial.cpp
//! @brief     Implements class FormFactorDecoratorMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorMaterial.h"
#include "BornAgainNamespace.h"
#include "MaterialFactoryFuncs.h"
#include "MathConstants.h"
#include "WavevectorInfo.h"

FormFactorDecoratorMaterial::FormFactorDecoratorMaterial(const IFormFactor& form_factor)
    : IFormFactorDecorator(form_factor)
    , m_material(createVacuumMaterial())
    , m_ambient_material(createVacuumMaterial())
{
    setName(BornAgain::FormFactorDecoratorMaterialType);
}

FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial()
{}

FormFactorDecoratorMaterial* FormFactorDecoratorMaterial::clone() const
{
    std::unique_ptr<FormFactorDecoratorMaterial> P_result(
                new FormFactorDecoratorMaterial(*mp_form_factor));
    P_result->setMaterial(m_material);
    P_result->setAmbientMaterial(m_ambient_material);
    return P_result.release();
}

void FormFactorDecoratorMaterial::setMaterial(Material material)
{
    m_material = std::move(material);
}

void FormFactorDecoratorMaterial::setAmbientMaterial(Material material)
{
    m_ambient_material = std::move(material);
}

complex_t FormFactorDecoratorMaterial::evaluate(const WavevectorInfo& wavevectors) const
{
    return getRefractiveIndexFactor(wavevectors)*mp_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const WavevectorInfo& wavevectors) const
{
    // the conjugated linear part of time reversal operator T
    // (T=UK with K complex conjugate operator and U is linear)
    Eigen::Matrix2cd time_reverse_conj = Eigen::Matrix2cd::Zero();
    time_reverse_conj(0, 1) = 1.0;
    time_reverse_conj(1, 0) = -1.0;
    // the interaction and time reversal taken together:
    Eigen::Matrix2cd V_eff = time_reverse_conj
                             * (  m_material.polarizedSubtrSLD(wavevectors)
                                - m_ambient_material.polarizedSubtrSLD(wavevectors) );
    return mp_form_factor->evaluate(wavevectors) * V_eff;
}

complex_t FormFactorDecoratorMaterial::getRefractiveIndexFactor(
        const WavevectorInfo& wavevectors) const
{
    return m_material.scalarSubtrSLD(wavevectors) - m_ambient_material.scalarSubtrSLD(wavevectors);
}
