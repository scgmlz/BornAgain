// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBAComputation.h
//! @brief     Defines class DWBAComputation.
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

#include "IComputation.h"
#include "Complex.h"
#include "SimulationOptions.h"

class IFresnelMap;
class MultiLayer;
struct HomogeneousRegion;
class IComputationTerm;

//! Performs a single-threaded DWBA computation with given sample and simulation parameters.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class DWBAComputation : public IComputation
{
public:
    DWBAComputation(
        const MultiLayer& multilayer,
        const SimulationOptions& options,
        ProgressHandler& progress,
        const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it);
    ~DWBAComputation();

    void run();

    static_assert(std::is_copy_constructible<DWBAComputation>::value==false,
                  "DWBAComputation should not be copy constructable");
    static_assert(std::is_copy_assignable<DWBAComputation>::value==false,
                  "DWBAComputation should not be copy assignable");
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

    //! contains the information, necessary to calculate the Fresnel coefficients
    std::unique_ptr<IFresnelMap> mP_fresnel_map;

    std::vector<std::unique_ptr<IComputationTerm>> m_computation_terms;
};

#endif // MAINCOMPUTATION_H
