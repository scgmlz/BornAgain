// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/PolyhedralTopology.h
//! @brief     Defines classes PolygonalTopology, PolyhedralTopology
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRALTOPOLOGY_H
#define BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRALTOPOLOGY_H

#include <vector>

//! For internal use in PolyhedralFace.
class PolygonalTopology
{
public:
    std::vector<int> vertexIndices;
    bool symmetry_S2;
};

//! For internal use in IFormFactorPolyhedron.
class PolyhedralTopology
{
public:
    std::vector<PolygonalTopology> faces;
    bool symmetry_Ci;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_POLYHEDRALTOPOLOGY_H
