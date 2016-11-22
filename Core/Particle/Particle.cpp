// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Particle.cpp
//! @brief     Implements class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Particle.h"
#include "BornAgainNamespace.h"
#include "FormFactorDecoratorPositionFactor.h"
#include "IMaterial.h"

Particle::Particle()
{
    initialize();
}

Particle::Particle(const IMaterial& p_material)
    : mP_material(p_material.clone())
{
    initialize();
}

Particle::Particle(const IMaterial& p_material, const IFormFactor& form_factor)
    : mP_material(p_material.clone())
    , mP_form_factor(form_factor.clone())
{
    initialize();
    registerChild(mP_form_factor.get());
}

Particle::Particle(const IMaterial& p_material, const IFormFactor& form_factor,
                   const IRotation& rotation)
    : mP_material(p_material.clone())
    , mP_form_factor(form_factor.clone())
{
    initialize();
    setRotation(rotation);
    registerChild(mP_form_factor.get());
}

Particle* Particle::clone() const
{
    Particle* p_result = new Particle();
    p_result->setAbundance(m_abundance);
    if (mP_form_factor)
        p_result->setFormFactor(*mP_form_factor);
    if (mP_material)
        p_result->setMaterial(*mP_material);
    if (mP_ambient_material)
        p_result->setAmbientMaterial(*mP_ambient_material);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);

    return p_result;
}

Particle* Particle::cloneInvertB() const
{
    Particle* p_result = new Particle();
    p_result->setAbundance(m_abundance);
    if (mP_form_factor)
        p_result->setFormFactor(*mP_form_factor);
    if (mP_material)
        p_result->mP_material.reset(mP_material->cloneInverted());
    if (mP_ambient_material)
        p_result->mP_ambient_material.reset(mP_ambient_material->cloneInverted());
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);

    return p_result;
}

std::string Particle::to_str(int indent) const
{
    std::stringstream ss;
    ss << std::string(4*indent, '.') << " " << getName() << " "
       << (getMaterial() ? getMaterial()->getName() : "0_MATERIAL") << " "
       << getRefractiveIndex() << "\n";
    for( const ISample* child: getChildren() )
        ss << child->to_str(indent+1);
    return ss.str();
}

void Particle::setAmbientMaterial(const IMaterial& material)
{
    if(mP_ambient_material.get() != &material)
        mP_ambient_material.reset(material.clone());
}

IFormFactor* Particle::createTransformedFormFactor(const IRotation* p_rotation,
                                                   kvector_t translation) const
{
    if (!mP_form_factor)
        return nullptr;
    const std::unique_ptr<IRotation> P_total_rotation(createComposedRotation(p_rotation));
    kvector_t total_position = getComposedTranslation(p_rotation, translation);
    std::unique_ptr<IFormFactor> P_temp_ff1;
    if (P_total_rotation)
        P_temp_ff1.reset(new FormFactorDecoratorRotation(*mP_form_factor, *P_total_rotation));
    else
        P_temp_ff1.reset(mP_form_factor->clone());
    std::unique_ptr<IFormFactor> P_temp_ff2;
    if (total_position != kvector_t())
        P_temp_ff2.reset(new FormFactorDecoratorPositionFactor(*P_temp_ff1, total_position));
    else
        P_temp_ff2.swap(P_temp_ff1);
    FormFactorDecoratorMaterial* p_ff = new FormFactorDecoratorMaterial(*P_temp_ff2);
    if (mP_material) {
        if (mP_rotation) {
            const std::unique_ptr<const IMaterial> P_transformed_material(
                mP_material->createTransformedMaterial(P_total_rotation->getTransform3D()));
            p_ff->setMaterial(*P_transformed_material);
        } else
            p_ff->setMaterial(*mP_material);
    }
    if (mP_ambient_material)
        p_ff->setAmbientMaterial(*mP_ambient_material);
    return p_ff;
}

void Particle::setMaterial(const IMaterial& material)
{
    if(mP_material.get() != &material)
        mP_material.reset(material.clone());
}

complex_t Particle::getRefractiveIndex() const
{
    return mP_material ? mP_material->getRefractiveIndex() : 0.0;
}

void Particle::setFormFactor(const IFormFactor& form_factor)
{
    if (&form_factor != mP_form_factor.get()) {
        if (mP_form_factor)
            deregisterChild(mP_form_factor.get());
        mP_form_factor.reset(form_factor.clone());
        registerChild(mP_form_factor.get());
    }
}

void Particle::initialize()
{
    setName(BornAgain::ParticleType);
    registerPosition();
}
