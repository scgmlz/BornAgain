//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/IComputeFF.cpp
//! @brief     Implements interface class IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/FFCompute/IComputeFF.h"
#include "Sample/RT/ILayerRTCoefficients.h" // required by VS19 compiler
#include "Sample/Scattering/IFormFactor.h"
#include <stdexcept>

IComputeFF::IComputeFF(const IFormFactor& ff) : m_ff(ff.clone()) {}

IComputeFF::~IComputeFF() = default;

void IComputeFF::setAmbientMaterial(const Material& material) {
    m_ff->setAmbientMaterial(material);
}

double IComputeFF::volume() const {
    return m_ff->volume();
}

double IComputeFF::radialExtension() const {
    return m_ff->radialExtension();
}

double IComputeFF::bottomZ(const IRotation& rotation) const {
    return m_ff->bottomZ(rotation);
}

double IComputeFF::topZ(const IRotation& rotation) const {
    return m_ff->topZ(rotation);
}

Eigen::Matrix2cd IComputeFF::evaluatePol(const WavevectorInfo&) const {
    throw std::runtime_error("Bug: impossible call to FFCompute::evaluatePol");
}

void IComputeFF::setSpecularInfo(std::unique_ptr<const ILayerRTCoefficients>,
                                 std::unique_ptr<const ILayerRTCoefficients>) {}
