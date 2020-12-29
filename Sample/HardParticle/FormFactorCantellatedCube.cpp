//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/HardParticle/FormFactorCantellatedCube.cpp
//! @brief     Implements class FormFactorCantellatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/FormFactorCantellatedCube.h"

const PolyhedralTopology FormFactorCantellatedCube::topology = {
    {
        /*  0 */ {{0, 1, 2, 3}, true},
        /*  1 */ {{0, 8, 5, 1}, true},
        /*  2 */ {{1, 9, 6, 2}, true},
        /*  3 */ {{2, 10, 7, 3}, true},
        /*  4 */ {{3, 11, 4, 0}, true},
        /*  5 */ {{0, 4, 8}, false},
        /*  6 */ {{1, 5, 9}, false},
        /*  7 */ {{2, 6, 10}, false},
        /*  8 */ {{3, 7, 11}, false},
        /*  9 */ {{4, 12, 16, 8}, true},
        /* 10 */ {{5, 13, 17, 9}, true},
        /* 11 */ {{4, 11, 19, 12}, true},
        /* 12 */ {{5, 8, 16, 13}, true},
        /* 13 */ {{7, 10, 18, 15}, true},
        /* 14 */ {{6, 9, 17, 14}, true},
        /* 15 */ {{7, 15, 19, 11}, true},
        /* 16 */ {{6, 14, 18, 10}, true},
        /* 17 */ {{13, 21, 17}, false},
        /* 18 */ {{12, 20, 16}, false},
        /* 19 */ {{15, 23, 19}, false},
        /* 20 */ {{14, 22, 18}, false},
        /* 21 */ {{14, 17, 21, 22}, true},
        /* 22 */ {{13, 16, 20, 21}, true},
        /* 23 */ {{12, 19, 23, 20}, true},
        /* 24 */ {{15, 18, 22, 23}, true},
        /* 25 */ {{20, 23, 22, 21}, true},
    },
    true};

FormFactorCantellatedCube::FormFactorCantellatedCube(const std::vector<double> P)
    : IFormFactorPolyhedron(
        {"CantellatedCube",
         "a cube with truncated edges and vertices",
         {{"Length", "nm", "length of untruncated edge", 0, +INF, 0},
          {"RemovedLength", "nm",
           "side length of the trirectangular tetrahedron removed one corner", 0, +INF, 0}}},
        P)
    , m_length(m_P[0])
    , m_removed_length(m_P[1])
{
    onChange();
}

FormFactorCantellatedCube::FormFactorCantellatedCube(double length, double removed_length)
    : FormFactorCantellatedCube(std::vector<double>{length, removed_length})
{
}

void FormFactorCantellatedCube::onChange()
{
    if (m_removed_length > 0.5 * m_length) {
        std::ostringstream ostr;
        ostr << "::FormFactorCantellatedCube() -> Error in class initialization ";
        ostr << "with parameters 'length':" << m_length;
        ostr << " 'removed_length':" << m_removed_length << "\n\n";
        ostr << "Check for removed_length <= 0.5*length failed.";
        throw std::runtime_error(ostr.str());
    }
    double a = m_length / 2;
    double c = a - m_removed_length;

    setPolyhedron(topology, -a, {{-c, -c, +a}, // point 0
                                 {+c, -c, +a}, {+c, +c, +a}, {-c, +c, +a},
                                 {-a, -c, +c}, // point 4
                                 {+c, -a, +c}, {+a, +c, +c}, {-c, +a, +c},
                                 {-c, -a, +c}, // point 8
                                 {+a, -c, +c}, {+c, +a, +c}, {-a, +c, +c},
                                 {-a, -c, -c}, // point 12
                                 {+c, -a, -c}, {+a, +c, -c}, {-c, +a, -c},
                                 {-c, -a, -c}, // point 16
                                 {+a, -c, -c}, {+c, +a, -c}, {-a, +c, -c},
                                 {-c, -c, -a}, // point 20
                                 {+c, -c, -a}, {+c, +c, -a}, {-c, +c, -a}});
}
