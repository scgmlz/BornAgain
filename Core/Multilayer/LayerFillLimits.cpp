// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerFillLimits.cpp
//! @brief     Implements class LayerFillLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/LayerFillLimits.h"
#include <algorithm>
#include <stdexcept>

namespace
{
ZLimits CalculateNewLayerLimits(ZLimits old_limits, ZLimits bounded_limits);
}

LayerFillLimits::LayerFillLimits(std::vector<double> layers_bottomz)
    : m_layers_bottomz(std::move(layers_bottomz)), m_layer_fill_limits(m_layers_bottomz.size() + 1)
// default ZLimits designate an absence of limits
{
}

void LayerFillLimits::update(ParticleLimits particle_limits, double offset)
{
    if (m_layers_bottomz.empty())
        return; // do nothing for the single layer case
    double top = particle_limits.m_top + offset;
    double bottom = particle_limits.m_bottom + offset;
    if (bottom > top)
        throw std::runtime_error("LayerFillLimits::update: lower_limit > upper_limit.");
    if (bottom == top) // zero-size particle
        return;
    size_t top_index = layerIndexTop(top);
    size_t bottom_index = layerIndexBottom(bottom);
    for (size_t i_layer = top_index; i_layer < bottom_index + 1; ++i_layer) {
        ZLimits limits(bottom, top);
        updateLayerLimits(i_layer, limits);
    }
}

std::vector<ZLimits> LayerFillLimits::layerZLimits() const
{
    return m_layer_fill_limits;
}

size_t LayerFillLimits::layerIndexTop(double top_z) const
{
    if (m_layers_bottomz.empty())
        return 0;
    if (top_z <= m_layers_bottomz.back())
        return m_layers_bottomz.size();
    auto index_above = std::lower_bound(m_layers_bottomz.rbegin(), m_layers_bottomz.rend(), top_z);
    return static_cast<size_t>(m_layers_bottomz.rend() - index_above);
}

size_t LayerFillLimits::layerIndexBottom(double bottom_z) const
{
    if (m_layers_bottomz.empty())
        return 0;
    if (bottom_z < m_layers_bottomz.back())
        return m_layers_bottomz.size();
    auto index_below =
        std::upper_bound(m_layers_bottomz.rbegin(), m_layers_bottomz.rend(), bottom_z);
    return static_cast<size_t>(m_layers_bottomz.rend() - index_below);
}

void LayerFillLimits::updateLayerLimits(size_t i_layer, ZLimits limits)
{
    if (!limits.isFinite())
        throw std::runtime_error("LayerFillLimits::updateLayerLimits: given limits are not "
                                 "finite.");
    auto old_limits = m_layer_fill_limits[i_layer];
    double layer_ref = i_layer ? m_layers_bottomz[i_layer - 1] : m_layers_bottomz[i_layer];
    double upper =
        i_layer ? std::min(limits.upperLimit().m_value, layer_ref) : limits.upperLimit().m_value;
    double lower = (i_layer == m_layer_fill_limits.size() - 1)
                       ? limits.lowerLimit().m_value
                       : std::max(limits.lowerLimit().m_value, m_layers_bottomz[i_layer]);
    ZLimits bounded_limits(lower - layer_ref, upper - layer_ref);
    m_layer_fill_limits[i_layer] = CalculateNewLayerLimits(old_limits, bounded_limits);
}

namespace
{
ZLimits CalculateNewLayerLimits(ZLimits old_limits, ZLimits bounded_limits)
{
    if (!old_limits.isFinite())
        return bounded_limits;
    else
        return ConvexHull(old_limits, bounded_limits);
}
} // namespace
