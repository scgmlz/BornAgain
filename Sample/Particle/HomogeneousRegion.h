//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/HomogeneousRegion.h
//! @brief     Defines struct HomogeneousRegion, and declares fct createAveragedMaterial
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_PARTICLE_HOMOGENEOUSREGION_H
#define BORNAGAIN_SAMPLE_PARTICLE_HOMOGENEOUSREGION_H

#include "Sample/Material/Material.h"

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
Material createAveragedMaterial(const Material& layer_mat,
                                const std::vector<HomogeneousRegion>& regions);

#endif // USER_API

#endif // BORNAGAIN_SAMPLE_PARTICLE_HOMOGENEOUSREGION_H
#endif // USER_API
