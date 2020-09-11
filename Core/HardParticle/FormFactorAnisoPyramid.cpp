// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorAnisoPyramid.cpp
//! @brief     Implements class FormFactorAnisoPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorAnisoPyramid.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"

const PolyhedralTopology FormFactorAnisoPyramid::topology = {{{{3, 2, 1, 0}, true},
                                                              {{0, 1, 5, 4}, false},
                                                              {{1, 2, 6, 5}, false},
                                                              {{2, 3, 7, 6}, false},
                                                              {{3, 0, 4, 7}, false},
                                                              {{4, 5, 6, 7}, true}},
                                                             false};

//! Constructor of a truncated pyramid with a rectangular base.
//! @param length: length of the rectangular base in nm
//! @param width: width of the rectangular base in nm
//! @param height: height of pyramid in nm
//! @param alpha: dihedral angle in radians between base and facet
FormFactorAnisoPyramid::FormFactorAnisoPyramid(const std::vector<double> P)
    : FormFactorPolyhedron({"AnisoPyramid",
                            "class_tooltip",
                            {{"Length", "nm", "para_tooltip", 0, +INF, 0},
                             {"Width", "nm", "para_tooltip", 0, +INF, 0},
                             {"Height", "nm", "para_tooltip", 0, +INF, 0},
                             {"Alpha", "rad", "para_tooltip", 0., M_PI_2, 0}}},
                           P),
      m_length(m_P[0]), m_width(m_P[1]), m_height(m_P[2]), m_alpha(m_P[3])
{
    onChange();
}

FormFactorAnisoPyramid::FormFactorAnisoPyramid(double length, double width, double height,
                                               double alpha)
    : FormFactorAnisoPyramid(std::vector<double>{length, width, height, alpha})
{
}

IFormFactor* FormFactorAnisoPyramid::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                     kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    double dbase_edge = 2 * effects.dz_bottom * MathFunctions::cot(m_alpha);
    FormFactorAnisoPyramid slicedff(m_length - dbase_edge, m_width - dbase_edge,
                                    m_height - effects.dz_bottom - effects.dz_top, m_alpha);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
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

    setPolyhedron(topology, -zcom,
                  {// base:
                   {-D, -W, -zcom},
                   {D, -W, -zcom},
                   {D, W, -zcom},
                   {-D, W, -zcom},
                   // top:
                   {-d, -w, m_height - zcom},
                   {d, -w, m_height - zcom},
                   {d, w, m_height - zcom},
                   {-d, w, m_height - zcom}});
}
