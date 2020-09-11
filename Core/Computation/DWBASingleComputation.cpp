// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBASingleComputation.cpp
//! @brief     Implements class DWBASingleComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/DWBASingleComputation.h"
#include "Core/Computation/DelayedProgressCounter.h"
#include "Core/Computation/GISASSpecularComputation.h"
#include "Core/Computation/ParticleLayoutComputation.h"
#include "Core/Computation/RoughMultiLayerComputation.h"

DWBASingleComputation::DWBASingleComputation() = default;

DWBASingleComputation::~DWBASingleComputation() = default;

DWBASingleComputation::DWBASingleComputation(DWBASingleComputation&&) = default;

void DWBASingleComputation::setProgressHandler(ProgressHandler* p_progress)
{
    mP_progress_counter.reset(new DelayedProgressCounter(p_progress, 100));
}

void DWBASingleComputation::addLayoutComputation(ParticleLayoutComputation* p_layout_comp)
{
    m_layout_comps.emplace_back(p_layout_comp);
    p_layout_comp->mergeRegionMap(m_region_map);
}

void DWBASingleComputation::setRoughnessComputation(RoughMultiLayerComputation* p_roughness_comp)
{
    mP_roughness_comp.reset(p_roughness_comp);
}

void DWBASingleComputation::setSpecularBinComputation(GISASSpecularComputation* p_spec_comp)
{
    mP_spec_comp.reset(p_spec_comp);
}

void DWBASingleComputation::compute(SimulationElement& elem) const
{
    for (auto& layout_comp : m_layout_comps) {
        layout_comp->compute(elem);
    }
    if (mP_roughness_comp) { // also check absence of matrix RT coefficients
        mP_roughness_comp->compute(elem);
    }
    if (mP_spec_comp) { // also check absence of matrix RT coefficients
        mP_spec_comp->compute(elem);
    }
    if (mP_progress_counter) {
        mP_progress_counter->stepProgress();
    }
}

const std::map<size_t, std::vector<HomogeneousRegion>>& DWBASingleComputation::regionMap() const
{
    return m_region_map;
}
