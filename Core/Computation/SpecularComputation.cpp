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

#include "SpecularComputation.h"
#include "Layer.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "ScalarFresnelMap.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

static_assert(std::is_copy_constructible<SpecularComputation>::value == false,
              "SpecularComputation should not be copy constructible");
static_assert(std::is_copy_assignable<SpecularComputation>::value == false,
              "SpecularComputation should not be copy assignable");

void SpecularComputation::init()
{
    mP_fresnel_map = createFresnelMap();
    m_computation_term.reset(
        new SpecularComputationTerm(mP_multi_layer.get(), mP_fresnel_map.get()));
}

SpecularComputation::~SpecularComputation() = default;

void SpecularComputation::runProtected()
{
    if (!m_progress->alive())
        return;
    m_iter_holder->eval(*m_computation_term);
}

std::unique_ptr<IFresnelMap> SpecularComputation::createFresnelMap()
{
    std::unique_ptr<IFresnelMap> P_result;

    if (!mP_multi_layer->requiresMatrixRTCoefficients())
        P_result.reset(new ScalarFresnelMap());
    else
        P_result.reset(new MatrixFresnelMap());

    if (m_sim_options.isIntegrate())
        P_result->disableCaching();

    if (m_sim_options.useAvgMaterials())
        throw std::runtime_error("Error in SpecularComputation::createFresnelMap: using averaged "
                                 "materials is not implemented");

    P_result->setMultilayer(*mP_multi_layer);
    return P_result;
}

