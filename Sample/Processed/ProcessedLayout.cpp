//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Processed/ProcessedLayout.cpp
//! @brief     Implements class ProcessedLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Processed/ProcessedLayout.h"
#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/FFCompute/ComputeBA.h"
#include "Sample/FFCompute/ComputeBAPol.h"
#include "Sample/FFCompute/ComputeDWBA.h"
#include "Sample/FFCompute/ComputeDWBAPol.h"
#include "Sample/Fresnel/FormFactorCoherentSum.h"
#include "Sample/Particle/IParticle.h"
#include "Sample/Slice/Slice.h"
#include "Sample/Slice/SlicedFormFactorList.h"

namespace {
void ScaleRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map, double factor) {
    for (auto& entry : region_map) {
        for (auto& region : entry.second) {
            region.m_volume *= factor;
        }
    }
}
} // namespace

//  ************************************************************************************************
//  class ProcessedLayout
//  ************************************************************************************************

ProcessedLayout::ProcessedLayout(const ParticleLayout& layout, const std::vector<Slice>& slices,
                                 double z_ref, const IFresnelMap* p_fresnel_map, bool polarized)
    : m_fresnel_map(p_fresnel_map), m_polarized(polarized) {
    m_n_slices = slices.size();
    collectFormFactors(layout, slices, z_ref);
    if (const auto* iff = layout.interferenceFunction())
        m_iff.reset(iff->clone());
}

ProcessedLayout::ProcessedLayout(ProcessedLayout&& other) {
    m_fresnel_map = other.m_fresnel_map;
    m_polarized = other.m_polarized;
    m_n_slices = other.m_n_slices;
    m_surface_density = other.m_surface_density;
    m_formfactors = std::move(other.m_formfactors);
    m_iff = std::move(other.m_iff);
    m_region_map = std::move(other.m_region_map);
}

size_t ProcessedLayout::numberOfSlices() const {
    return m_n_slices;
}

double ProcessedLayout::surfaceDensity() const {
    return m_surface_density;
}

const std::vector<FormFactorCoherentSum>& ProcessedLayout::formFactorList() const {
    return m_formfactors;
}

const IInterferenceFunction* ProcessedLayout::interferenceFunction() const {
    return m_iff.get();
}

std::map<size_t, std::vector<HomogeneousRegion>> ProcessedLayout::regionMap() const {
    return m_region_map;
}

ProcessedLayout::~ProcessedLayout() = default;

void ProcessedLayout::collectFormFactors(const ParticleLayout& layout,
                                         const std::vector<Slice>& slices, double z_ref) {
    double layout_abundance = layout.getTotalAbundance();
    for (const auto* particle : layout.particles()) {
        FormFactorCoherentSum ff_coh = processParticle(*particle, slices, z_ref);
        ff_coh.scaleRelativeAbundance(layout_abundance);
        m_formfactors.emplace_back(ff_coh);
    }
    double weight = layout.weight();
    m_surface_density = weight * layout.totalParticleSurfaceDensity();
    double scale_factor = m_surface_density / layout_abundance;
    ScaleRegionMap(m_region_map, scale_factor);
}

FormFactorCoherentSum ProcessedLayout::processParticle(const IParticle& particle,
                                                       const std::vector<Slice>& slices,
                                                       double z_ref) {
    double abundance = particle.abundance();
    auto sliced_ffs = SlicedFormFactorList::createSlicedFormFactors(particle, slices, z_ref);
    auto region_map = sliced_ffs.regionMap();
    ScaleRegionMap(region_map, abundance);
    mergeRegionMap(region_map);
    auto result = FormFactorCoherentSum(abundance);
    for (size_t i = 0; i < sliced_ffs.size(); ++i) {
        const auto ff_pair = sliced_ffs[i];
        std::unique_ptr<IComputeFF> ff_framework;
        if (slices.size() > 1) {
            if (m_polarized)
                ff_framework = std::make_unique<ComputeDWBAPol>(*ff_pair.first);
            else
                ff_framework = std::make_unique<ComputeDWBA>(*ff_pair.first);
        } else {
            if (m_polarized)
                ff_framework = std::make_unique<ComputeBAPol>(*ff_pair.first);
            else
                ff_framework = std::make_unique<ComputeBA>(*ff_pair.first);
        }

        size_t slice_index = ff_pair.second;
        const Material slice_material = slices[slice_index].material();
        ff_framework->setAmbientMaterial(slice_material);

        auto part = FormFactorCoherentPart(ff_framework.release());
        part.setSpecularInfo(m_fresnel_map, slice_index);

        result.addCoherentPart(part);
    }
    return result;
}

void ProcessedLayout::mergeRegionMap(
    const std::map<size_t, std::vector<HomogeneousRegion>>& region_map) {
    for (const auto& entry : region_map) {
        size_t layer_index = entry.first;
        auto regions = entry.second;
        m_region_map[layer_index].insert(m_region_map[layer_index].begin(), regions.begin(),
                                         regions.end());
    }
}
