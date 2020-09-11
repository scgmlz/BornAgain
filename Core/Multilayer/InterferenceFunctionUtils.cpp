// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/InterferenceFunctionUtils.cpp
//! @brief     Implements helper functions for InterferenceFunctions and Strategies.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/InterferenceFunctionUtils.h"
#include "Core/Multilayer/FormFactorCoherentSum.h"

namespace InterferenceFunctionUtils
{
std::vector<complex_t>
PrecomputeScalarFormFactors(const SimulationElement& sim_element,
                            const std::vector<FormFactorCoherentSum>& ff_wrappers)
{
    std::vector<complex_t> result;
    for (auto& ffw : ff_wrappers) {
        result.push_back(ffw.evaluate(sim_element));
    }
    return result;
}

matrixFFVector_t
PrecomputePolarizedFormFactors(const SimulationElement& sim_element,
                               const std::vector<FormFactorCoherentSum>& ff_wrappers)
{
    matrixFFVector_t result;
    for (auto& ffw : ff_wrappers) {
        result.push_back(ffw.evaluatePol(sim_element));
    }
    return result;
}
} // namespace InterferenceFunctionUtils
