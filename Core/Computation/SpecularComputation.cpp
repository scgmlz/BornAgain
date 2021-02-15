//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Core/Computation/SpecularComputation.cpp
//! @brief     Implements class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Computation/SpecularComputation.h"
#include "Base/Progress/ProgressHandler.h"
#include "Core/Element/SpecularSimulationElement.h"
#include "Core/Term/SpecularComputationTerm.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/Specular/SpecularStrategyBuilder.h"

static_assert(std::is_copy_constructible<SpecularComputation>::value == false,
              "SpecularComputation should not be copy constructible");
static_assert(std::is_copy_assignable<SpecularComputation>::value == false,
              "SpecularComputation should not be copy assignable");

SpecularComputation::SpecularComputation(const MultiLayer& multilayer,
                                         const SimulationOptions& options,
                                         ProgressHandler& progress, SpecularElementIter begin_it,
                                         SpecularElementIter end_it)
    : IComputation(multilayer, options, progress), m_begin_it(begin_it), m_end_it(end_it)
{
    if (m_processed_sample->containsMagneticMaterial()
        || m_processed_sample->externalField() != kvector_t{}
        || options.isPolarized())
        m_computation_term.reset(
            new SpecularMatrixTerm(SpecularStrategyBuilder::build(multilayer, true)));
    else
        m_computation_term.reset(
            new SpecularScalarTerm(SpecularStrategyBuilder::build(multilayer, false)));
}

SpecularComputation::~SpecularComputation() = default;

void SpecularComputation::runProtected()
{
    if (!m_progress->alive())
        return;

    m_computation_term->setProgressHandler(m_progress);
    auto& slices = m_processed_sample->averageSlices();
    for (auto it = m_begin_it; it != m_end_it; ++it)
        m_computation_term->computeIntensity(*it, slices);
}
