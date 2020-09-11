// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCuboctahedron.cpp
//! @brief     Implements class FormFactorCuboctahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorCuboctahedron.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/HardParticle/FormFactorPyramid.h"
#include "Core/Tools/MathFunctions.h"

const PolyhedralTopology FormFactorCuboctahedron::topology = {{{{3, 2, 1, 0}, true},
                                                               {{0, 1, 5, 4}, false},
                                                               {{1, 2, 6, 5}, false},
                                                               {{2, 3, 7, 6}, false},
                                                               {{3, 0, 4, 7}, false},
                                                               {{4, 5, 9, 8}, false},
                                                               {{5, 6, 10, 9}, false},
                                                               {{6, 7, 11, 10}, false},
                                                               {{7, 4, 8, 11}, false},
                                                               {{8, 9, 10, 11}, true}},
                                                              false};

//! Constructor of cuboctahedron (compound of two truncated pyramids with a common square base
//! and opposite orientations).
//! @param length: side length of the common square base in nanometers
//! @param height: height of the lower pyramid in nanometers
//! @param height_ratio: ratio of heights of top to bottom pyramids
//! @param alpha: dihedral angle in radians between base and facet
FormFactorCuboctahedron::FormFactorCuboctahedron(const std::vector<double> P)
    : FormFactorPolyhedron({"Cuboctahedron",
                            "class_tooltip",
                            {{"Length", "nm", "para_tooltip", 0, +INF, 0},
                             {"Height", "nm", "para_tooltip", 0, +INF, 0},
                             {"HeightRatio", "nm", "para_tooltip", 0, +INF, 0},
                             {"Alpha", "rad", "para_tooltip", 0., M_PI_2, 0}}},
                           P),
      m_length(m_P[0]), m_height(m_P[1]), m_height_ratio(m_P[2]), m_alpha(m_P[3])
{
    onChange();
}

FormFactorCuboctahedron::FormFactorCuboctahedron(double length, double height, double height_ratio,
                                                 double alpha)
    : FormFactorCuboctahedron(std::vector<double>{length, height, height_ratio, alpha})
{
}

IFormFactor* FormFactorCuboctahedron::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                      kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height * (1 + m_height_ratio));
    if (effects.dz_bottom > m_height) {
        double dbase_edge = 2 * (effects.dz_bottom - m_height) * MathFunctions::cot(m_alpha);
        FormFactorPyramid slicedff(
            m_length - dbase_edge,
            m_height * (1 + m_height_ratio) - effects.dz_bottom - effects.dz_top, m_alpha);
        return CreateTransformedFormFactor(slicedff, rot, effects.position);
    } else if (effects.dz_top > m_height_ratio * m_height) {
        double dbase_edge = 2 * (m_height - effects.dz_bottom) * MathFunctions::cot(m_alpha);
        FormFactorPyramid slicedff(
            m_length - dbase_edge,
            m_height * (1 + m_height_ratio) - effects.dz_bottom - effects.dz_top, M_PI - m_alpha);
        return CreateTransformedFormFactor(slicedff, rot, effects.position);
    } else {
        FormFactorCuboctahedron slicedff(m_length, m_height - effects.dz_bottom,
                                         m_height_ratio * m_height - effects.dz_top, m_alpha);
        return CreateTransformedFormFactor(slicedff, rot, effects.position);
    }
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

    double dzcom =
        m_height * ((x * x - 1) / 2 - 2 * r * (x * x * x - 1) / 3 + r * r * (x * x * x * x - 1) / 4)
        / ((x + 1) - r * (x * x + 1) + r * r * (x * x * x + 1) / 3);
    double za = -dzcom - m_height;
    double zb = -dzcom;
    double zc = -dzcom + x * m_height;

    setPolyhedron(topology, za,
                  {// base:
                   {-a, -a, za},
                   {a, -a, za},
                   {a, a, za},
                   {-a, a, za},
                   // middle
                   {-b, -b, zb},
                   {b, -b, zb},
                   {b, b, zb},
                   {-b, b, zb},
                   // top
                   {-c, -c, zc},
                   {c, -c, zc},
                   {c, c, zc},
                   {-c, c, zc}});
}
