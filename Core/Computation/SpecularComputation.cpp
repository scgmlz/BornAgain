// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputation.cpp
//! @brief     Implements class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IFresnelMap.h"
#include "SpecularComputation.h"
#include "MultiLayer.h"
#include "ProcessedSample.h"
#include "ProgressHandler.h"
#include "SpecularSimulationElement.h"


static_assert(std::is_copy_constructible<SpecularComputation>::value == false,
              "SpecularComputation should not be copy constructible");
static_assert(std::is_copy_assignable<SpecularComputation>::value == false,
              "SpecularComputation should not be copy assignable");

SpecularComputation::SpecularComputation(const MultiLayer& multilayer,
                                         const SimulationOptions& options,
                                         ProgressHandler& progress, SpecularElementIter begin_it,
                                         SpecularElementIter end_it)
    : IComputation(multilayer, options, progress)
    , m_begin_it(begin_it)
    , m_end_it(end_it)
{
    if (mP_processed_sample->containsMagneticMaterial()
        || mP_processed_sample->externalField() != kvector_t{})
        m_computation_term.reset(new SpecularMatrixTerm{
            static_cast<SpecularMagneticStrategy*>(this->mP_processed_sample->fresnelMap()->getStrategy()) });
    else
        m_computation_term.reset(new SpecularScalarTerm{
            static_cast<SpecularScalarStrategy*>(this->mP_processed_sample->fresnelMap()->getStrategy()) });
}

SpecularComputation::~SpecularComputation() = default;

void SpecularComputation::runProtected()
{
    if (!mp_progress->alive())
        return;

    m_computation_term->setProgressHandler(mp_progress);
    auto& slices = mP_processed_sample->averageSlices();
    for (auto it = m_begin_it; it != m_end_it; ++it)
        m_computation_term->compute(*it, slices);
}
