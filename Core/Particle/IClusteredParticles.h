// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IClusteredParticles.h
//! @brief     Defines class IClusteredParticles.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_ICLUSTEREDPARTICLES_H
#define BORNAGAIN_CORE_PARTICLE_ICLUSTEREDPARTICLES_H

#include "Core/Particle/HomogeneousRegion.h"
#include "Core/Scattering/ISample.h"
#include "Core/Vector/Vectors3D.h"

class IFormFactor;
class IRotation;

//! An ordered assembly of particles. Currently, the only child class is Crystal.
//! @ingroup samples_internal

class IClusteredParticles : public ISample
{
public:
    IClusteredParticles* clone() const override = 0;

    //! Creates a total form factor for the mesocrystal with a specific shape and content
    //! The bulk content of the mesocrystal is encapsulated by the IClusteredParticles object itself
    virtual IFormFactor* createTotalFormFactor(const IFormFactor&, const IRotation*,
                                               const kvector_t& /*translation*/) const = 0;

    //! Creates region information with volumetric densities instead of absolute volume
    //! These densities need to be multiplied by the total mesocrystal volume
    virtual std::vector<HomogeneousRegion> homogeneousRegions() const = 0;
};

#endif // BORNAGAIN_CORE_PARTICLE_ICLUSTEREDPARTICLES_H
