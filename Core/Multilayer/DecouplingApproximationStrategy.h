// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DecouplingApproximationStrategy.h
//! @brief     Defines classes DecouplingApproximationStrategy1 and
//!              DecouplingApproximationStrategy2
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECOUPLINGAPPROXIMATIONSTRATEGY_H
#define DECOUPLINGAPPROXIMATIONSTRATEGY_H

#include "IInterferenceFunctionStrategy.h"

class SimulationElement;

//! Strategy class to compute the total scalar scattering from a decorated layer
//! in decoupling approximation.
//! @ingroup algorithms_internal

class BA_CORE_API_ DecouplingApproximationStrategy1 final : public IInterferenceFunctionStrategy1
{
public:
    DecouplingApproximationStrategy1(SimulationOptions sim_params)
        : IInterferenceFunctionStrategy(sim_params)
    {
    }

private:
    double evaluateForList(const SimulationElement& sim_element) const final;
};

//! Strategy class to compute the total polarized scattering from a decorated layer
//! in decoupling approximation.
//! @ingroup algorithms_internal

class BA_CORE_API_ DecouplingApproximationStrategy2 final : public IInterferenceFunctionStrategy2
{
public:
    DecouplingApproximationStrategy2(SimulationOptions sim_params)
        : IInterferenceFunctionStrategy(sim_params)
    {
    }

private:
    double evaluateForList(const SimulationElement& sim_element) const final;
};

#endif // DECOUPLINGAPPROXIMATIONSTRATEGY_H
