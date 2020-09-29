// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/Prism.cpp
//! @brief     Implements class Prism.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

//! The mathematics implemented here is described in full detail in a paper
//! by Joachim Wuttke, entitled
//! "Form factor (Fourier shape transform) of polygon and polyhedron."

#include "Core/HardParticle/Prism.h"
#include "Core/Tools/MathFunctions.h"
#include <stdexcept> // need overlooked by g++ 5.4

namespace
{
const double eps = 2e-16;
} // namespace

Prism::Prism(bool symmetry_Ci, double height, const std::vector<kvector_t>& vertices)
{
    m_height = height;
    m_vertices.clear();
    for (const kvector_t& vertex : vertices) {
        m_vertices.push_back(vertex);
        m_vertices.push_back(vertex + kvector_t{0, 0, m_height});
    }

    try {
        m_base = std::unique_ptr<PolyhedralFace>(new PolyhedralFace(vertices, symmetry_Ci));
    } catch (std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Invalid parameterization of Prism: ") + e.what());
    } catch (std::logic_error& e) {
        throw std::logic_error(std::string("Bug in Prism: ") + e.what()
                               + " [please report to the maintainers]");
    } catch (std::exception& e) {
        throw std::runtime_error(std::string("Unexpected exception in Prism: ") + e.what()
                                 + " [please report to the maintainers]");
    }
}

double Prism::area() const
{
    return m_base->area();
}

const std::vector<kvector_t>& Prism::vertices()
{
    return m_vertices;
}

complex_t Prism::evaluate_for_q(const cvector_t& q) const
{
    try {
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis.maxOrder = 0;
        diagnosis.nExpandedFaces = 0;
#endif
        cvector_t qxy(q.x(), q.y(), 0.);
        return m_height * exp_I(m_height / 2 * q.z()) * MathFunctions::sinc(m_height / 2 * q.z())
               * m_base->ff_2D(qxy);
    } catch (std::logic_error& e) {
        throw std::logic_error(std::string("Bug in Prism: ") + e.what()
                               + " [please report to the maintainers]");
    } catch (std::runtime_error& e) {
        throw std::runtime_error(std::string("Numeric computation failed in Prism: ") + e.what()
                                 + " [please report to the maintainers]");
    } catch (std::exception& e) {
        throw std::runtime_error(std::string("Unexpected exception in Prism: ") + e.what()
                                 + " [please report to the maintainers]");
    }
}
