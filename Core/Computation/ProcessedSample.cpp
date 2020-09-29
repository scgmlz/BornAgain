// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedSample.cpp
//! @brief     Implements class ProcessedSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/ProcessedSample.h"
#include "Core/Computation/ProcessedLayout.h"
#include "Core/Computation/SpecularStrategyBuilder.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MatrixFresnelMap.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/MultiLayerUtils.h"
#include "Core/Multilayer/ScalarFresnelMap.h"
#include "Core/Multilayer/Slice.h"
#include "Core/Parametrization/SimulationOptions.h"
#include "Core/Particle/HomogeneousRegion.h"

namespace
{
std::unique_ptr<IFresnelMap> CreateFresnelMap(const MultiLayer& sample,
                                              const std::vector<Slice>& slices,
                                              const SimulationOptions& options);
bool ContainsMagneticMaterial(const MultiLayer& sample);
bool ContainsMagneticSlice(const std::vector<Slice>& slices);
bool CheckRegions(const std::vector<HomogeneousRegion>& regions);
std::vector<Slice>
CreateAverageMaterialSlices(const std::vector<Slice>& slices,
                            const std::map<size_t, std::vector<HomogeneousRegion>>& region_map);
} // namespace

ProcessedSample::ProcessedSample(const MultiLayer& sample, const SimulationOptions& options)
    : m_slices{}, m_top_z{0.0}, m_polarized{false}, m_crossCorrLength{sample.crossCorrLength()},
      m_ext_field{sample.externalField()}
{
    initSlices(sample, options);
    mP_fresnel_map = CreateFresnelMap(sample, m_slices, options);
    initBFields();
    initLayouts(sample);
    initFresnelMap(options);
}

ProcessedSample::~ProcessedSample() = default;

size_t ProcessedSample::numberOfSlices() const
{
    return m_slices.size();
}

const std::vector<Slice>& ProcessedSample::slices() const
{
    return m_slices;
}

const std::vector<Slice>& ProcessedSample::averageSlices() const
{
    return mP_fresnel_map->slices();
}

const std::vector<ProcessedLayout>& ProcessedSample::layouts() const
{
    return m_layouts;
}

const IFresnelMap* ProcessedSample::fresnelMap() const
{
    return mP_fresnel_map.get();
}

double ProcessedSample::crossCorrelationLength() const
{
    return m_crossCorrLength;
}

kvector_t ProcessedSample::externalField() const
{
    return m_ext_field;
}

const LayerRoughness* ProcessedSample::bottomRoughness(size_t i) const
{
    if (i + 2 > m_slices.size())
        throw std::runtime_error("ProcessedSample::bottomRoughness: "
                                 "index out of bounds.");
    return m_slices[i + 1].topRoughness();
}

double ProcessedSample::sliceTopZ(size_t i) const
{
    if (i == 0)
        return m_top_z;
    return sliceBottomZ(i - 1);
}

double ProcessedSample::sliceBottomZ(size_t i) const
{
    if (numberOfSlices() < 2)
        return m_top_z;
    // Last slice has no bottom:
    if (i + 2 > numberOfSlices())
        i = numberOfSlices() - 2;
    auto z = m_top_z;
    for (size_t j = 1; j <= i; ++j)
        z -= m_slices[j].thickness();
    return z;
}

bool ProcessedSample::containsMagneticMaterial() const
{
    return m_polarized;
}

bool ProcessedSample::hasRoughness() const
{
    for (auto& slice : m_slices) {
        if (slice.topRoughness())
            return true;
    }
    return false;
}

double ProcessedSample::crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const
{
    if (m_crossCorrLength <= 0.0)
        return 0.0;
    double z_j = sliceBottomZ(j);
    double z_k = sliceBottomZ(k);
    const LayerRoughness* rough_j = bottomRoughness(j);
    const LayerRoughness* rough_k = bottomRoughness(k);
    if (!rough_j || !rough_k)
        return 0.0;
    double sigma_j = rough_j->getSigma();
    double sigma_k = rough_k->getSigma();
    if (sigma_j <= 0 || sigma_k <= 0)
        return 0.0;
    double corr = 0.5
                  * ((sigma_k / sigma_j) * rough_j->getSpectralFun(kvec)
                     + (sigma_j / sigma_k) * rough_k->getSpectralFun(kvec))
                  * std::exp(-1 * std::abs(z_j - z_k) / m_crossCorrLength);
    return corr;
}

// Creates a array of slices with the correct thickness, roughness and material
void ProcessedSample::initSlices(const MultiLayer& sample, const SimulationOptions& options)
{
    if (sample.numberOfLayers() == 0)
        return;
    bool use_slicing = options.useAvgMaterials() && sample.numberOfLayers() > 1;
    auto layer_limits = MultiLayerUtils::ParticleRegions(sample, use_slicing);
    for (size_t i = 0; i < sample.numberOfLayers(); ++i) {
        auto p_layer = sample.layer(i);
        auto n_slices = p_layer->numberOfSlices();
        const ZLimits& slice_limits = layer_limits[i];
        double tl = p_layer->thickness();
        const Material* p_material = p_layer->material();
        auto p_roughness = MultiLayerUtils::LayerTopRoughness(sample, i);
        if (p_roughness && p_roughness->getSigma() <= 0)
            p_roughness = nullptr;
        // if no slicing is needed, create single slice for the layer
        if (!slice_limits.isFinite() || n_slices == 0) {
            if (i == sample.numberOfLayers() - 1)
                tl = 0.0;
            addSlice(tl, *p_material, p_roughness);
            continue;
        }
        double top = slice_limits.upperLimit().m_value;
        double bottom = slice_limits.lowerLimit().m_value;
        // top layer
        if (i == 0) {
            if (top <= 0)
                throw std::runtime_error("ProcessedSample::ProcessedSample: "
                                         "top limit for top layer must be > 0.");
            addSlice(0.0, *p_material);
            addNSlices(n_slices, top - bottom, *p_material);
            if (bottom > 0) {
                addSlice(bottom, *p_material);
            }
            m_top_z = top;
        }
        // middle or bottom layer
        else {
            if (top < 0) {
                addSlice(-top, *p_material, p_roughness);
                addNSlices(n_slices, top - bottom, *p_material);
            } else {
                addNSlices(n_slices, top - bottom, *p_material, p_roughness);
            }
            // middle layer
            if (i < sample.numberOfLayers() - 1 && bottom > -tl) {
                addSlice(bottom + tl, *p_material);
            }
            // bottom layer
            if (i == sample.numberOfLayers() - 1) {
                addSlice(0.0, *p_material);
            }
        }
    }
}

