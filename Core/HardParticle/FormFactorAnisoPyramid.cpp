// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorAnisoPyramid.cpp
//! @brief     Implements class FormFactorAnisoPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorAnisoPyramid.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"

const PolyhedralTopology FormFactorAnisoPyramid::topology = { { { { 3, 2, 1, 0 }, true },
                                                                { { 0, 1, 5, 4 }, false },
                                                                { { 1, 2, 6, 5 }, false },
                                                                { { 2, 3, 7, 6 }, false },
                                                                { { 3, 0, 4, 7 }, false },
                                                                { { 4, 5, 6, 7 }, true } },
                                                              false };

//! @param length of one side of the rectangular base
//! @param width  of other side of the rectangular base
//! @param height of frustum
//! @param alpha  dihedral angle in radians between base and facet
FormFactorAnisoPyramid::FormFactorAnisoPyramid(
    double length, double width, double height, double alpha)
    : FormFactorPolyhedron(), m_length(length), m_width(width), m_height(height), m_alpha(alpha)
{
    setName(BornAgain::FFAnisoPyramidType);
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Alpha, &m_alpha).setUnit("rad").setLimited(0., M_PI_2);
    onChange();
}

void FormFactorAnisoPyramid::onChange()
{
    double cot_alpha = MathFunctions::cot(m_alpha);
    if (!std::isfinite(cot_alpha) || cot_alpha < 0)
        throw Exceptions::OutOfBoundsException("AnisoPyramid: angle alpha out of bounds");
    double r = cot_alpha * 2 * m_height / m_length;
    double s = cot_alpha * 2 * m_height / m_width;
    if (r > 1 || s > 1) {
        std::ostringstream ostr;
        ostr << "FormFactorAnisoPyramid() -> Error in class initialization with parameters";
        ostr << " length:" << m_length;
        ostr << " width:" << m_width;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2*height <= (length,width)*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double D = m_length / 2;
    double d = m_length / 2 * (1 - r);
    double W = m_width / 2;
    double w = m_width / 2 * (1 - s);

    double zcom =
        m_height * (.5 - (r + s) / 3 + r * s / 4) / (1 - (r + s) / 2 + r * s / 3); // center of mass

    setPolyhedron(
        topology, -zcom, { // base:
                           { -D, -W, -zcom },
                           { D, -W, -zcom },
                           { D, W, -zcom },
                           { -D, W, -zcom },
                           // top:
                           { -d, -w, m_height - zcom },
                           { d, -w, m_height - zcom },
                           { d, w, m_height - zcom },
                           { -d, w, m_height - zcom } });
}
