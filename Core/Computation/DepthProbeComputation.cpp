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

#include "DepthProbeComputation.h"
#include "Layer.h"
#include "IFresnelMap.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "ScalarFresnelMap.h"
#include "ProgressHandler.h"

static_assert(std::is_copy_constructible<DepthProbeComputation>::value == false,
              "DepthProbeComputation should not be copy constructible");
static_assert(std::is_copy_assignable<DepthProbeComputation>::value == false,
              "DepthProbeComputation should not be copy assignable");

DepthProbeComputation::DepthProbeComputation(const MultiLayer& multilayer,
                                             const SimulationOptions& options,
                                             ProgressHandler& progress,
                                             DepthProbeElementIter begin_it,
                                             DepthProbeElementIter end_it)
    : IComputation(options, progress, multilayer)
    , m_begin_it(begin_it), m_end_it(end_it)
    , mP_fresnel_map(createFresnelMap())
    , m_computation_term(mP_multi_layer.get(), mP_fresnel_map.get())
{
}

DepthProbeComputation::~DepthProbeComputation() = default;

void DepthProbeComputation::runProtected()
{
    if (!m_progress->alive())
        return;
    m_computation_term.eval(m_progress, m_begin_it, m_end_it);
}

std::unique_ptr<IFresnelMap> DepthProbeComputation::createFresnelMap()
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
