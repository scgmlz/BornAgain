// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultilayerInfo.h
//! @brief     Defines struct MultilayerInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYERINFO_H
#define MULTILAYERINFO_H

class IFresnelMap;
class MultiLayer;

//! Container struct for information regarding a multilayer: Fresnel coefficients and the
//! multilayer itself.
//! Used by the components of DWBASingleComputation, which adds up the contributions from
//! particles, roughness and specular signal
//! @ingroup algorithms_internal

struct MultilayerInfo
{
    MultilayerInfo(const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map)
        : mp_multilayer(p_multilayer) , mp_fresnel_map(p_fresnel_map) {}

    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
};

#endif // MULTILAYERINFO_H
