// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDodecahedron.cpp
//! @brief     Implements class FormFactorDodecahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorDodecahedron.h"

const PolyhedralTopology FormFactorDodecahedron::topology = {{// bottom:
                                                              {{0, 4, 3, 2, 1}, false},
                                                              // lower ring:
                                                              {{0, 5, 12, 9, 4}, false},
                                                              {{4, 9, 11, 8, 3}, false},
                                                              {{3, 8, 10, 7, 2}, false},
                                                              {{2, 7, 14, 6, 1}, false},
                                                              {{1, 6, 13, 5, 0}, false},
                                                              // upper ring:
                                                              {{8, 11, 16, 15, 10}, false},
                                                              {{9, 12, 17, 16, 11}, false},
                                                              {{5, 13, 18, 17, 12}, false},
                                                              {{6, 14, 19, 18, 13}, false},
                                                              {{7, 10, 15, 19, 14}, false},
                                                              // top:
                                                              {{15, 16, 17, 18, 19}, false}},
                                                             true};

//! Constructor of a dodecahedron.
//! @param edge: length of the edge in nanometers
FormFactorDodecahedron::FormFactorDodecahedron(const std::vector<double> P)
    : FormFactorPolyhedron(
        {"Dodecahedron", "class_tooltip", {{"Edge", "nm", "para_tooltip", 0, +INF, 0}}}, P),
      m_edge(m_P[0])
{
    onChange();
}

FormFactorDodecahedron::FormFactorDodecahedron(double edge)
    : FormFactorDodecahedron(std::vector<double>{edge})
{
}

void FormFactorDodecahedron::onChange()
{
    double a = m_edge;
    setPolyhedron(topology, -1.113516364411607 * a,
                  {{0.8506508083520399 * a, 0 * a, -1.113516364411607 * a},
                   {0.2628655560595668 * a, 0.8090169943749473 * a, -1.113516364411607 * a},
                   {-0.6881909602355868 * a, 0.5 * a, -1.113516364411607 * a},
                   {-0.6881909602355868 * a, -0.5 * a, -1.113516364411607 * a},
                   {0.2628655560595668 * a, -0.8090169943749473 * a, -1.113516364411607 * a},
                   {1.376381920471174 * a, 0 * a, -0.2628655560595667 * a},
                   {0.42532540417602 * a, 1.309016994374947 * a, -0.2628655560595667 * a},
                   {-1.113516364411607 * a, 0.8090169943749475 * a, -0.2628655560595667 * a},
                   {-1.113516364411607 * a, -0.8090169943749475 * a, -0.2628655560595667 * a},
                   {0.42532540417602 * a, -1.309016994374947 * a, -0.2628655560595667 * a},
                   {-1.376381920471174 * a, 0 * a, 0.2628655560595667 * a},
                   {-0.42532540417602 * a, -1.309016994374947 * a, 0.2628655560595667 * a},
                   {1.113516364411607 * a, -0.8090169943749475 * a, 0.2628655560595667 * a},
                   {1.113516364411607 * a, 0.8090169943749475 * a, 0.2628655560595667 * a},
                   {-0.42532540417602 * a, 1.309016994374947 * a, 0.2628655560595667 * a},
                   {-0.8506508083520399 * a, 0 * a, 1.113516364411607 * a},
                   {-0.2628655560595668 * a, -0.8090169943749473 * a, 1.113516364411607 * a},
                   {0.6881909602355868 * a, -0.5 * a, 1.113516364411607 * a},
                   {0.6881909602355868 * a, 0.5 * a, 1.113516364411607 * a},
                   {-0.2628655560595668 * a, 0.8090169943749473 * a, 1.113516364411607 * a}});
    assert_platonic();
}
