// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Hash2Doubles.cpp
//! @brief     Implements class Hash2Doubles.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Hash2Doubles.h"

//! Returns hash value of a pair of doubles, computed by exclusive-or of the component hash values.
size_t Hash2Doubles::operator()(std::pair<double, double> doubles) const noexcept
{
    return std::hash<double>{}(doubles.first) ^ std::hash<double>{}(doubles.second);
}
