// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedCube.cpp
//! @brief     Implements class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTruncatedCube.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "RealParameter.h"

const PolyhedralTopology FormFactorTruncatedCube::topology = {
    { { { 0, 1, 7, 6, 9, 10, 4, 3 }, true },
      { { 0, 2, 1 }, false },
      { { 3, 4, 5 }, false },
      { { 9, 11, 10 }, false },
      { { 6, 7, 8 }, false },
      { { 0, 3, 5, 17, 15, 12, 14, 2 }, true },
      { { 4, 10, 11, 23, 22, 16, 17, 5 }, true },
      { { 1, 2, 14, 13, 19, 20, 8, 7 }, true },
      { { 6, 8, 20, 18, 21, 23, 11, 9 }, true },
      { { 15, 17, 16 }, false },
      { { 12, 13, 14 }, false },
      { { 18, 20, 19 }, false },
      { { 21, 22, 23 }, false },
      { { 12, 15, 16, 22, 21, 18, 19, 13 }, true } },
    true
};

//! @param length         of the full cube
//! @param removed_length as removed from each edge of the cube

FormFactorTruncatedCube::FormFactorTruncatedCube(double length, double removed_length)
    : FormFactorPolyhedron(), m_length(length), m_removed_length(removed_length)
{
    setName(BornAgain::FFTruncatedCubeType);
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::RemovedLength, &m_removed_length).setUnit("nm").setNonnegative();
    onChange();
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

    setPolyhedron(topology, -a, { { -a + b, -a, -a }, { -a, -a + b, -a }, { -a, -a, -a + b },
                                  { a - b, -a, -a },  { a, -a + b, -a },  { a, -a, -a + b },
                                  { -a + b, a, -a },  { -a, a - b, -a },  { -a, a, -a + b },
                                  { a - b, a, -a },   { a, a - b, -a },   { a, a, -a + b },
                                  { -a + b, -a, a },  { -a, -a + b, a },  { -a, -a, a - b },
                                  { a - b, -a, a },   { a, -a + b, a },   { a, -a, a - b },
                                  { -a + b, a, a },   { -a, a - b, a },   { -a, a, a - b },
                                  { a - b, a, a },    { a, a - b, a },    { a, a, a - b } });
}
