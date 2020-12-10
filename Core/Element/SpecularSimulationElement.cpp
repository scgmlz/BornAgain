//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Element/SpecularSimulationElement.cpp
//! @brief     Implements the class SpecularSimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Element/SpecularSimulationElement.h"
#include "Device/Detector/IDetector.h"
#include "Device/Instrument/Instrument.h"
#include "Sample/Slice/KzComputation.h"

SpecularSimulationElement::SpecularSimulationElement(double kz, const Instrument& instrument,
                                                     bool computable)
    : m_polarization(instrument.beam().getPolarization(),
                     instrument.detector().detectionProperties().analyzerOperator())
    , m_intensity(0.0)
    , m_computable(computable)
    , m_kz_computation([kz](const std::vector<Slice>& slices) {
        return KzComputation::computeKzFromSLDs(slices, kz);
    }) {}

SpecularSimulationElement::SpecularSimulationElement(double wavelength, double alpha,
                                                     const Instrument& instrument, bool computable)
    : m_polarization(instrument.beam().getPolarization(),
                     instrument.detector().detectionProperties().analyzerOperator())
    , m_intensity(0.0)
    , m_computable(computable)
    , m_kz_computation(
          [k = vecOfLambdaAlphaPhi(wavelength, alpha, 0.0)](const std::vector<Slice>& slices) {
              return KzComputation::computeKzFromRefIndices(slices, k);
          }) {}

SpecularSimulationElement::SpecularSimulationElement(const SpecularSimulationElement& other)
    : m_polarization(other.m_polarization)
    , m_intensity(other.m_intensity)
    , m_computable(other.m_computable)
    , m_kz_computation(other.m_kz_computation) {}

SpecularSimulationElement::SpecularSimulationElement(SpecularSimulationElement&& other) noexcept
    : m_polarization(std::move(other.m_polarization))
    , m_intensity(other.m_intensity)
    , m_computable(other.m_computable)
    , m_kz_computation(std::move(other.m_kz_computation)) {}

SpecularSimulationElement::~SpecularSimulationElement() = default;

std::vector<complex_t> SpecularSimulationElement::produceKz(const std::vector<Slice>& slices) {
    return m_kz_computation(slices);
}
