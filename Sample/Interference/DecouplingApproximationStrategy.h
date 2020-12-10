//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/DecouplingApproximationStrategy.h
//! @brief     Defines class DecouplingApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_INTERFERENCE_DECOUPLINGAPPROXIMATIONSTRATEGY_H
#define BORNAGAIN_SAMPLE_INTERFERENCE_DECOUPLINGAPPROXIMATIONSTRATEGY_H

#include "Sample/Interference/IInterferenceFunctionStrategy.h"

class SimulationElement;

//! Strategy class to compute the total scattering from a particle layout
//! in the decoupling approximation.
//! @ingroup algorithms_internal

class DecouplingApproximationStrategy : public IInterferenceFunctionStrategy {
public:
    DecouplingApproximationStrategy(const std::vector<FormFactorCoherentSum>& weighted_formfactors,
                                    const IInterferenceFunction* iff, SimulationOptions sim_params,
                                    bool polarized);

private:
    double scalarCalculation(const SimulationElement& sim_element) const override;
    double polarizedCalculation(const SimulationElement& sim_element) const override;

    std::unique_ptr<IInterferenceFunction> m_iff;
};

#endif // BORNAGAIN_SAMPLE_INTERFERENCE_DECOUPLINGAPPROXIMATIONSTRATEGY_H
#endif // USER_API
