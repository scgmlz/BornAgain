// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Vector/Vectors3D.h
//! @brief     Defines basic vectors in R^3 and C^3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_BASE_VECTOR_VECTORS3D_H
#define BORNAGAIN_BASE_VECTOR_VECTORS3D_H

#include "Base/Vector/BasicVector3D.h"

using ivector_t = BasicVector3D<int>;
using kvector_t = BasicVector3D<double>;
using cvector_t = BasicVector3D<std::complex<double>>;

#endif // BORNAGAIN_BASE_VECTOR_VECTORS3D_H
