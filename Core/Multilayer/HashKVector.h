// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/HashKVector.h
//! @brief     Defines class HashKVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef HASHKVECTOR_H
#define HASHKVECTOR_H

#include "Vectors3D.h"
#include <utility>

//! Provides a hash function for a 3-vector of doubles, for use in MatrixFresnelMap.
class HashKVector
{
public:
    size_t operator()(const kvector_t& kvec) const noexcept;
};

#endif // HASHKVECTOR_H
