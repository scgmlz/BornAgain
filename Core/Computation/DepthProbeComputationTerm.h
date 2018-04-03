// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DepthProbeComputationTerm.h
//! @brief     Defines class DepthProbeComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DEPTHPROBECOMPUTATIONTERM_H
#define DEPTHPROBECOMPUTATIONTERM_H

#include <vector>

class IFresnelMap;
class MultiLayer;
class ProgressHandler;
class SimulationElement;
class DepthProbeElement;

class DepthProbeComputationTerm
{
    using DepthProbeElementIter = std::vector<DepthProbeElement>::iterator;
public:
    DepthProbeComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void eval(ProgressHandler* progress, const DepthProbeElementIter& begin_it,
              const DepthProbeElementIter& end_it) const;

private:
    void evalSingle(const DepthProbeElementIter& iter) const;

    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
};

#endif // DEPTHPROBECOMPUTATIONTERM_H
