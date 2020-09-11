// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleCoreShell.cpp
//! @brief     Implements class ParticleCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Particle/FormFactorCoreShell.h"
#include "Core/Particle/Particle.h"

ParticleCoreShell::ParticleCoreShell(const Particle& shell, const Particle& core,
                                     kvector_t relative_core_position)
{
    setName("ParticleCoreShell");
    registerParticleProperties();
    addAndRegisterCore(core, relative_core_position);
    addAndRegisterShell(shell);
}

ParticleCoreShell::~ParticleCoreShell() {}

ParticleCoreShell* ParticleCoreShell::clone() const
{
    ParticleCoreShell* p_result = new ParticleCoreShell(*mp_shell, *mp_core);
    p_result->setAbundance(m_abundance);
    if (mP_rotation.get())
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

SlicedParticle ParticleCoreShell::createSlicedParticle(ZLimits limits) const
{
    if (!mp_core || !mp_shell)
        return {};
    std::unique_ptr<IRotation> P_rotation(IRotation::createIdentity());
    if (mP_rotation)
        P_rotation.reset(mP_rotation->clone());

    // core
    std::unique_ptr<Particle> P_core(mp_core->clone());
    P_core->rotate(*P_rotation);
    P_core->translate(m_position);
    auto sliced_core = P_core->createSlicedParticle(limits);

    // shell
    std::unique_ptr<Particle> P_shell(mp_shell->clone());
    P_shell->rotate(*P_rotation);
    P_shell->translate(m_position);
    auto sliced_shell = P_shell->createSlicedParticle(limits);
    if (!sliced_shell.mP_slicedff)
        return {};

    SlicedParticle result;
    // if core out of limits, return sliced shell
    if (!sliced_core.mP_slicedff) {
        result.mP_slicedff.reset(sliced_shell.mP_slicedff.release());
        result.m_regions.push_back(sliced_shell.m_regions.back());
        return result;
    }

    // set core ambient material
    if (sliced_shell.m_regions.size() != 1)
        return {};
    auto shell_material = sliced_shell.m_regions[0].m_material;
    sliced_core.mP_slicedff->setAmbientMaterial(shell_material);

    // construct sliced particle
    sliced_shell.m_regions.back().m_volume -= sliced_core.m_regions.back().m_volume;
    result.mP_slicedff.reset(new FormFactorCoreShell(sliced_core.mP_slicedff.release(),
                                                     sliced_shell.mP_slicedff.release()));
    result.m_regions.push_back(sliced_core.m_regions.back());
    result.m_regions.push_back(sliced_shell.m_regions.back());

    return result;
}

std::vector<const INode*> ParticleCoreShell::getChildren() const
{
    return std::vector<const INode*>() << IParticle::getChildren() << mp_core << mp_shell;
}

void ParticleCoreShell::addAndRegisterCore(const Particle& core, kvector_t relative_core_position)
{
    mp_core.reset(core.clone());
    mp_core->translate(relative_core_position);
    registerChild(mp_core.get());
    mp_core->registerAbundance(false);
}

void ParticleCoreShell::addAndRegisterShell(const Particle& shell)
{
    mp_shell.reset(shell.clone());
    registerChild(mp_shell.get());
    mp_shell->registerAbundance(false);
    mp_shell->registerPosition(false);
}

ParticleCoreShell::ParticleCoreShell() : mp_shell{nullptr}, mp_core{nullptr}
{
    setName("ParticleCoreShell");
}
