// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/Hash2Doubles.h
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

#include <functional>
#include <utility>

//! Provides a hash function for a pair of doubles, for use in ScalarFresnelMap.
class Hash2Doubles
{
public:
    Hash2Doubles() {}
    ~Hash2Doubles() {}

    size_t operator()(std::pair<double, double> doubles) const noexcept;
private:
    std::hash<double> m_double_hash;
};

#endif // HASH2DOUBLES_H
