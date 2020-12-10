//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/FormFactorPrecompute.h
//! @brief     Defines helper functions for InterferenceFunctions and Strategies.
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
#ifndef BORNAGAIN_SAMPLE_INTERFERENCE_FORMFACTORPRECOMPUTE_H
#define BORNAGAIN_SAMPLE_INTERFERENCE_FORMFACTORPRECOMPUTE_H

#include "Base/Types/Complex.h"
#include <Eigen/StdVector>
#include <vector>

class FormFactorCoherentSum;
class SimulationElement;

namespace FormFactorPrecompute {
using matrixFFVector_t = std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd>>;

std::vector<complex_t> scalar(const SimulationElement& sim_element,
                              const std::vector<FormFactorCoherentSum>& ff_wrappers);
matrixFFVector_t polarized(const SimulationElement& sim_element,
                           const std::vector<FormFactorCoherentSum>& ff_wrappers);

} // namespace FormFactorPrecompute

#endif // BORNAGAIN_SAMPLE_INTERFERENCE_FORMFACTORPRECOMPUTE_H
#endif // USER_API
