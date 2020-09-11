// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DecouplingApproximationStrategy.h
//! @brief     Defines class DecouplingApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_DECOUPLINGAPPROXIMATIONSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_DECOUPLINGAPPROXIMATIONSTRATEGY_H

#include "Core/Multilayer/IInterferenceFunctionStrategy.h"

class SimulationElement;

//! Strategy class to compute the total scattering from a particle layout
//! in the decoupling approximation.
//! @ingroup algorithms_internal

class DecouplingApproximationStrategy final : public IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy(SimulationOptions sim_params, bool polarized);

private:
    double scalarCalculation(const SimulationElement& sim_element) const override;
    double polarizedCalculation(const SimulationElement& sim_element) const override;
};

#endif // BORNAGAIN_CORE_MULTILAYER_DECOUPLINGAPPROXIMATIONSTRATEGY_H
