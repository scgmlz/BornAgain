//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Vector/Direction.cpp
//! @brief     Implements class Direction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Vector/Direction.h"
#include "Base/Math/Constants.h"
#include <cmath>

kvector_t vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi) {
    return M_TWOPI / _lambda * Direction(_alpha, _phi).vector();
}

kvector_t Direction::vector() const {
    return {std::cos(m_alpha) * std::cos(m_phi), -std::cos(m_alpha) * std::sin(m_phi),
            std::sin(m_alpha)};
}
