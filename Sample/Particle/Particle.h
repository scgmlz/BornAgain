//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/Particle.h
//! @brief     Defines class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_PARTICLE_PARTICLE_H
#define BORNAGAIN_SAMPLE_PARTICLE_PARTICLE_H

#include "Sample/Material/Material.h"
#include "Sample/Particle/IParticle.h"

//! A particle with a form factor and refractive index.
//! @ingroup samples

class Particle : public IParticle {
public:
    Particle() = delete;
    ~Particle();
    Particle(Material material);
    Particle(Material material, const IFormFactor& form_factor);
    Particle(Material material, const IFormFactor& form_factor, const IRotation& rotation);

    Particle* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    SlicedParticle createSlicedParticle(ZLimits limits) const final;

    void setMaterial(Material material);
    const Material* material() const final { return &m_material; }

    std::vector<const INode*> getChildren() const final;

protected:
    Material m_material;
    std::unique_ptr<IFormFactor> m_form_factor;

private:
    void initialize();
    void setFormFactor(const IFormFactor& form_factor);
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_PARTICLE_H
