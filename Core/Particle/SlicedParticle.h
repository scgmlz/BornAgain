// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/SlicedParticle.h
//! @brief     Defines class SlicedParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SLICEDPARTICLE_H
#define SLICEDPARTICLE_H

#include "IFormFactor.h"
#include "HomogeneousRegion.h"
#include <memory>

//! Struct that contains information on a sliced particle.
//! This information is needed for evaluating the sliced form factor and the average of a material,
//! used in the Fresnel calculations.
//!
//! @ingroup intern

struct SlicedParticle
{
    std::unique_ptr<IFormFactor> mP_slicedff;
    std::vector<HomogeneousRegion> m_regions;
};

#endif // SLICEDPARTICLE_H
