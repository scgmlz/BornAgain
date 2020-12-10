//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/ParticleCoreShell.h
//! @brief     Defines ParticleCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_PARTICLE_PARTICLECORESHELL_H
#define BORNAGAIN_SAMPLE_PARTICLE_PARTICLECORESHELL_H

#include "Sample/Particle/IParticle.h"

class Particle;

//! A particle with a core/shell geometry.
//! @ingroup samples

class ParticleCoreShell : public IParticle {
public:
    ParticleCoreShell(const Particle& shell, const Particle& core,
                      kvector_t relative_core_position = kvector_t(0.0, 0.0, 0.0));
    ~ParticleCoreShell();

    ParticleCoreShell* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    SlicedParticle createSlicedParticle(ZLimits limits) const final;

    const Particle* coreParticle() const;

    const Particle* shellParticle() const;

    std::vector<const INode*> getChildren() const final;

protected:
    void addAndRegisterCore(const Particle& core, kvector_t relative_core_position);
    void addAndRegisterShell(const Particle& shell);
    ParticleCoreShell();

    std::unique_ptr<Particle> m_shell;
    std::unique_ptr<Particle> m_core;
};

inline const Particle* ParticleCoreShell::coreParticle() const {
    return m_core.get();
}

inline const Particle* ParticleCoreShell::shellParticle() const {
    return m_shell.get();
}

#endif // BORNAGAIN_SAMPLE_PARTICLE_PARTICLECORESHELL_H
