// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputation.h
//! @brief     Defines interface IComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ICOMPUTATION_H
#define ICOMPUTATION_H

#include "ComputationStatus.h"
#include "IComputationTerm.h"
#include "SimulationOptions.h"
#include <memory>
#include <vector>

class MultiLayer;
class ProgressHandler;

//! Interface for a single-threaded computation with given range of SimulationElements
//! and ProgressHandler.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class IComputation
{
protected:
    struct IIterHandler;
public:
    IComputation(const SimulationOptions& options,
                 const std::shared_ptr<ProgressHandler>& progress,
                 std::unique_ptr<IIterHandler> iter_holder,
                 const MultiLayer& sample);
    virtual ~IComputation();

    void run();

    bool isCompleted() const { return m_status.isCompleted(); }
    std::string errorMessage() const { return m_status.errorMessage(); }

protected:
    struct IIterHandler
    {
        virtual ~IIterHandler() = default;
        virtual void eval(const IComputationTerm& comp_term) const = 0;
    };

    template<typename Iter>
    struct IterHandler : IIterHandler
    {
        explicit IterHandler(const Iter& begin, const Iter& end) : m_begin(begin), m_end(end) {}
        virtual void eval(const IComputationTerm& comp_term) const override
        {
            comp_term.eval(m_begin, m_end);
        }

        Iter m_begin, m_end;
    };

    virtual void runProtected() = 0;

    SimulationOptions m_sim_options;
    std::shared_ptr<ProgressHandler> m_progress;
    std::unique_ptr<IIterHandler> m_iter_holder; //!< defines the span of detector bins this simulation will work on
    ComputationStatus m_status;
    std::unique_ptr<MultiLayer> mP_multi_layer;
};

#endif // ICOMPUTATION_H