void ProcessedSample::initLayouts(const MultiLayer& sample)
{
    double z_ref = -m_top_z;
    m_polarized = ContainsMagneticMaterial(sample);
    for (size_t i = 0; i < sample.numberOfLayers(); ++i) {
        if (i > 1)
            z_ref -= MultiLayerUtils::LayerThickness(sample, i - 1);
        auto p_layer = sample.layer(i);
        for (auto p_layout : p_layer->layouts()) {
            m_layouts.emplace_back(*p_layout, m_slices, z_ref, mP_fresnel_map.get(), m_polarized);
            mergeRegionMap(m_layouts.back().regionMap());
        }
    }
}

void ProcessedSample::addSlice(double thickness, const Material& material,
                               const LayerRoughness* p_roughness)
{
    if (p_roughness) {
        m_slices.emplace_back(thickness, material, *p_roughness);
    } else {
        m_slices.emplace_back(thickness, material);
    }
}

void ProcessedSample::addNSlices(size_t n, double thickness, const Material& material,
                                 const LayerRoughness* p_roughness)
{
    if (thickness <= 0.0)
        return;
    if (n == 0)
        throw std::runtime_error("ProcessedSample::addNSlices: number of slices should be "
                                 "bigger than zero.");
    double slice_thickness = thickness / n;
    addSlice(slice_thickness, material, p_roughness);
    for (size_t i = 1; i < n; ++i) {
        addSlice(slice_thickness, material);
    }
}

void ProcessedSample::initBFields()
{
    if (m_slices.size() == 0)
        return;
    double m_z0 = m_slices[0].material().magnetization().z();
    double b_z = Slice::Magnetic_Permeability * (m_ext_field.z() + m_z0);
    for (size_t i = 0; i < m_slices.size(); ++i) {
        m_slices[i].initBField(m_ext_field, b_z);
    }
}

void ProcessedSample::mergeRegionMap(
    const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    for (auto& entry : region_map) {
        size_t i = entry.first;
        auto& regions = entry.second;
        m_region_map[i].insert(m_region_map[i].begin(), regions.begin(), regions.end());
    }
}

void ProcessedSample::initFresnelMap(const SimulationOptions& sim_options)
{
    if (sim_options.useAvgMaterials()) {
        mP_fresnel_map->setSlices(CreateAverageMaterialSlices(m_slices, m_region_map));
    } else {
        mP_fresnel_map->setSlices(m_slices);
    }
}

namespace
{
std::unique_ptr<IFresnelMap> CreateFresnelMap(const MultiLayer& sample,
                                              const std::vector<Slice>& slices,
                                              const SimulationOptions& options)
{
    std::unique_ptr<IFresnelMap> P_result;
    if (ContainsMagneticSlice(slices))
        P_result.reset(new MatrixFresnelMap(SpecularStrategyBuilder::build(sample, true)));
    else
        P_result.reset(new ScalarFresnelMap(SpecularStrategyBuilder::build(sample, false)));
    if (options.isIntegrate())
        P_result->disableCaching();
    return P_result;
}

bool ContainsMagneticMaterial(const MultiLayer& sample)
{
    for (const Material* mat : sample.containedMaterials())
        if (mat->isMagneticMaterial())
            return true;
    return false;
}

bool ContainsMagneticSlice(const std::vector<Slice>& slices)
{
    for (size_t i = 0; i < slices.size(); ++i) {
        if (slices[i].material().isMagneticMaterial())
            return true;
    }
    return false;
}

bool CheckRegions(const std::vector<HomogeneousRegion>& regions)
{
    double total_fraction = 0.0;
    for (auto& region : regions)
        total_fraction += region.m_volume;
    return (total_fraction >= 0 && total_fraction <= 1);
}

std::vector<Slice>
CreateAverageMaterialSlices(const std::vector<Slice>& slices,
                            const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    std::vector<Slice> result = slices;
    auto last_slice_index = slices.size() - 1;
    for (auto& entry : region_map) {
        auto i_slice = entry.first;
        if (i_slice == 0 || i_slice == last_slice_index)
            continue; // skip semi-infinite layers
        auto slice_mat = slices[i_slice].material();
        if (!CheckRegions(entry.second))
            throw std::runtime_error("CreateAverageMaterialSlices: "
                                     "total volumetric fraction of particles exceeds 1!");
        auto new_material = createAveragedMaterial(slice_mat, entry.second);
        result[i_slice].setMaterial(new_material);
    }
    return result;
}
} // namespace
