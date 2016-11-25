// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCuboctahedron.cpp
//! @brief     Implements class FormFactorCuboctahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCuboctahedron.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"

const PolyhedralTopology FormFactorCuboctahedron::topology = { { { { 3, 2, 1, 0 }, true },
                                                                 { { 0, 1, 5, 4 }, false },
                                                                 { { 1, 2, 6, 5 }, false },
                                                                 { { 2, 3, 7, 6 }, false },
                                                                 { { 3, 0, 4, 7 }, false },
                                                                 { { 4, 5, 9, 8 }, false },
                                                                 { { 5, 6, 10, 9 }, false },
                                                                 { { 6, 7, 11, 10 }, false },
                                                                 { { 7, 4, 8, 11 }, false },
                                                                 { { 8, 9, 10, 11 }, true } },
                                                               false };

//! @param length        of one side of the square base
//! @param height        of bottom frustum
//! @param height_ratio: ratio of heights of top to bottom frustum
//! @param alpha:        dihedral angle in radians between base and facet
FormFactorCuboctahedron::FormFactorCuboctahedron(
    double length, double height, double height_ratio, double alpha)
    : FormFactorPolyhedron()
    , m_length(length)
    , m_height(height)
    , m_height_ratio(height_ratio)
    , m_alpha(alpha)
{
    setName(BornAgain::FFCuboctahedronType);
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::HeightRatio, &m_height_ratio).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Alpha, &m_alpha).setUnit("rad").setLimited(0., M_PI_2);
    onChange();
}

void FormFactorCuboctahedron::onChange()
{
    double cot_alpha = MathFunctions::cot(m_alpha);
    if (!std::isfinite(cot_alpha) || cot_alpha < 0)
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    double x = m_height_ratio;
    double r = cot_alpha * 2 * m_height / m_length;
    if (std::max(1., x) * r > 1) {
        std::ostringstream ostr;
        ostr << "FormFactorCuboctahedron() -> Error in class initialization with parameters";
        ostr << " height:" << m_height;
        ostr << " length:" << m_length;
        ostr << " height_ratio:" << m_height_ratio;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2.*height <= length*tan(alpha)*min(1.,1.0/height_ratio)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    double a = m_length / 2 * (1 - r);
    double b = m_length / 2;
    double c = m_length / 2 * (1 - r * x);

    double dzcom = m_height
        * ((x * x - 1) / 2 - 2 * r * (x * x * x - 1) / 3 + r * r * (x * x * x * x - 1) / 4)
        / ((x + 1) - r * (x * x + 1) + r * r * (x * x * x + 1) / 3);
    double za = -dzcom - m_height;
    double zb = -dzcom;
    double zc = -dzcom + x * m_height;

    setPolyhedron(
        topology, za, { // base:
                        { -a, -a, za },
                        { a, -a, za },
                        { a, a, za },
                        { -a, a, za },
                        // middle
                        { -b, -b, zb },
                        { b, -b, zb },
                        { b, b, zb },
                        { -b, b, zb },
                        // top
                        { -c, -c, zc },
                        { c, -c, zc },
                        { c, c, zc },
                        { -c, c, zc } });
}
