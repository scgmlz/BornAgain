// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/HomogeneousRegion.h
//! @brief     Defines struct HomogeneousRegion, and declares fct CreateAveragedMaterial
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_HOMOGENEOUSREGION_H
#define BORNAGAIN_CORE_PARTICLE_HOMOGENEOUSREGION_H

#include "Core/Material/Material.h"

//! Struct that contains information on a single homogeneous region of a particle inside
//! a single layer.
//! This information is needed for calculating the average of a material, used in the Fresnel
//! calculations.
//!
//! @ingroup intern

struct HomogeneousRegion {
    double m_volume;
    Material m_material;
};

#ifndef SWIG

//! @ingroup materials

//! Creates averaged material. Square refractive index of returned material is arithmetic mean over
//! _regions_ and _layer_mat_. Magnetization (if present) is averaged linearly.
BA_CORE_API_ Material CreateAveragedMaterial(const Material& layer_mat,
                                             const std::vector<HomogeneousRegion>& regions);

#endif // SWIG

#endif // BORNAGAIN_CORE_PARTICLE_HOMOGENEOUSREGION_H
