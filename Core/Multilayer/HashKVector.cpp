// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/HashKVector.cpp
//! @brief     Implements class HashKVector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "HashKVector.h"
#include <functional> // hash

//! Returns hash value of a 3-vector, computed by exclusive-or of the component hash values.
size_t HashKVector::operator()(const kvector_t& kvec) const noexcept
{
    return std::hash<double>{}(kvec.x())
         ^ std::hash<double>{}(kvec.y())
         ^ std::hash<double>{}(kvec.z());
}
