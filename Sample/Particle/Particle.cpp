//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/Particle.cpp
//! @brief     Implements class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Particle/Particle.h"
#include "Base/Vector/Transform3D.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Particle/SlicedParticle.h"
#include "Sample/Scattering/FormFactorDecoratorMaterial.h"
#include "Sample/Scattering/FormFactorDecoratorPositionFactor.h"
#include "Sample/Scattering/Rotations.h"

Particle::~Particle() = default;

Particle::Particle(Material material) : m_material(std::move(material)) {
    initialize();
}

Particle::Particle(Material material, const IFormFactor& form_factor)
    : m_material(std::move(material)), m_form_factor(form_factor.clone()) {
    initialize();
    registerChild(m_form_factor.get());
}

Particle::Particle(Material material, const IFormFactor& form_factor, const IRotation& rotation)
    : m_material(std::move(material)), m_form_factor(form_factor.clone()) {
    initialize();
    setRotation(rotation);
    registerChild(m_form_factor.get());
}

Particle* Particle::clone() const {
    Particle* p_result = new Particle(m_material);
    p_result->setAbundance(m_abundance);
    if (m_form_factor)
        p_result->setFormFactor(*m_form_factor);
    if (m_rotation)
        p_result->setRotation(*m_rotation);
    p_result->setPosition(m_position);

    return p_result;
}

SlicedParticle Particle::createSlicedParticle(ZLimits limits) const {
    if (!m_form_factor)
        return {};
    std::unique_ptr<IRotation> P_rotation(new IdentityRotation);
    if (m_rotation)
        P_rotation.reset(m_rotation->clone());
    std::unique_ptr<IFormFactor> P_tem_ff(
        m_form_factor->createSlicedFormFactor(limits, *P_rotation, m_position));
    if (!P_tem_ff)
        return {};
    std::unique_ptr<FormFactorDecoratorMaterial> P_ff(new FormFactorDecoratorMaterial(*P_tem_ff));
    double volume = P_tem_ff->volume();
    Material transformed_material(m_material.rotatedMaterial(P_rotation->getTransform3D()));
    P_ff->setMaterial(transformed_material);
    SlicedParticle result;
    result.m_regions.push_back({volume, transformed_material});
    result.m_slicedff = std::move(P_ff);
    return result;
}

void Particle::setMaterial(Material material) {
    m_material = std::move(material);
}

void Particle::setFormFactor(const IFormFactor& form_factor) {
    if (&form_factor != m_form_factor.get()) {
        m_form_factor.reset(form_factor.clone());
        registerChild(m_form_factor.get());
    }
}

std::vector<const INode*> Particle::getChildren() const {
    return std::vector<const INode*>() << IParticle::getChildren() << m_form_factor;
}

void Particle::initialize() {
    setName("Particle");
    registerParticleProperties();
}
