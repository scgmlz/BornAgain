// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/KernelTypes.h
//! @brief     Defines common types for fitting library.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef KERNELTYPES_H
#define KERNELTYPES_H

#include <functional>
#include <vector>

typedef std::function<double(const std::vector<double>&)> objective_function_t;

typedef std::function<double(const std::vector<double>&, unsigned int, std::vector<double>&)>
    gradient_function_t;

typedef std::function<double(const double*)> root_objective_t;

typedef std::function<double(const double*, unsigned int, double*)> root_gradient_t;

#endif // KERNELTYPES_H
