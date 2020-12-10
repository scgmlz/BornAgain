//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/IBornFF.cpp
//! @brief     Implements interface class IBornFF.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Scattering/IBornFF.h"
#include "Base/Utils/Algorithms.h"
#include "Sample/Material/WavevectorInfo.h"
#include "Sample/Scattering/Rotations.h"
#include "Sample/Shapes/IShape.h"

IBornFF::IBornFF() = default;

IBornFF::IBornFF(const NodeMeta& meta, const std::vector<double>& PValues)
    : IFormFactor(meta, PValues) {}

IBornFF::~IBornFF() = default;

complex_t IBornFF::evaluate(const WavevectorInfo& wavevectors) const {
    return evaluate_for_q(wavevectors.getQ());
}

Eigen::Matrix2cd IBornFF::evaluatePol(const WavevectorInfo& wavevectors) const {
    return evaluate_for_q_pol(wavevectors.getQ());
}

double IBornFF::bottomZ(const IRotation& rotation) const {
    if (!m_shape)
        return 0;
    return BottomZ(m_shape->vertices(), rotation);
}

double IBornFF::topZ(const IRotation& rotation) const {
    if (!m_shape)
        return 0;
    return TopZ(m_shape->vertices(), rotation);
}

bool IBornFF::canSliceAnalytically(const IRotation& rot) const {
    if (rot.zInvariant())
        return true;
    return false;
}

Eigen::Matrix2cd IBornFF::evaluate_for_q_pol(cvector_t q) const {
    return evaluate_for_q(q) * Eigen::Matrix2cd::Identity();
}

SlicingEffects IBornFF::computeSlicingEffects(ZLimits limits, const kvector_t& position,
                                              double height) {
    kvector_t new_position(position);
    double z_bottom = position.z();
    double z_top = position.z() + height;
    OneSidedLimit lower_limit = limits.lowerLimit();
    OneSidedLimit upper_limit = limits.upperLimit();
    ASSERT(upper_limit.m_limitless || lower_limit.m_limitless
           || lower_limit.m_value <= upper_limit.m_value);
    double dz_top = upper_limit.m_limitless ? -1 : z_top - upper_limit.m_value;
    double dz_bottom = lower_limit.m_limitless ? -1 : lower_limit.m_value - z_bottom;
    ASSERT(dz_top >= 0 || dz_bottom >= 0);
    ASSERT(dz_bottom <= height);
    ASSERT(dz_top <= height);
    if (dz_bottom < 0)
        dz_bottom = 0;
    if (dz_top < 0)
        dz_top = 0;
    if (dz_bottom > 0)
        new_position.setZ(lower_limit.m_value);
    return {new_position, dz_bottom, dz_top};
}

double IBornFF::BottomZ(const std::vector<kvector_t>& vertices, const IRotation& rotation) {
    ASSERT(vertices.size());
    return algo::min_value(
        vertices.begin(), vertices.end(),
        [&](const kvector_t& vertex) -> double { return rotation.transformed(vertex).z(); });
}

double IBornFF::TopZ(const std::vector<kvector_t>& vertices, const IRotation& rotation) {
    ASSERT(vertices.size());
    return algo::max_value(
        vertices.begin(), vertices.end(),
        [&](const kvector_t& vertex) -> double { return rotation.transformed(vertex).z(); });
}
