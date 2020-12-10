//  ************************************************************************************************
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
//  ************************************************************************************************

#include "Core/Computation/DWBASingleComputation.h"
#include "Base/Progress/DelayedProgressCounter.h"
#include "Core/Computation/GISASSpecularComputation.h"
#include "Core/Computation/ParticleLayoutComputation.h"
#include "Core/Computation/RoughMultiLayerComputation.h"

DWBASingleComputation::DWBASingleComputation() = default;

DWBASingleComputation::~DWBASingleComputation() = default;

void DWBASingleComputation::setProgressHandler(ProgressHandler* p_progress) {
    m_progress_counter = std::make_unique<DelayedProgressCounter>(p_progress, 100);
}

void DWBASingleComputation::addLayoutComputation(ParticleLayoutComputation* p_layout_comp) {
    m_layout_comps.emplace_back(p_layout_comp);
    p_layout_comp->mergeRegionMap(m_region_map);
}

void DWBASingleComputation::setRoughnessComputation(RoughMultiLayerComputation* p_roughness_comp) {
    m_roughness_comp.reset(p_roughness_comp);
}

void DWBASingleComputation::setSpecularBinComputation(GISASSpecularComputation* p_spec_comp) {
    m_spec_comp.reset(p_spec_comp);
}

void DWBASingleComputation::compute(SimulationElement& elem) const {
    for (auto& layout_comp : m_layout_comps)
        layout_comp->compute(elem);

    if (m_roughness_comp) // also check absence of matrix RT coefficients
        m_roughness_comp->compute(elem);

    if (m_spec_comp) // also check absence of matrix RT coefficients
        m_spec_comp->compute(elem);

    if (m_progress_counter)
        m_progress_counter->stepProgress();
}
