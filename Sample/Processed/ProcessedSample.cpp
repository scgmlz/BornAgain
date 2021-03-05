//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/Processed/ProcessedSample.cpp
//! @brief     Implements class ProcessedSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Processed/ProcessedSample.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Fresnel/MatrixFresnelMap.h"
#include "Sample/Fresnel/ScalarFresnelMap.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayerUtils.h"
#include "Sample/Particle/HomogeneousRegion.h"
#include "Sample/Particle/IParticle.h"
#include "Sample/Processed/ProcessedLayout.h"
#include "Sample/RT/SimulationOptions.h"
#include "Sample/Scattering/LayerFillLimits.h"
#include "Sample/Slice/LayerRoughness.h"
#include "Sample/Specular/SpecularStrategyBuilder.h"

namespace {

std::unique_ptr<IFresnelMap> createFresnelMap(const MultiLayer& sample,
                                              const std::vector<Slice>& slices,
                                              const SimulationOptions& options)
{
    std::unique_ptr<IFresnelMap> result;
    const bool magnetic = std::any_of(slices.cbegin(), slices.cend(), [](const Slice& slice) {
        return slice.material().isMagneticMaterial();
    });
    if (magnetic)
        result = std::make_unique<MatrixFresnelMap>(SpecularStrategyBuilder::build(sample, true));
    else
        result = std::make_unique<ScalarFresnelMap>(SpecularStrategyBuilder::build(sample, false));
    if (options.isIntegrate())
        result->disableCaching();
    return result;
}

bool checkRegions(const std::vector<HomogeneousRegion>& regions)
{
    double total_fraction = 0.0;
    for (const auto& region : regions)
        total_fraction += region.m_volume;
    return (total_fraction >= 0 && total_fraction <= 1);
}

std::vector<Slice>
createAverageMaterialSlices(const std::vector<Slice>& slices,
                            const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    std::vector<Slice> result = slices;
    const auto last_slice_index = slices.size() - 1;
    for (const auto& entry : region_map) {
        const auto i_slice = entry.first;
        if (i_slice == 0 || i_slice == last_slice_index)
            continue; // skip semi-infinite layers
        const auto slice_mat = slices[i_slice].material();
        if (!checkRegions(entry.second))
            throw std::runtime_error("createAverageMaterialSlices: "
                                     "total volumetric fraction of particles exceeds 1!");
        const auto new_material = createAveragedMaterial(slice_mat, entry.second);
        result[i_slice].setMaterial(new_material);
    }
    return result;
}

std::vector<double> bottomLayerCoordinates(const MultiLayer& multilayer)
{
    auto n_layers = multilayer.numberOfLayers();
    if (n_layers < 2)
        return {};
    std::vector<double> result(n_layers - 1);
    result[0] = 0.0;
    for (size_t i = 1; i < n_layers - 1; ++i)
        result[i] = result[i - 1] - multilayer.layer(i)->thickness();
    return result;
}

//! Calculate z-regions occupied by particles
std::vector<ZLimits> particleRegions(const MultiLayer& multilayer, bool use_slicing)
{
    const std::vector<double> bottom_coords = bottomLayerCoordinates(multilayer);
    LayerFillLimits layer_fill_limits(bottom_coords);
    if (use_slicing) {
        for (size_t i = 0; i < multilayer.numberOfLayers(); ++i) {
            auto layer = multilayer.layer(i);
            double offset = (i == 0) ? 0 : bottom_coords[i - 1];
            for (const auto* layout : layer->layouts())
                for (const auto* particle : layout->particles())
                    layer_fill_limits.update(particle->bottomTopZ(), offset);
        }
    }
    return layer_fill_limits.layerZLimits();
}

} // namespace

//  ************************************************************************************************
//  class ProcessedSample
//  ************************************************************************************************

ProcessedSample::ProcessedSample(const MultiLayer& sample, const SimulationOptions& options,
                                 bool forcePolarized)
    : m_slices{}
    , m_top_z{0.0}
    , m_polarized{forcePolarized}
    , m_crossCorrLength{sample.crossCorrLength()}
    , m_ext_field{sample.externalField()}
{
    initSlices(sample, options);
    m_fresnel_map = createFresnelMap(sample, m_slices, options);
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
    return m_fresnel_map->slices();
}

const std::vector<ProcessedLayout>& ProcessedSample::layouts() const
{
    return m_layouts;
}

const IFresnelMap* ProcessedSample::fresnelMap() const
{
    return m_fresnel_map.get();
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
    double z = m_top_z;
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
    for (const auto& slice : m_slices)
        if (slice.topRoughness())
            return true;
    return false;
}

