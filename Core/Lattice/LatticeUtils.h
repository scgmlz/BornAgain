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

#ifndef BORNAGAIN_CORE_LATTICE_LATTICEUTILS_H
#define BORNAGAIN_CORE_LATTICE_LATTICEUTILS_H

#include "Core/Lattice/Lattice.h"
#include "Core/Vector/Vectors3D.h"

class ILatticeOrientation;

namespace LatticeUtils
{
BA_CORE_API_ Lattice CreateFCCLattice(double lattice_constant,
                                      const ILatticeOrientation& orientation);
BA_CORE_API_ Lattice CreateHCPLattice(double a, double c, const ILatticeOrientation& orientation);
BA_CORE_API_ Lattice CreateBCTLattice(double a, double c, const ILatticeOrientation& orientation);
} // namespace LatticeUtils

#endif // BORNAGAIN_CORE_LATTICE_LATTICEUTILS_H
