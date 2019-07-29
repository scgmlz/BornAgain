// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/LatticeUtils.h
//! @brief     Defines factory functions for different types of lattices and orientations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef LATTICEUTILS_H
#define LATTICEUTILS_H

#include "Lattice.h"
#include "Vectors3D.h"

class ILatticeOrientation;

namespace LatticeUtils
{
BA_CORE_API_ Lattice CreateFCCLattice(double lattice_constant,
                                      const ILatticeOrientation& orientation);
BA_CORE_API_ Lattice CreateHCPLattice(double a, double c,
                                      const ILatticeOrientation& orientation);
BA_CORE_API_ Lattice CreateBCTLattice(double a, double c,
                                      const ILatticeOrientation& orientation);
}  // namespace LatticeUtils

#endif // LATTICEUTILS_H
