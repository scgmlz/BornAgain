//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/BakeLattice.cpp
//! @brief     Implements class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Lattice/BakeLattice.h"
#include "Sample/Lattice/Lattice3D.h"

Lattice3D bake::CubicLattice(double a) {
    kvector_t a1(a, 0.0, 0.0);
    kvector_t a2(0.0, a, 0.0);
    kvector_t a3(0.0, 0.0, a);
    return Lattice3D(a1, a2, a3);
}

Lattice3D bake::FCCLattice(double a) {
    double b = a / 2.0;
    kvector_t a1(0.0, b, b);
    kvector_t a2(b, 0.0, b);
    kvector_t a3(b, b, 0.0);
    return Lattice3D(a1, a2, a3);
}

Lattice3D bake::HexagonalLattice(double a, double c) {
    kvector_t a1(a, 0.0, 0.0);
    kvector_t a2(-a / 2.0, std::sqrt(3.0) * a / 2.0, 0.0);
    kvector_t a3(0.0, 0.0, c);
    return Lattice3D(a1, a2, a3);
}

Lattice3D bake::HCPLattice(double a, double c) {
    kvector_t a1(a, 0.0, 0.0);
    kvector_t a2(-a / 2.0, std::sqrt(3.0) * a / 2.0, 0);
    kvector_t a3(a / 2.0, a / std::sqrt(3.0) / 2.0, c / 2.0);
    return Lattice3D(a1, a2, a3);
}

Lattice3D bake::TetragonalLattice(double a, double c) {
    kvector_t a1(a, 0.0, 0.0);
    kvector_t a2(0.0, a, 0.0);
    kvector_t a3(0.0, 0.0, c);
    return Lattice3D(a1, a2, a3);
}

Lattice3D bake::BCTLattice(double a, double c) {
    kvector_t a1(a, 0.0, 0.0);
    kvector_t a2(0.0, a, 0.0);
    kvector_t a3(a / 2.0, a / 2.0, c / 2.0);
    return Lattice3D(a1, a2, a3);
}
