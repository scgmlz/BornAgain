// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.cpp
//! @brief     Implements functor SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/SpecularComputationTerm.h"
#include "Core/Computation/DelayedProgressCounter.h"
#include "Core/Multilayer/SpecularScalarStrategy.h"
#include "Core/Multilayer/SpecularSimulationElement.h"
#include "Core/RT/ScalarRTCoefficients.h"

SpecularComputationTerm::SpecularComputationTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : m_Strategy(std::move(strategy)){};

SpecularScalarTerm::SpecularScalarTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : SpecularComputationTerm(std::move(strategy))
{
}

SpecularComputationTerm::~SpecularComputationTerm() = default;

void SpecularComputationTerm::setProgressHandler(ProgressHandler* p_progress)
{
    mP_progress_counter.reset(new DelayedProgressCounter(p_progress, 100));
}

void SpecularComputationTerm::compute(SpecularSimulationElement& elem,
                                      const std::vector<Slice>& slices) const
{
    if (!elem.isCalculated())
        return;

    eval(elem, slices);

    if (mP_progress_counter)
        mP_progress_counter->stepProgress();
}

SpecularScalarTerm::~SpecularScalarTerm() = default;

void SpecularScalarTerm::eval(SpecularSimulationElement& elem,
                              const std::vector<Slice>& slices) const
{
    auto coeff = m_Strategy->Execute(slices, elem.produceKz(slices));
    elem.setIntensity(std::norm(coeff.front()->getScalarR()));
}

SpecularMatrixTerm::SpecularMatrixTerm(std::unique_ptr<ISpecularStrategy> strategy)
    : SpecularComputationTerm(std::move(strategy))
{
}

SpecularMatrixTerm::~SpecularMatrixTerm() = default;

void SpecularMatrixTerm::eval(SpecularSimulationElement& elem,
                              const std::vector<Slice>& slices) const
{
    auto coeff = m_Strategy->Execute(slices, elem.produceKz(slices));
    elem.setIntensity(intensity(elem, coeff.front()));
}

double SpecularMatrixTerm::intensity(const SpecularSimulationElement& elem,
                                     ISpecularStrategy::single_coeff_t& coeff) const
{
    const auto& polarization = elem.polarizationHandler().getPolarization();
    const auto& analyzer = elem.polarizationHandler().getAnalyzerOperator();

    // constructing reflection operator
    Eigen::Matrix2cd R;
    R.col(0) = coeff->R1plus() + coeff->R2plus();
    R.col(1) = coeff->R1min() + coeff->R2min();

    const complex_t result = (polarization * R.adjoint() * analyzer * R).trace();

    return std::abs(result);
}
