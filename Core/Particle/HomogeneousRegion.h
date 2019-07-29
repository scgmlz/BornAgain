// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/HomogeneousRegion.h
//! @brief     Defines struct HomogeneousRegion.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef HOMOGENEOUSREGION_H
#define HOMOGENEOUSREGION_H

#include "Material.h"

//! Struct that contains information on a single homogeneous region of a particle inside
//! a single layer.
//! This information is needed for calculating the average of a material, used in the Fresnel
//! calculations.
//!
//! @ingroup intern

struct HomogeneousRegion
{
    double m_volume;
    Material m_material;
};

#endif // HOMOGENEOUSREGION_H
