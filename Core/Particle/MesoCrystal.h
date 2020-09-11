// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/MesoCrystal.h
//! @brief     Defines class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_MESOCRYSTAL_H
#define BORNAGAIN_CORE_PARTICLE_MESOCRYSTAL_H

#include "Core/Particle/IParticle.h"

class IClusteredParticles;

//! A particle with an internal structure of smaller particles.
//! @ingroup samples

class BA_CORE_API_ MesoCrystal : public IParticle
{
public:
    MesoCrystal(const IClusteredParticles& particle_structure, const IFormFactor& form_factor);

    ~MesoCrystal();
    MesoCrystal* clone() const override final;

    void accept(INodeVisitor* visitor) const override final;

    SlicedParticle createSlicedParticle(ZLimits limits) const override final;

    std::vector<const INode*> getChildren() const override final;

private:
    MesoCrystal(IClusteredParticles* p_particle_structure, IFormFactor* p_form_factor);
    void initialize();

    std::unique_ptr<IClusteredParticles> mp_particle_structure; //!< Crystal  structure
    std::unique_ptr<IFormFactor> mp_meso_form_factor;           //!< Outer shape of this mesocrystal
};

#endif // BORNAGAIN_CORE_PARTICLE_MESOCRYSTAL_H
