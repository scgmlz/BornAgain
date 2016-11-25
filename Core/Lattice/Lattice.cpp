// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice.cpp
//! @brief     Implements class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Lattice.h"
#include "ISelectionRule.h"
#include "MathConstants.h"
#include "Transform3D.h"
#include <gsl/gsl_linalg.h>

Lattice::Lattice(const kvector_t a1, const kvector_t a2, const kvector_t a3)
    : mp_selection_rule(0), m_a1(a1), m_a2(a2), m_a3(a3), m_cache_ok(false)
{
    initialize();
}

Lattice::Lattice(const Lattice& lattice)
    : mp_selection_rule(0)
    , m_a1(lattice.m_a1)
    , m_a2(lattice.m_a2)
    , m_a3(lattice.m_a3)
    , m_cache_ok(false)
{
    initialize();
    if (lattice.mp_selection_rule)
        setSelectionRule(*lattice.mp_selection_rule);
}

Lattice::~Lattice() { delete mp_selection_rule; }

Lattice Lattice::createTransformedLattice(const Transform3D& transform) const
{
    kvector_t a1 = transform.transformed(m_a1);
    kvector_t a2 = transform.transformed(m_a2);
    kvector_t a3 = transform.transformed(m_a3);
    Lattice result = Lattice(a1, a2, a3);
    if (mp_selection_rule)
        result.setSelectionRule(*mp_selection_rule);
    return result;
}

void Lattice::initialize() const
{
    computeReciprocalVectors();
    m_cache_ok = true;
}

double Lattice::getVolume() const { return std::abs(m_a1.dot(m_a2.cross(m_a3))); }

void Lattice::getReciprocalLatticeBasis(kvector_t b1, kvector_t b2, kvector_t b3) const
{
    if (!m_cache_ok) {
        initialize();
    }
    b1 = m_b1;
    b2 = m_b2;
    b3 = m_b3;
    return;
}

ivector_t Lattice::getNearestLatticeVectorCoordinates(const kvector_t vector_in) const
{
    double a1_coord = vector_in.dot(m_b1) / M_TWOPI;
    double a2_coord = vector_in.dot(m_b2) / M_TWOPI;
    double a3_coord = vector_in.dot(m_b3) / M_TWOPI;
    int c1 = (int)std::floor(a1_coord + 0.5);
    int c2 = (int)std::floor(a2_coord + 0.5);
    int c3 = (int)std::floor(a3_coord + 0.5);
    return ivector_t(c1, c2, c3);
}

ivector_t Lattice::getNearestReciprocalLatticeVectorCoordinates(const kvector_t vector_in) const
{
    double b1_coord = vector_in.dot(m_a1) / M_TWOPI;
    double b2_coord = vector_in.dot(m_a2) / M_TWOPI;
    double b3_coord = vector_in.dot(m_a3) / M_TWOPI;
    int c1 = (int)std::floor(b1_coord + 0.5);
    int c2 = (int)std::floor(b2_coord + 0.5);
    int c3 = (int)std::floor(b3_coord + 0.5);
    return ivector_t(c1, c2, c3);
}

std::vector<kvector_t>
Lattice::reciprocalLatticeVectorsWithinRadius(const kvector_t input_vector, double radius) const
{
    if (!m_cache_ok)
        initialize();
    ivector_t nearest_coords = getNearestReciprocalLatticeVectorCoordinates(input_vector);
    return vectorsWithinRadius(
        input_vector, nearest_coords, radius, m_b1, m_b2, m_b3, m_a1, m_a2, m_a3);
}

Lattice Lattice::createFCCLattice(double a)
{
    double b = a / 2.0;
    kvector_t a1(0.0, b, b);
    kvector_t a2(b, 0.0, b);
    kvector_t a3(b, b, 0.0);
    return Lattice(a1, a2, a3);
}

Lattice Lattice::createTrigonalLattice(double a, double c)
{
    kvector_t a1(a, 0.0, 0.0);
    kvector_t a2(-a / 2.0, std::sqrt(3.0) * a / 2.0, 0);
    kvector_t a3(0.0, 0.0, c);
    return Lattice(a1, a2, a3);
}

