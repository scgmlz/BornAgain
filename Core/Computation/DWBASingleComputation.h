// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBASingleComputation.h
//! @brief     Defines class DWBASingleComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_DWBASINGLECOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_DWBASINGLECOMPUTATION_H

#include "Core/Particle/HomogeneousRegion.h"
#include <map>
#include <memory>
#include <vector>

class DelayedProgressCounter;
class GISASSpecularComputation;
class ParticleLayoutComputation;
class ProgressHandler;
class RoughMultiLayerComputation;
class SimulationElement;

//! Class that handles all the computations involved in GISAS (particles, roughness,...) for
//! a single detector bin.
//!
//! Called by DWBASimulation on each detector bin.
//!
//! @ingroup algorithms_internal

class DWBASingleComputation
{
public:
    DWBASingleComputation();
    ~DWBASingleComputation();
    DWBASingleComputation(DWBASingleComputation&& other);

    void setProgressHandler(ProgressHandler* p_progress);

    void addLayoutComputation(ParticleLayoutComputation* p_layout_comp);
    void setRoughnessComputation(RoughMultiLayerComputation* p_roughness_comp);
    void setSpecularBinComputation(GISASSpecularComputation* p_spec_comp);
    void compute(SimulationElement& elem) const;

    //! Retrieves a map of regions for the calculation of averaged layers
    const std::map<size_t, std::vector<HomogeneousRegion>>& regionMap() const;

private:
    std::vector<std::unique_ptr<ParticleLayoutComputation>> m_layout_comps;
    std::unique_ptr<RoughMultiLayerComputation> mP_roughness_comp;
    std::unique_ptr<GISASSpecularComputation> mP_spec_comp;
    std::unique_ptr<DelayedProgressCounter> mP_progress_counter;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // BORNAGAIN_CORE_COMPUTATION_DWBASINGLECOMPUTATION_H
