// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SlicedFormFactorList.cpp
//! @brief     Defines class SlicedFormFactorList.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SlicedFormFactorList.h"
#include "Core/Multilayer/Slice.h"
#include "Core/Particle/IParticle.h"
#include "Core/Scattering/Rotations.h"
#include <utility>

namespace
{
std::pair<size_t, size_t> SliceIndexSpan(const IParticle& particle,
                                         const std::vector<Slice>& slices, double z_ref);
size_t TopZToSliceIndex(double z, const std::vector<Slice>& slices);
size_t BottomZToSliceIndex(double z, const std::vector<Slice>& slices);
double SliceTopZ(size_t i, const std::vector<Slice>& slices);
ZLimits SlicesZLimits(const std::vector<Slice>& slices, size_t slice_index);
void ScaleRegions(std::vector<HomogeneousRegion>& regions, double factor);
} // namespace

SlicedFormFactorList SlicedFormFactorList::createSlicedFormFactors(const IParticle& particle,
                                                                   const std::vector<Slice>& slices,
                                                                   double z_ref)
{
    SlicedFormFactorList result;
    auto particles = particle.decompose();
    for (auto p_particle : particles) {
        result.addParticle(*p_particle, slices, z_ref);
    }
    return result;
}

void SlicedFormFactorList::addParticle(IParticle& particle, const std::vector<Slice>& slices,
                                       double z_ref)
{
    auto slice_indices = SliceIndexSpan(particle, slices, z_ref);
    bool single_layer = (slice_indices.first == slice_indices.second);
    for (size_t i = slice_indices.first; i < slice_indices.second + 1; ++i) {
        double z_top_i = SliceTopZ(i, slices);
        kvector_t translation(0.0, 0.0, z_ref - z_top_i);
        particle.translate(translation);
        // if particle is contained in this layer, set limits to infinite:
        ZLimits limits = single_layer ? ZLimits() : SlicesZLimits(slices, i);
        auto sliced_particle = particle.createSlicedParticle(limits);
        m_ff_list.emplace_back(std::move(sliced_particle.mP_slicedff), i);
        double thickness = slices[i].thickness();
        if (thickness > 0.0)
            ScaleRegions(sliced_particle.m_regions, 1 / thickness);
        m_region_map[i].insert(m_region_map[i].end(), sliced_particle.m_regions.begin(),
                               sliced_particle.m_regions.end());
        z_ref = z_top_i; // particle now has coordinates relative to z_top_i
    }
}

size_t SlicedFormFactorList::size() const
{
    return m_ff_list.size();
}

std::pair<const IFormFactor*, size_t> SlicedFormFactorList::operator[](size_t index) const
{
    if (index >= size())
        throw std::out_of_range("SlicedFormFactorList::operator[] error: "
                                "index out of range");
    return {m_ff_list[index].first.get(), m_ff_list[index].second};
}

std::map<size_t, std::vector<HomogeneousRegion>> SlicedFormFactorList::regionMap() const
{
    return m_region_map;
}

namespace
{
std::pair<size_t, size_t> SliceIndexSpan(const IParticle& particle,
                                         const std::vector<Slice>& slices, double z_ref)
{
    auto bottomTopZ = particle.bottomTopZ();
    double zbottom = bottomTopZ.m_bottom;
    double ztop = bottomTopZ.m_top;
    double eps = (ztop - zbottom) * 1e-6; // allow for relatively small crossing due to numerical
                                          // approximations (like rotation over 180 degrees)
    double zmax = ztop + z_ref - eps;
    double zmin = zbottom + z_ref + eps;
    size_t top_index = TopZToSliceIndex(zmax, slices);
    size_t bottom_index = BottomZToSliceIndex(zmin, slices);
    if (top_index > bottom_index) // happens for zero size particles
        top_index = bottom_index;
    return {top_index, bottom_index};
}

size_t TopZToSliceIndex(double z, const std::vector<Slice>& slices)
{
    auto n_layers = slices.size();
    if (n_layers < 2 || z > 0.0)
        return 0;
    double z_layer_bottom = 0.0;
    size_t i_slice = 0;
    while (i_slice + 1 < n_layers) {
        ++i_slice;
        z_layer_bottom -= slices[i_slice].thickness();
        if (z > z_layer_bottom)
            break;
    }
    return i_slice;
}

size_t BottomZToSliceIndex(double z, const std::vector<Slice>& slices)
{
    auto n_layers = slices.size();
    if (n_layers < 2 || z >= 0.0)
        return 0;
    double z_layer_bottom = 0.0;
    size_t i_slice = 0;
    while (i_slice + 1 < n_layers) {
        ++i_slice;
        z_layer_bottom -= slices[i_slice].thickness();
        if (z >= z_layer_bottom)
            break;
    }
    return i_slice;
}

double SliceTopZ(size_t i, const std::vector<Slice>& slices)
{
    if (i == 0)
        return 0.0;
    double top_z = 0.0;
    for (size_t j = 1; j < i; ++j)
        top_z -= slices[j].thickness();
    return top_z;
}

ZLimits SlicesZLimits(const std::vector<Slice>& slices, size_t slice_index)
{
    size_t N = slices.size();
    if (N < 2)
        return ZLimits{};
    if (slice_index == 0)
        return ZLimits({false, 0}, {true, 0});
    if (slice_index == N - 1)
        return ZLimits({true, 0}, {false, 0});
    double thickness = slices[slice_index].thickness();
    return ZLimits(-thickness, 0.0);
}

void ScaleRegions(std::vector<HomogeneousRegion>& regions, double factor)
{
    for (auto& region : regions)
        region.m_volume *= factor;
}
} // namespace