void Lattice::computeReciprocalVectors() const
{
    kvector_t a23 = m_a2.cross(m_a3);
    kvector_t a31 = m_a3.cross(m_a1);
    kvector_t a12 = m_a1.cross(m_a2);
    m_b1 = M_TWOPI / m_a1.dot(a23) * a23;
    m_b2 = M_TWOPI / m_a2.dot(a31) * a31;
    m_b3 = M_TWOPI / m_a3.dot(a12) * a12;
}

std::vector<kvector_t> Lattice::vectorsWithinRadius(
    const kvector_t input_vector, const ivector_t& nearest_coords, double radius,
    const kvector_t v1, const kvector_t v2, const kvector_t v3, const kvector_t rec1,
    const kvector_t rec2, const kvector_t rec3) const
{
    int max_X = (int)std::floor(rec1.mag() * radius / M_TWOPI);
    int max_Y = (int)std::floor(rec2.mag() * radius / M_TWOPI);
    int max_Z = (int)std::floor(rec3.mag() * radius / M_TWOPI);

    std::vector<kvector_t> ret;
    for (int index_X = -max_X; index_X <= max_X; ++index_X) {
        for (int index_Y = -max_Y; index_Y <= max_Y; ++index_Y) {
            for (int index_Z = -max_Z; index_Z <= max_Z; ++index_Z) {
                ivector_t coords(
                    index_X + nearest_coords[0], index_Y + nearest_coords[1],
                    index_Z + nearest_coords[2]);
                if (mp_selection_rule && !mp_selection_rule->coordinateSelected(coords))
                    continue;
                kvector_t latticePoint = coords[0] * v1 + coords[1] * v2 + coords[2] * v3;
                if ((latticePoint - input_vector).mag() <= radius)
                    ret.push_back(latticePoint);
            }
        }
    }
    return ret;
}

void Lattice::computeInverseVectors(
    const kvector_t v1, const kvector_t v2, const kvector_t v3, kvector_t o1, kvector_t o2,
    kvector_t o3)
{
    gsl_matrix* p_basisMatrix = gsl_matrix_alloc(3, 3);
    gsl_matrix* p_inverseMatrix = gsl_matrix_alloc(3, 3);
    gsl_permutation* p_perm = gsl_permutation_alloc(3);
    int s;

    gsl_matrix_set(p_basisMatrix, 0, 0, v1.x());
    gsl_matrix_set(p_basisMatrix, 0, 1, v2.x());
    gsl_matrix_set(p_basisMatrix, 0, 2, v3.x());

    gsl_matrix_set(p_basisMatrix, 1, 0, v1.y());
    gsl_matrix_set(p_basisMatrix, 1, 1, v2.y());
    gsl_matrix_set(p_basisMatrix, 1, 2, v3.y());

    gsl_matrix_set(p_basisMatrix, 2, 0, v1.z());
    gsl_matrix_set(p_basisMatrix, 2, 1, v2.z());
    gsl_matrix_set(p_basisMatrix, 2, 2, v3.z());

    gsl_linalg_LU_decomp(p_basisMatrix, p_perm, &s);
    gsl_linalg_LU_invert(p_basisMatrix, p_perm, p_inverseMatrix);

    o1.setX(gsl_matrix_get(p_inverseMatrix, 0, 0));
    o1.setY(gsl_matrix_get(p_inverseMatrix, 1, 0));
    o1.setZ(gsl_matrix_get(p_inverseMatrix, 2, 0));

    o2.setX(gsl_matrix_get(p_inverseMatrix, 0, 1));
    o2.setY(gsl_matrix_get(p_inverseMatrix, 1, 1));
    o2.setZ(gsl_matrix_get(p_inverseMatrix, 2, 1));

    o3.setX(gsl_matrix_get(p_inverseMatrix, 0, 2));
    o3.setY(gsl_matrix_get(p_inverseMatrix, 1, 2));
    o3.setZ(gsl_matrix_get(p_inverseMatrix, 2, 2));

    gsl_permutation_free(p_perm);
    gsl_matrix_free(p_basisMatrix);
    gsl_matrix_free(p_inverseMatrix);
}

void Lattice::setSelectionRule(const ISelectionRule& p_selection_rule)
{
    delete mp_selection_rule;
    mp_selection_rule = p_selection_rule.clone();
}
