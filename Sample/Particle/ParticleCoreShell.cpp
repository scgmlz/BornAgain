//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/ParticleCoreShell.cpp
//! @brief     Implements class ParticleCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Particle/ParticleCoreShell.h"
#include "Sample/Particle/FormFactorCoreShell.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/SlicedParticle.h"
#include "Sample/Scattering/Rotations.h"

ParticleCoreShell::ParticleCoreShell(const Particle& shell, const Particle& core,
                                     kvector_t relative_core_position) {
    setName("ParticleCoreShell");
    registerParticleProperties();
    addAndRegisterCore(core, relative_core_position);
    addAndRegisterShell(shell);
}

ParticleCoreShell::~ParticleCoreShell() = default;

ParticleCoreShell* ParticleCoreShell::clone() const {
    ParticleCoreShell* p_result = new ParticleCoreShell(*m_shell, *m_core);
    p_result->setAbundance(m_abundance);
    if (m_rotation)
        p_result->setRotation(*m_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

SlicedParticle ParticleCoreShell::createSlicedParticle(ZLimits limits) const {
    if (!m_core || !m_shell)
        return {};
    std::unique_ptr<IRotation> P_rotation(new IdentityRotation);
    if (m_rotation)
        P_rotation.reset(m_rotation->clone());

    // core
    std::unique_ptr<Particle> P_core(m_core->clone());
    P_core->rotate(*P_rotation);
    P_core->translate(m_position);
    auto sliced_core = P_core->createSlicedParticle(limits);

    // shell
    std::unique_ptr<Particle> P_shell(m_shell->clone());
    P_shell->rotate(*P_rotation);
    P_shell->translate(m_position);
    auto sliced_shell = P_shell->createSlicedParticle(limits);
    if (!sliced_shell.m_slicedff)
        return {};

    SlicedParticle result;
    // if core out of limits, return sliced shell
    if (!sliced_core.m_slicedff) {
        result.m_slicedff.reset(sliced_shell.m_slicedff.release());
        result.m_regions.push_back(sliced_shell.m_regions.back());
        return result;
    }

    // set core ambient material
    if (sliced_shell.m_regions.size() != 1)
        return {};
    auto shell_material = sliced_shell.m_regions[0].m_material;
    sliced_core.m_slicedff->setAmbientMaterial(shell_material);

    // construct sliced particle
    sliced_shell.m_regions.back().m_volume -= sliced_core.m_regions.back().m_volume;
    result.m_slicedff.reset(new FormFactorCoreShell(sliced_core.m_slicedff.release(),
                                                    sliced_shell.m_slicedff.release()));
    result.m_regions.push_back(sliced_core.m_regions.back());
    result.m_regions.push_back(sliced_shell.m_regions.back());

    return result;
}

std::vector<const INode*> ParticleCoreShell::getChildren() const {
    return std::vector<const INode*>() << IParticle::getChildren() << m_core << m_shell;
}

void ParticleCoreShell::addAndRegisterCore(const Particle& core, kvector_t relative_core_position) {
    m_core.reset(core.clone());
    m_core->translate(relative_core_position);
    registerChild(m_core.get());
    m_core->registerAbundance(false);
}

void ParticleCoreShell::addAndRegisterShell(const Particle& shell) {
    m_shell.reset(shell.clone());
    registerChild(m_shell.get());
    m_shell->registerAbundance(false);
    m_shell->registerPosition(false);
}

ParticleCoreShell::ParticleCoreShell() : m_shell{nullptr}, m_core{nullptr} {
    setName("ParticleCoreShell");
}
