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
#include "IMaterial.h"
#include "ISampleVisitor.h"
#include "MathConstants.h"
#include "WavevectorInfo.h"

FormFactorDecoratorMaterial::FormFactorDecoratorMaterial(const IFormFactor& form_factor)
    : FormFactorDecoratorFactor(form_factor, 1.0)
    , mP_material{ nullptr }
    , mP_ambient_material{ nullptr }
{
    setName(BornAgain::FormFactorDecoratorMaterialType);
}

FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial() {}

FormFactorDecoratorMaterial* FormFactorDecoratorMaterial::clone() const
{
    FormFactorDecoratorMaterial* result = new FormFactorDecoratorMaterial(*mp_form_factor);
    result->setMaterial(*mP_material);
    result->setAmbientMaterial(*mP_ambient_material);
    return result;
}

void FormFactorDecoratorMaterial::setMaterial(const IMaterial& material)
{
    if (mP_material.get() != &material)
        mP_material.reset(material.clone());
    m_factor = getRefractiveIndexFactor();
}

void FormFactorDecoratorMaterial::setAmbientMaterial(const IMaterial& material)
{
    if (mP_ambient_material.get() != &material)
        mP_ambient_material.reset(material.clone());
    m_factor = getRefractiveIndexFactor();
}

complex_t FormFactorDecoratorMaterial::getAmbientRefractiveIndex() const
{
    return mP_ambient_material ? mP_ambient_material->getRefractiveIndex() : 1.0;
}

Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const WavevectorInfo& wavevectors) const
{
    // the conjugated linear part of time reversal operator T
    // (T=UK with K complex conjugate operator and U is linear)
    Eigen::Matrix2cd time_reverse_conj = Eigen::Matrix2cd::Zero();
    time_reverse_conj(0, 1) = 1.0;
    time_reverse_conj(1, 0) = -1.0;
    // the interaction and time reversal taken together:
    double wavelength = wavevectors.getWavelength();
    double k_mag2 = 4.0 * M_PI * M_PI / wavelength / wavelength;
    Eigen::Matrix2cd V_eff =
        time_reverse_conj * (mP_material->getScatteringMatrix(k_mag2)
                             - mP_ambient_material->getScatteringMatrix(k_mag2));
    return mp_form_factor->evaluate(wavevectors) * V_eff;
}

complex_t FormFactorDecoratorMaterial::getRefractiveIndexFactor() const
{
    if (mP_material && mP_ambient_material) {
        complex_t particle_index = mP_material->getRefractiveIndex();
        complex_t ambient_index = mP_ambient_material->getRefractiveIndex();
        return particle_index * particle_index - ambient_index * ambient_index;
    } else
        return 1.0;
}
