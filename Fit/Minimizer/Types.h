//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/Types.h
//! @brief     Defines common types for fitting library.
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
#ifndef BORNAGAIN_FIT_MINIMIZER_TYPES_H
#define BORNAGAIN_FIT_MINIMIZER_TYPES_H

#include <functional>
#include <vector>

namespace mumufit {
class Parameters;
}

using scalar_function_t = std::function<double(const std::vector<double>&)>;

using gradient_function_t =
    std::function<double(const std::vector<double>&, unsigned int, std::vector<double>&)>;

using root_scalar_t = std::function<double(const double*)>;

using root_gradient_t = std::function<double(const double*, unsigned int, double*)>;

using fcn_scalar_t = std::function<double(const mumufit::Parameters&)>;
using fcn_residual_t = std::function<std::vector<double>(const mumufit::Parameters&)>;

#endif // BORNAGAIN_FIT_MINIMIZER_TYPES_H
#endif // USER_API
