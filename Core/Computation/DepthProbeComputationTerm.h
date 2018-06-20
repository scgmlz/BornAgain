// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DepthProbeComputationTerm.h
//! @brief     Defines functor DepthProbeComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DEPTHPROBECOMPUTATIONTERM_H
#define DEPTHPROBECOMPUTATIONTERM_H

#include <memory>
#include <vector>

class DelayedProgressCounter;
class IFresnelMap;
class MultiLayer;
class ProgressHandler;
class DepthProbeElement;

class DepthProbeComputationTerm
{
public:
    DepthProbeComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);
    ~DepthProbeComputationTerm();

    void setProgressHandler(ProgressHandler* p_progress);

    void compute(DepthProbeElement& elem) const;

private:
    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
    std::unique_ptr<DelayedProgressCounter> mP_progress_counter;
};

#endif // DEPTHPROBECOMPUTATIONTERM_H
