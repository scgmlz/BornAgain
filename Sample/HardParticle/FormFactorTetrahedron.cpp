//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorTetrahedron.cpp
//! @brief     Implements class FormFactorTetrahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/FormFactorTetrahedron.h"
#include "Base/Math/Constants.h"
#include "Base/Math/Functions.h"

const PolyhedralTopology FormFactorTetrahedron::topology = {{{{2, 1, 0}, false},
                                                             {{0, 1, 4, 3}, false},
                                                             {{1, 2, 5, 4}, false},
                                                             {{2, 0, 3, 5}, false},
                                                             {{3, 4, 5}, false}},
                                                            false};

FormFactorTetrahedron::FormFactorTetrahedron(const std::vector<double> P)
    : IFormFactorPolyhedron(
        {"Tetrahedron",
         "actually, not a tetrahedron, but a trigonal frustum",
         {{"BaseEdge", "nm", "edge of base triangle", 0, +INF, 0},
          {"Height", "nm", "height of frustum", 0, +INF, 0},
          {"Alpha", "rad", "angle between base and a side face", 0., M_PI_2, 0}}},
        P)
    , m_base_edge(m_P[0])
    , m_height(m_P[1])
    , m_alpha(m_P[2]) {
    onChange();
}

FormFactorTetrahedron::FormFactorTetrahedron(double base_edge, double height, double alpha)
    : FormFactorTetrahedron(std::vector<double>{base_edge, height, alpha}) {}

IFormFactor* FormFactorTetrahedron::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                    kvector_t translation) const {
    auto effects = computeSlicingEffects(limits, translation, m_height);
    double dbase_edge = 2 * sqrt(3) * effects.dz_bottom * Math::cot(m_alpha);
    FormFactorTetrahedron slicedff(m_base_edge - dbase_edge,
                                   m_height - effects.dz_bottom - effects.dz_top, m_alpha);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorTetrahedron::onChange() {
    double cot_alpha = Math::cot(m_alpha);
    if (!std::isfinite(cot_alpha) || cot_alpha < 0)
        throw std::runtime_error("pyramid angle alpha out of bounds");
    double r = cot_alpha * 2 * std::sqrt(3.) * m_height / m_base_edge; // L(top)/L(base)
    if (r > 1) {
        std::ostringstream ostr;
        ostr << "Incompatible parameters in Tetrahedron: ";
        ostr << "(base_edge=" << m_base_edge;
        ostr << ", height:" << m_height;
        ostr << ", alpha[rad]:" << m_alpha << ")";
        throw std::runtime_error(ostr.str());
    }

    double a = m_base_edge;
    double as = a / 2;
    double ac = a / sqrt(3) / 2;
    double ah = a / sqrt(3);
    double b = a * (1 - r);
    double bs = b / 2;
    double bc = b / sqrt(3) / 2;
    double bh = b / sqrt(3);

    double zcom = m_height * (.5 - 2 * r / 3 + r * r / 4) / (1 - r + r * r / 3); // center of mass

    setPolyhedron(topology, -zcom,
                  {// base:
                   {-ac, as, -zcom},
                   {-ac, -as, -zcom},
                   {ah, 0., -zcom},
                   // top:
                   {-bc, bs, m_height - zcom},
                   {-bc, -bs, m_height - zcom},
                   {bh, 0., m_height - zcom}});
}
