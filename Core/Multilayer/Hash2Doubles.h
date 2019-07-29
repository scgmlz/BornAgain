// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Hash2Doubles.h
//! @brief     Defines class Hash2Doubles.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef HASH2DOUBLES_H
#define HASH2DOUBLES_H

#include <cstddef> // size_t
#include <utility> // pair

//! Provides a hash function for a pair of doubles, for use in ScalarFresnelMap.
class Hash2Doubles
{
public:
    size_t operator()(std::pair<double, double> doubles) const noexcept;
};

#endif // HASH2DOUBLES_H
