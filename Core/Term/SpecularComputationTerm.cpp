//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Term/SpecularComputationTerm.cpp
//! @brief     Implements functor SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Term/SpecularComputationTerm.h"
#include "Base/Progress/DelayedProgressCounter.h"
#include "Core/Element/SpecularSimulationElement.h"
#include "Sample/RT/ILayerRTCoefficients.h"

//  ************************************************************************************************
//  class SpecularComputationTerm
//  ************************************************************************************************

SpecularComputationTerm::SpecularComputationTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : m_Strategy(std::move(strategy)){};

SpecularScalarTerm::SpecularScalarTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : SpecularComputationTerm(std::move(strategy)) {}

SpecularComputationTerm::~SpecularComputationTerm() = default;

void SpecularComputationTerm::setProgressHandler(ProgressHandler* p_progress) {
    m_progress_counter = std::make_unique<DelayedProgressCounter>(p_progress, 100);
}

void SpecularComputationTerm::computeIntensity(SpecularSimulationElement& elem,
                                               const std::vector<Slice>& slices) const {
    if (!elem.isCalculated())
        return;

    eval(elem, slices);

    if (m_progress_counter)
        m_progress_counter->stepProgress();
}

//  ************************************************************************************************
//  class SpecularScalarTerm
//  ************************************************************************************************

SpecularScalarTerm::~SpecularScalarTerm() = default;

void SpecularScalarTerm::eval(SpecularSimulationElement& elem,
                              const std::vector<Slice>& slices) const {
    const auto coeff = m_Strategy->Execute(slices, elem.produceKz(slices));
    elem.setIntensity(std::norm(coeff.front()->getScalarR()));
}

//  ************************************************************************************************
//  class SpecularMatrixTerm
//  ************************************************************************************************

namespace {

double matrix_intensity(const SpecularSimulationElement& elem,
                        const std::unique_ptr<const ILayerRTCoefficients>& coeff) {
    const auto& polarization = elem.polarizationHandler().getPolarization();
    const auto& analyzer = elem.polarizationHandler().getAnalyzerOperator();

    const auto R = coeff->getReflectionMatrix();

    const complex_t result = (polarization * R.adjoint() * analyzer * R).trace();

    return std::abs(result);
}

} // namespace

SpecularMatrixTerm::SpecularMatrixTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : SpecularComputationTerm(std::move(strategy)) {}

SpecularMatrixTerm::~SpecularMatrixTerm() = default;

void SpecularMatrixTerm::eval(SpecularSimulationElement& elem,
                              const std::vector<Slice>& slices) const {
    const auto coeff = m_Strategy->Execute(slices, elem.produceKz(slices));
    elem.setIntensity(matrix_intensity(elem, coeff.front()));
}
