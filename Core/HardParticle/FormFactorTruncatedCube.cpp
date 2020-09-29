// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedCube.cpp
//! @brief     Implements class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorTruncatedCube.h"
#include "Core/Basics/Exceptions.h"

const PolyhedralTopology FormFactorTruncatedCube::topology = {
    {{{0, 1, 7, 6, 9, 10, 4, 3}, true},
     {{0, 2, 1}, false},
     {{3, 4, 5}, false},
     {{9, 11, 10}, false},
     {{6, 7, 8}, false},
     {{0, 3, 5, 17, 15, 12, 14, 2}, true},
     {{4, 10, 11, 23, 22, 16, 17, 5}, true},
     {{1, 2, 14, 13, 19, 20, 8, 7}, true},
     {{6, 8, 20, 18, 21, 23, 11, 9}, true},
     {{15, 17, 16}, false},
     {{12, 13, 14}, false},
     {{18, 20, 19}, false},
     {{21, 22, 23}, false},
     {{12, 15, 16, 22, 21, 18, 19, 13}, true}},
    true};

//! Constructor of a truncated cube.
//! @param length: length of the full cube's edge in nanometers
//! @param removed_length: removed length from each edge of the cube in nanometers
FormFactorTruncatedCube::FormFactorTruncatedCube(const std::vector<double> P)
    : IFormFactorPolyhedron({"TruncatedCube",
                             "class_tooltip",
                             {{"Length", "nm", "para_tooltip", 0, +INF, 0},
                              {"RemovedLength", "nm", "para_tooltip", 0, +INF, 0}}},
                            P),
      m_length(m_P[0]), m_removed_length(m_P[1])
{
    onChange();
}

FormFactorTruncatedCube::FormFactorTruncatedCube(double length, double removed_length)
    : FormFactorTruncatedCube(std::vector<double>{length, removed_length})
{
}

void FormFactorTruncatedCube::onChange()
{
    if (m_removed_length > 0.5 * m_length) {
        std::ostringstream ostr;
        ostr << "::FormFactorTruncatedCube() -> Error in class initialization ";
        ostr << "with parameters 'length':" << m_length;
        ostr << " 'removed_length':" << m_removed_length << "\n\n";
        ostr << "Check for removed_length <= 0.5*length failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double a = m_length / 2;
    double b = m_removed_length;

    setPolyhedron(topology, -a,
                  {{-a + b, -a, -a}, {-a, -a + b, -a}, {-a, -a, -a + b}, {a - b, -a, -a},
                   {a, -a + b, -a},  {a, -a, -a + b},  {-a + b, a, -a},  {-a, a - b, -a},
                   {-a, a, -a + b},  {a - b, a, -a},   {a, a - b, -a},   {a, a, -a + b},
                   {-a + b, -a, a},  {-a, -a + b, a},  {-a, -a, a - b},  {a - b, -a, a},
                   {a, -a + b, a},   {a, -a, a - b},   {-a + b, a, a},   {-a, a - b, a},
                   {-a, a, a - b},   {a - b, a, a},    {a, a - b, a},    {a, a, a - b}});
}
