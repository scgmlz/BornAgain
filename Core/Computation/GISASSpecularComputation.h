// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/GISASSpecularComputation.h
//! @brief     Defines class GISASSpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GISASSPECULARCOMPUTATION_H_
#define GISASSPECULARCOMPUTATION_H_

#include "MultilayerInfo.h"
#include <vector>

class SimulationElement;

//! Computes the specular signal in the bin where q_parallel = 0. Used by DWBAComputation.
//! @ingroup algorithms_internal

class GISASSpecularComputation final
{
public:
    GISASSpecularComputation(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void compute(SimulationElement& elem) const;
private:
    MultilayerInfo m_multilayer_info;
};

#endif // GISASSPECULARCOMPUTATION_H_