double ProcessedSample::crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const
{
    if (m_crossCorrLength <= 0.0)
        return 0.0;
    const double z_j = sliceBottomZ(j);
    const double z_k = sliceBottomZ(k);
    const LayerRoughness* rough_j = bottomRoughness(j);
    const LayerRoughness* rough_k = bottomRoughness(k);
    if (!rough_j || !rough_k)
        return 0.0;
    const double sigma_j = rough_j->getSigma();
    const double sigma_k = rough_k->getSigma();
    if (sigma_j <= 0 || sigma_k <= 0)
        return 0.0;
    return 0.5
           * ((sigma_k / sigma_j) * rough_j->getSpectralFun(kvec)
              + (sigma_j / sigma_k) * rough_k->getSpectralFun(kvec))
           * std::exp(-1 * std::abs(z_j - z_k) / m_crossCorrLength);
}

// Creates a array of slices with the correct thickness, roughness and material
void ProcessedSample::initSlices(const MultiLayer& sample, const SimulationOptions& options)
{
    if (sample.numberOfLayers() == 0)
        return;
    bool use_slicing = options.useAvgMaterials() && sample.numberOfLayers() > 1;
    const auto layer_limits = particleRegions(sample, use_slicing);
    for (size_t i = 0; i < sample.numberOfLayers(); ++i) {
        const auto layer = sample.layer(i);
        const auto n_slices = layer->numberOfSlices();
        const ZLimits& slice_limits = layer_limits[i];
        double tl = layer->thickness();
        const Material* material = layer->material();
        auto roughness = MultiLayerUtils::LayerTopRoughness(sample, i);
        if (roughness && roughness->getSigma() <= 0)
            roughness = nullptr;
        // if no slicing is needed, create single slice for the layer
        if (!slice_limits.isFinite() || n_slices == 0) {
            if (i == sample.numberOfLayers() - 1)
                tl = 0.0;
            addSlice(tl, *material, roughness);
            continue;
        }
        const double top = slice_limits.upperLimit().m_value;
        const double bottom = slice_limits.lowerLimit().m_value;
        // top layer
        if (i == 0) {
            if (top <= 0)
                throw std::runtime_error("ProcessedSample::ProcessedSample: "
                                         "top limit for top layer must be > 0.");
            addSlice(0.0, *material);
            addNSlices(n_slices, top - bottom, *material);
            if (bottom > 0)
                addSlice(bottom, *material);
            m_top_z = top;
        }
        // middle or bottom layer
        else {
            if (top < 0) {
                addSlice(-top, *material, roughness);
                addNSlices(n_slices, top - bottom, *material);
            } else {
                addNSlices(n_slices, top - bottom, *material, roughness);
            }
            // middle layer
            if (i < sample.numberOfLayers() - 1 && bottom > -tl)
                addSlice(bottom + tl, *material);
            // bottom layer
            if (i == sample.numberOfLayers() - 1)
                addSlice(0.0, *material);
        }
    }
}

void ProcessedSample::initLayouts(const MultiLayer& sample)
{
    double z_ref = -m_top_z;
    m_polarized = m_polarized || sample.isMagnetic();

    for (size_t i = 0; i < sample.numberOfLayers(); ++i) {
        if (i > 1)
            z_ref -= sample.layer(i - 1)->thickness();
        auto layer = sample.layer(i);
        for (const auto* layout : layer->layouts()) {
            m_layouts.emplace_back(*layout, m_slices, z_ref, m_fresnel_map.get(), m_polarized);
            mergeRegionMap(m_layouts.back().regionMap());
        }
    }
}

void ProcessedSample::addSlice(double thickness, const Material& material,
                               const LayerRoughness* roughness)
{
    if (roughness)
        m_slices.emplace_back(thickness, material, *roughness);
    else
        m_slices.emplace_back(thickness, material);
}

void ProcessedSample::addNSlices(size_t n, double thickness, const Material& material,
                                 const LayerRoughness* roughness)
{
    if (thickness <= 0.0)
        return;
    if (n == 0)
        throw std::runtime_error("ProcessedSample::addNSlices: number of slices should be "
                                 "bigger than zero.");
    const double slice_thickness = thickness / n;
    addSlice(slice_thickness, material, roughness);
    for (size_t i = 1; i < n; ++i)
        addSlice(slice_thickness, material);
}

void ProcessedSample::initBFields()
{
    if (m_slices.empty())
        return;
    const double m_z0 = m_slices[0].material().magnetization().z();
    const double b_z = Slice::Magnetic_Permeability * (m_ext_field.z() + m_z0);
    for (size_t i = 0; i < m_slices.size(); ++i) {
        m_slices[i].initBField(m_ext_field, b_z);
    }
}

void ProcessedSample::mergeRegionMap(
    const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    for (const auto& entry : region_map) {
        size_t i = entry.first;
        auto& regions = entry.second;
        m_region_map[i].insert(m_region_map[i].begin(), regions.begin(), regions.end());
    }
}

void ProcessedSample::initFresnelMap(const SimulationOptions& sim_options)
{
    if (sim_options.useAvgMaterials()) {
        m_fresnel_map->setSlices(createAverageMaterialSlices(m_slices, m_region_map));
    } else {
        m_fresnel_map->setSlices(m_slices);
    }
}
