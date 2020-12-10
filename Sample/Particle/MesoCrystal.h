//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/MesoCrystal.h
//! @brief     Defines class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_PARTICLE_MESOCRYSTAL_H
#define BORNAGAIN_SAMPLE_PARTICLE_MESOCRYSTAL_H

#include "Sample/Particle/IParticle.h"

class Crystal;

//! A particle with an internal structure of smaller particles.
//! @ingroup samples

class MesoCrystal : public IParticle {
public:
    MesoCrystal(const Crystal& particle_structure, const IFormFactor& form_factor);

    ~MesoCrystal();
    MesoCrystal* clone() const final;

    void accept(INodeVisitor* visitor) const final;

    SlicedParticle createSlicedParticle(ZLimits limits) const final;

    std::vector<const INode*> getChildren() const final;

private:
    MesoCrystal(Crystal* p_particle_structure, IFormFactor* p_form_factor);
    void initialize();

    std::unique_ptr<Crystal> m_particle_structure;   //!< Crystal  structure
    std::unique_ptr<IFormFactor> m_meso_form_factor; //!< Outer shape of this mesocrystal
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_MESOCRYSTAL_H
