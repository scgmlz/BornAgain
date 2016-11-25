// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MainComputation.h
//! @brief     Defines class MainComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MAINCOMPUTATION_H
#define MAINCOMPUTATION_H

#include "Complex.h"
#include "ComputationOutcome.h"
#include "INoncopyable.h"
#include "SimulationOptions.h"
#include <vector>

class MultiLayer;
class DecoratedLayerComputation;
class RoughMultiLayerComputation;
class SpecularComputation;
class ProgressHandler;
class SimulationElement;

//! Performs a single-threaded DWBA computation with given sample and simulation parameters,
//! for a given span of detector bins.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class MainComputation final : public INoncopyable
{
public:
    MainComputation(
        const MultiLayer* p_multi_layer, const SimulationOptions& options,
        ProgressHandler& progress, const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it);
    ~MainComputation();

    void run();

    bool isCompleted() const { return m_outcome.isCompleted(); }
    std::string getRunMessage() const { return m_outcome.getRunMessage(); }

private:
    void runProtected();

    //! calculates intensity map for samples with magnetization
    void collectRTCoefficientsScalar();
    void collectRTCoefficientsMatrix();

    MultiLayer* mp_multi_layer;
    SimulationOptions m_sim_options;
    ProgressHandler* m_progress;
    //! these iterators define the span of detector bins this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    RoughMultiLayerComputation* mp_roughness_computation;
    SpecularComputation* mp_specular_computation;
    std::vector<std::vector<DecoratedLayerComputation*>> m_layer_computation;

    ComputationOutcome m_outcome;
};

#endif // MAINCOMPUTATION_H
