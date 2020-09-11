// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBAComputation.h
//! @brief     Defines class DWBAComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_DWBACOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_DWBACOMPUTATION_H

#include "Core/Computation/DWBASingleComputation.h"
#include "Core/Computation/IComputation.h"
#include "Core/Parametrization/SimulationOptions.h"

class MultiLayer;
class SimulationElement;

//! Performs a single-threaded DWBA computation with given sample and simulation parameters.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class DWBAComputation : public IComputation
{
public:
    DWBAComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                    ProgressHandler& progress, std::vector<SimulationElement>::iterator begin_it,
                    std::vector<SimulationElement>::iterator end_it);
    ~DWBAComputation() override;

private:
    void runProtected() override;

    //! These iterators define the span of detector bins this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;
    //! Contains the information, necessary to calculate the Fresnel coefficients.
    DWBASingleComputation m_single_computation;
};

#endif // BORNAGAIN_CORE_COMPUTATION_DWBACOMPUTATION_H
