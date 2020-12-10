//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/ComputeBAPol.cpp
//! @brief     Defines class ComputeBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/FFCompute/ComputeBAPol.h"
#include "Sample/Material/WavevectorInfo.h"
#include <stdexcept>

ComputeBAPol::ComputeBAPol(const IFormFactor& ff) : IComputeFF(ff) {}

ComputeBAPol::~ComputeBAPol() = default;

ComputeBAPol* ComputeBAPol::clone() const {
    return new ComputeBAPol(*m_ff);
}

complex_t ComputeBAPol::evaluate(const WavevectorInfo&) const {
    throw std::runtime_error("ComputeBAPol::evaluate: "
                             "should never be called for matrix interactions");
}

Eigen::Matrix2cd ComputeBAPol::evaluatePol(const WavevectorInfo& wavevectors) const {
    Eigen::Matrix2cd ff_BA = m_ff->evaluatePol(wavevectors);
    Eigen::Matrix2cd result;
    result(0, 0) = -ff_BA(1, 0);
    result(0, 1) = ff_BA(0, 0);
    result(1, 0) = -ff_BA(1, 1);
    result(1, 1) = ff_BA(0, 1);
    return result;
}
