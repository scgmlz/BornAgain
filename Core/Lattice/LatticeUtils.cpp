// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/LatticeUtils.cpp
//! @brief     Implements factory functions for different types of lattices and orientations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Lattice/LatticeUtils.h"
#include "Core/Lattice/ILatticeOrientation.h"

Lattice LatticeUtils::CreateFCCLattice(double lattice_constant,
                                       const ILatticeOrientation& orientation)
{
    Lattice prim_cubic = Lattice::createCubicLattice(1.0);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_cubic);
    auto rotation = P_orientation->transformationMatrix();
    Lattice fcc = Lattice::createFCCLattice(lattice_constant);
    return fcc.createTransformedLattice(rotation);
}

Lattice LatticeUtils::CreateHCPLattice(double a, double c, const ILatticeOrientation& orientation)
{
    Lattice prim_hexagonal = Lattice::createHexagonalLattice(1.0, c / a);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_hexagonal);
    auto rotation = P_orientation->transformationMatrix();
    Lattice hcp = Lattice::createHCPLattice(a, c);
    return hcp.createTransformedLattice(rotation);
}

Lattice LatticeUtils::CreateBCTLattice(double a, double c, const ILatticeOrientation& orientation)
{
    Lattice prim_tetragonal = Lattice::createTetragonalLattice(1.0, c / a);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_tetragonal);
    auto rotation = P_orientation->transformationMatrix();
    Lattice hcp = Lattice::createBCTLattice(a, c);
    return hcp.createTransformedLattice(rotation);
}
