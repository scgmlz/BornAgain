//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/BakeLattice.h
//! @brief     Defines class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_LATTICE_BAKELATTICE_H
#define BORNAGAIN_SAMPLE_LATTICE_BAKELATTICE_H

class Lattice3D;

//! Functions that instantiate objects. To be used like constructors.

namespace bake {

//! Returns a primitive cubic (cP) lattice with edge length a.
Lattice3D CubicLattice(double a);

//! Returns a face-centered cubic (cF) lattice with edge length a.
Lattice3D FCCLattice(double a);

//! Returns a primitive hexagonal (hP) lattice with hexagonal edge a and height c.
Lattice3D HexagonalLattice(double a, double c);

//! TODO: Clarify how this is meant: HCP is not a Bravais lattice.
Lattice3D HCPLattice(double a, double c);

//! Returns a primitive tetragonal (tP) lattice with square base edge a and height c.
Lattice3D TetragonalLattice(double a, double c);

//! Returns a body-centered cubic (cI) lattice with edge length a.
//! TODO: Clarify meaning of c
Lattice3D BCTLattice(double a, double c);

} // namespace bake

#endif // BORNAGAIN_SAMPLE_LATTICE_BAKELATTICE_H
