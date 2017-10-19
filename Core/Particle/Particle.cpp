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
#include "HomogeneousMaterial.h"

Particle::Particle()
{
    initialize();
}

Particle::Particle(HomogeneousMaterial material)
    : m_material(material)
{
    initialize();
}

Particle::Particle(HomogeneousMaterial material, const IFormFactor& form_factor)
    : m_material(material)
    , mP_form_factor(form_factor.clone())
{
    initialize();
    registerChild(mP_form_factor.get());
}

Particle::Particle(HomogeneousMaterial material, const IFormFactor& form_factor,
                   const IRotation& rotation)
    : m_material(material)
    , mP_form_factor(form_factor.clone())
{
    initialize();
    setRotation(rotation);
    registerChild(mP_form_factor.get());
}

Particle* Particle::clone() const
{
    Particle* p_result = new Particle(m_material);
    p_result->setAbundance(m_abundance);
    if (mP_form_factor)
        p_result->setFormFactor(*mP_form_factor);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);

    return p_result;
}

SlicedParticle Particle::createSlicedParticle(ZLimits limits) const
{
    if (!mP_form_factor)
        return {};
    std::unique_ptr<IRotation> P_rotation(IRotation::createIdentity());
    if (mP_rotation)
        P_rotation.reset(mP_rotation->clone());
    std::unique_ptr<IFormFactor> P_temp_ff(
                mP_form_factor->createSlicedFormFactor(limits, *P_rotation, m_position));
    std::unique_ptr<FormFactorDecoratorMaterial> P_ff(new FormFactorDecoratorMaterial(*P_temp_ff));
    double volume = P_temp_ff->volume();
    std::unique_ptr<HomogeneousMaterial> transformed_material(
                m_material.transformedMaterial(P_rotation->getTransform3D()));
    P_ff->setMaterial(*transformed_material);
    SlicedParticle result;
    result.m_regions.push_back( { volume, *transformed_material } );
    result.mP_slicedff = std::move(P_ff);
    return result;
}

void Particle::setMaterial(HomogeneousMaterial material)
{
    m_material = std::move(material);
}

complex_t Particle::refractiveIndex() const
{
    return m_material.refractiveIndex();
}

void Particle::setFormFactor(const IFormFactor& form_factor)
{
    if (&form_factor != mP_form_factor.get()) {
        mP_form_factor.reset(form_factor.clone());
        registerChild(mP_form_factor.get());
    }
}

std::vector<const INode*> Particle::getChildren() const
{
    return std::vector<const INode*>() << IParticle::getChildren() << mP_form_factor;
}

void Particle::initialize()
{
    setName(BornAgain::ParticleType);
    registerParticleProperties();
}
