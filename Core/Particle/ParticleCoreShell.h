// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleCoreShell.h
//! @brief     Defines ParticleCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECORESHELL_H
#define PARTICLECORESHELL_H

#include "IParticle.h"

class IMaterial;
class Particle;

//! A particle with a core/shell geometry.
//! @ingroup samples

class BA_CORE_API_ ParticleCoreShell : public IParticle
{
public:
    ParticleCoreShell(const Particle& shell, const Particle& core,
                      kvector_t relative_core_position=kvector_t(0.0, 0.0, 0.0));
    virtual ~ParticleCoreShell();

    ParticleCoreShell* clone() const final;
    ParticleCoreShell* cloneInvertB() const final;

    //! Calls the ISampleVisitor's visit method
    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences its scattering power)
    void setAmbientMaterial(const IMaterial& material) final;
    const IMaterial* getAmbientMaterial() const final;

    //! Create a form factor for this particle with an extra scattering factor
    IFormFactor* createTransformedFormFactor(
        const IRotation* p_rotation, kvector_t translation) const final;

    //! Returns the core particle
    const Particle* getCoreParticle() const { return mp_core; }

    //! Returns the shell particle
    const Particle* getShellParticle() const { return mp_shell; }

protected:
    void addAndRegisterCore(const Particle &core, kvector_t relative_core_position);
    void addAndRegisterShell(const Particle &shell);

    ParticleCoreShell();
    Particle* mp_shell;
    Particle* mp_core;
};

#endif // PARTICLECORESHELL_H
