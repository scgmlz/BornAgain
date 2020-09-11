// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/InterferenceFunctionUtils.h
//! @brief     Defines helper functions for InterferenceFunctions and Strategies.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_INTERFERENCEFUNCTIONUTILS_H
#define BORNAGAIN_CORE_MULTILAYER_INTERFERENCEFUNCTIONUTILS_H

#include "Core/Basics/Complex.h"
#include <Eigen/StdVector>
#include <vector>

class FormFactorCoherentSum;
class SimulationElement;

namespace InterferenceFunctionUtils
{
using matrixFFVector_t = std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd>>;

std::vector<complex_t>
PrecomputeScalarFormFactors(const SimulationElement& sim_element,
                            const std::vector<FormFactorCoherentSum>& ff_wrappers);
matrixFFVector_t
PrecomputePolarizedFormFactors(const SimulationElement& sim_element,
                               const std::vector<FormFactorCoherentSum>& ff_wrappers);

} // namespace InterferenceFunctionUtils

#endif // BORNAGAIN_CORE_MULTILAYER_INTERFERENCEFUNCTIONUTILS_H
