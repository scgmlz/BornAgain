// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Particle.h
//! @brief     Defines class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_PARTICLE_H
#define BORNAGAIN_CORE_PARTICLE_PARTICLE_H

#include "Core/Material/Material.h"
#include "Core/Particle/IParticle.h"
#include "Core/Scattering/FormFactorDecoratorMaterial.h"
#include "Core/Scattering/FormFactorDecoratorRotation.h"

//! A particle with a form factor and refractive index.
//! @ingroup samples

class BA_CORE_API_ Particle : public IParticle
{
public:
    Particle();
    Particle(Material material);
    Particle(Material material, const IFormFactor& form_factor);
    Particle(Material material, const IFormFactor& form_factor, const IRotation& rotation);

    Particle* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    SlicedParticle createSlicedParticle(ZLimits limits) const override final;

    void setMaterial(Material material);
    const Material* material() const override final { return &m_material; }

    void setFormFactor(const IFormFactor& form_factor);

    std::vector<const INode*> getChildren() const override final;

protected:
    Material m_material;
    std::unique_ptr<IFormFactor> mP_form_factor;

private:
    void initialize();
};

#endif // BORNAGAIN_CORE_PARTICLE_PARTICLE_H
