//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Processed/ProfileHelper.cpp
//! @brief     Implements class ProfileHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Processed/ProfileHelper.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/Slice/LayerRoughness.h"

namespace {
const double prefactor = std::sqrt(2.0 / M_PI);
double TransitionTanh(double x) {
    return (1.0 - std::tanh(prefactor * x)) / 2.0;
}
double Transition(double x, double sigma) {
    if (sigma <= 0.0)
        return x < 0.0 ? 1.0 : 0.0;
    return TransitionTanh(x / sigma);
}
} // namespace

ProfileHelper::ProfileHelper(const ProcessedSample& sample) {
    auto N = sample.numberOfSlices();
    m_materialdata.reserve(N);
    if (N > 1) {
        m_zlimits.reserve(N - 1);
        m_sigmas.reserve(N - 1);
    }
    auto& slices = sample.averageSlices();
    for (size_t i = 0; i < N; ++i) {
        m_materialdata.push_back(slices[i].material().materialData());
        if (i + 1 < N) {
            m_zlimits.push_back(sample.sliceBottomZ(i));
            if (const auto* roughness = sample.bottomRoughness(i)) {
                m_sigmas.push_back(roughness->getSigma());
            } else {
                m_sigmas.push_back(0.0);
            }
        }
    }
}

ProfileHelper::~ProfileHelper() = default;

// Note: for refractive index materials, the material interpolation actually happens at the level
// of n^2. To first order in delta and beta, this implies the same smooth interpolation of delta
// and beta, as is done here.
std::vector<complex_t> ProfileHelper::calculateProfile(const std::vector<double>& z_values) const {
    complex_t top_value = m_materialdata.size() ? m_materialdata[0] : 0.0;
    std::vector<complex_t> result(z_values.size(), top_value);
    for (size_t i = 0; i < m_zlimits.size(); ++i) {
        auto sld_diff = m_materialdata[i + 1] - m_materialdata[i];
        for (size_t j = 0; j < z_values.size(); ++j) {
            auto arg = (z_values[j] - m_zlimits[i]);
            auto t = Transition(arg, m_sigmas[i]);
            result[j] += sld_diff * t;
        }
    }
    return result;
}

std::pair<double, double> ProfileHelper::defaultLimits() const {
    if (m_zlimits.size() < 1)
        return {0.0, 0.0};
    double interface_span = m_zlimits.front() - m_zlimits.back();
    double default_margin = interface_span > 0.0 ? interface_span / 20.0 : 10.0;
    double top_margin = m_sigmas.front() > 0.0 ? 5.0 * m_sigmas.front() : default_margin;
    double bottom_margin = m_sigmas.back() > 0.0 ? 5.0 * m_sigmas.back() : default_margin;
    double z_min = m_zlimits.back() - bottom_margin;
    double z_max = m_zlimits.front() + top_margin;
    return {z_min, z_max};
}
