// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Precomputed.cpp
//! @brief     Implements class Precomputed, providing precomputed constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Precomputed.h"
#include <cmath>

//! Precompute things upon class instantiation.

Precomputed::Precomputed()
{
    // Precompute the factorial: factorial[k] = k!
    double fac = 1;
    for (int k = 1; std::isfinite(fac); ++k) {
        factorial.push_back(fac);
        fac *= k;
    }
    // Precompute the reciprocal factorial: reciprocal_factorial[k] = 1/k!
    for (size_t k = 0; k < factorial.size(); ++k) {
        reciprocal_factorial.push_back(1 / factorial[k]);
    }
}
