// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPyramid.cpp
//! @brief     Implements class FormFactorPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPyramid.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"

const PolyhedralTopology FormFactorPyramid::topology = {
    {
        { { 3, 2, 1, 0 }, true }, // TODO -> true
        { { 0, 1, 5, 4 }, false },
        { { 1, 2, 6, 5 }, false },
        { { 2, 3, 7, 6 }, false },
        { { 3, 0, 4, 7 }, false },
        { { 4, 5, 6, 7 }, true } // TODO -> true
    },
    false
};

//! @param base_edge of one side of the square base
//! @param height    of the frustum
//! @param alpha:    dihedral angle in radians between base and facet

FormFactorPyramid::FormFactorPyramid(double base_edge, double height, double alpha)
    : FormFactorPolyhedron(), m_base_edge(base_edge), m_height(height), m_alpha(alpha)
{
    setName(BornAgain::FFPyramidType);
    registerParameter(BornAgain::BaseEdge, &m_base_edge).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Alpha, &m_alpha).setUnit("rad").setLimited(0., M_PI_2);
    onChange();
}

void FormFactorPyramid::onChange()
{
    double cot_alpha = MathFunctions::cot(m_alpha);
    if (!std::isfinite(cot_alpha) || cot_alpha < 0)
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    double r = cot_alpha * 2 * m_height / m_base_edge; // L(top)/L(base)
    if (r > 1) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters";
        ostr << " base_edge:" << m_base_edge;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= base_edge*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double a = m_base_edge / 2;
    double b = a * (1 - r);

    double zcom = m_height * (.5 - 2 * r / 3 + r * r / 4) / (1 - r + r * r / 3); // center of mass

    setPolyhedron(
        topology, -zcom, { // base:
                           { -a, -a, -zcom },
                           { a, -a, -zcom },
                           { a, a, -zcom },
                           { -a, a, -zcom },
                           // top:
                           { -b, -b, m_height - zcom },
                           { b, -b, m_height - zcom },
                           { b, b, m_height - zcom },
                           { -b, b, m_height - zcom } });
}
