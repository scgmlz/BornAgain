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

#ifndef BORNAGAIN_CORE_COMPUTATION_GISASSPECULARCOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_GISASSPECULARCOMPUTATION_H

class IFresnelMap;
class SimulationElement;

//! Computes the specular signal in the bin where q_parallel = 0. Used by DWBAComputation.
//! @ingroup algorithms_internal

class GISASSpecularComputation final
{
public:
    GISASSpecularComputation(const IFresnelMap* p_fresnel_map);

    void compute(SimulationElement& elem) const;

private:
    const IFresnelMap* mp_fresnel_map;
};

#endif // BORNAGAIN_CORE_COMPUTATION_GISASSPECULARCOMPUTATION_H
