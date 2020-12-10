//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/MesoCrystal.cpp
//! @brief     Implements class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Particle/MesoCrystal.h"
#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/SlicedParticle.h"
#include "Sample/Scattering/FormFactorDecoratorPositionFactor.h"
#include "Sample/Scattering/FormFactorDecoratorRotation.h"
#include "Sample/Scattering/Rotations.h"

MesoCrystal::MesoCrystal(const Crystal& particle_structure, const IFormFactor& form_factor)
    : m_particle_structure(particle_structure.clone()), m_meso_form_factor(form_factor.clone()) {
    initialize();
}

MesoCrystal::~MesoCrystal() = default;

MesoCrystal* MesoCrystal::clone() const {
    MesoCrystal* p_result =
        new MesoCrystal(m_particle_structure->clone(), m_meso_form_factor->clone());
    p_result->setAbundance(m_abundance);
    if (m_rotation)
        p_result->setRotation(*m_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

void MesoCrystal::accept(INodeVisitor* visitor) const {
    visitor->visit(this);
}

SlicedParticle MesoCrystal::createSlicedParticle(ZLimits limits) const {
    if (!m_particle_structure || !m_meso_form_factor)
        return {};
    std::unique_ptr<IRotation> rotation(new IdentityRotation);
    if (m_rotation)
        rotation.reset(m_rotation->clone());
    std::unique_ptr<IFormFactor> tem_ff(
        m_meso_form_factor->createSlicedFormFactor(limits, *rotation, m_position));
    std::unique_ptr<IFormFactor> total_ff(
        m_particle_structure->createTotalFormFactor(*tem_ff, rotation.get(), m_position));
    double meso_volume = m_meso_form_factor->volume();
    auto regions = m_particle_structure->homogeneousRegions();
    for (auto& region : regions)
        region.m_volume *= meso_volume;
    SlicedParticle result;
    result.m_slicedff = std::move(total_ff);
    result.m_regions = regions;
    return result;
}

std::vector<const INode*> MesoCrystal::getChildren() const {
    return std::vector<const INode*>()
           << IParticle::getChildren() << m_particle_structure << m_meso_form_factor;
}

MesoCrystal::MesoCrystal(Crystal* particle_structure, IFormFactor* form_factor)
    : m_particle_structure(particle_structure), m_meso_form_factor(form_factor) {
    initialize();
}

void MesoCrystal::initialize() {
    setName("MesoCrystal");
    registerParticleProperties();
    registerChild(m_particle_structure.get());
    registerChild(m_meso_form_factor.get());
}
