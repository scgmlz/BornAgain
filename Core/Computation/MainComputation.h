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

#include "ComputationStatus.h"
#include "Complex.h"
#include "INoncopyable.h"
#include "SimulationOptions.h"
#include <memory>
#include <vector>

class IFresnelMap;
class MultiLayer;
struct HomogeneousRegion;
class IComputationTerm;
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
        const MultiLayer& multilayer,
        const SimulationOptions& options,
        ProgressHandler& progress,
        const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it);
    ~MainComputation();

    void run();

    bool isCompleted() const { return m_status.isCompleted(); }
    std::string errorMessage() const { return m_status.errorMessage(); }

private:
    void runProtected();
    IFresnelMap* createFresnelMap();
    // creates a multilayer that contains averaged materials, for use in Fresnel calculations
    std::unique_ptr<MultiLayer> getAveragedMultilayer() const;
    // creates a multilayer for use in Fresnel calculations; if needed, it calculates average
    // materials and precalculates the magnetic B fields
    std::unique_ptr<MultiLayer> getMultilayerForFresnel() const;
    // sets the correct layer materials for the Fresnel map to use
    void initFresnelMap();
    bool checkRegions(const std::vector<HomogeneousRegion>& regions) const;

    std::unique_ptr<MultiLayer> mP_multi_layer;
    SimulationOptions m_sim_options;
    ProgressHandler* m_progress;
    //! these iterators define the span of detector bins this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    //! contains the information, necessary to calculate the Fresnel coefficients
    std::unique_ptr<IFresnelMap> mP_fresnel_map;

    std::vector<std::unique_ptr<IComputationTerm>> m_computation_terms;
    ComputationStatus m_status;
};

#endif // MAINCOMPUTATION_H
