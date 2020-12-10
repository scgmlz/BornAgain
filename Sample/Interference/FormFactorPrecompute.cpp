//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/FormFactorPrecompute.cpp
//! @brief     Implements helper functions for InterferenceFunctions and Strategies.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Interference/FormFactorPrecompute.h"
#include "Sample/Fresnel/FormFactorCoherentSum.h"

std::vector<complex_t>
FormFactorPrecompute::scalar(const SimulationElement& sim_element,
                             const std::vector<FormFactorCoherentSum>& ff_wrappers) {
    std::vector<complex_t> result;
    for (const auto& ffw : ff_wrappers)
        result.push_back(ffw.evaluate(sim_element));
    return result;
}

FormFactorPrecompute::matrixFFVector_t
FormFactorPrecompute::polarized(const SimulationElement& sim_element,
                                const std::vector<FormFactorCoherentSum>& ff_wrappers) {
    FormFactorPrecompute::matrixFFVector_t result;
    for (const auto& ffw : ff_wrappers)
        result.push_back(ffw.evaluatePol(sim_element));
    return result;
}
