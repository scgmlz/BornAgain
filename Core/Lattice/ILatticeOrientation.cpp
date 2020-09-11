// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/ILatticeOrientation.cpp
//! @brief     Implements subclasses of ILatticeOrientation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Lattice/ILatticeOrientation.h"
#include "Core/Vector/EigenCore.h"

namespace
{
bool ValidMillerIndex(MillerIndex index);
bool ParallelMillerIndices(MillerIndex index1, MillerIndex index2);
double SignForCrossProduct(MillerIndexOrientation::QComponent q1,
                           MillerIndexOrientation::QComponent q2);
MillerIndexOrientation::QComponent ThirdQComponent(MillerIndexOrientation::QComponent q1,
                                                   MillerIndexOrientation::QComponent q2);
void FillVectorInRow(Eigen::Matrix3d& matrix, kvector_t vec,
                     MillerIndexOrientation::QComponent row);
} // unnamed namespace

ILatticeOrientation::~ILatticeOrientation() = default;

MillerIndex::MillerIndex(double h_, double k_, double l_) : h(h_), k(k_), l(l_) {}

MillerIndexOrientation::MillerIndexOrientation(MillerIndexOrientation::QComponent q1,
                                               MillerIndex index1,
                                               MillerIndexOrientation::QComponent q2,
                                               MillerIndex index2)
    : m_prim_lattice(), m_q1(q1), m_q2(q2), m_ind1{index1}, m_ind2{index2}
{
    if (!checkAlignment())
        throw std::runtime_error("MillerIndexOrientation constructor: "
                                 "invalid alignment parameters");
}

MillerIndexOrientation* MillerIndexOrientation::clone() const
{
    auto P_result = std::make_unique<MillerIndexOrientation>(m_q1, m_ind1, m_q2, m_ind2);
    P_result->usePrimitiveLattice(m_prim_lattice);
    return P_result.release();
}

MillerIndexOrientation::~MillerIndexOrientation() = default;

void MillerIndexOrientation::usePrimitiveLattice(const Lattice& lattice)
{
    m_prim_lattice.resetBasis(lattice.getBasisVectorA(), lattice.getBasisVectorB(),
                              lattice.getBasisVectorC());
}

Transform3D MillerIndexOrientation::transformationMatrix() const
{
    auto dir_1 = m_prim_lattice.getMillerDirection(m_ind1.h, m_ind1.k, m_ind1.l);
    auto dir_2 = m_prim_lattice.getMillerDirection(m_ind2.h, m_ind2.k, m_ind2.l);
    auto dir_2_parallel = dir_2.project(dir_1);
    dir_2 = (dir_2 - dir_2_parallel).unit();
    auto dir_3 = SignForCrossProduct(m_q1, m_q2) * dir_1.cross(dir_2);
    auto q3 = ThirdQComponent(m_q1, m_q2);
    Eigen::Matrix3d rot_matrix;
    FillVectorInRow(rot_matrix, dir_1, m_q1);
    FillVectorInRow(rot_matrix, dir_2, m_q2);
    FillVectorInRow(rot_matrix, dir_3, q3);
    return Transform3D(rot_matrix);
}

bool MillerIndexOrientation::checkAlignment() const
{
    if (m_q1 == m_q2)
        return false;
    if (!ValidMillerIndex(m_ind1) || !ValidMillerIndex(m_ind2))
        return false;
    if (ParallelMillerIndices(m_ind1, m_ind2))
        return false;
    return true;
}

namespace
{
bool ValidMillerIndex(MillerIndex index)
{
    return (index.h != 0.0 || index.k != 0.0 || index.l != 0.0);
}
bool ParallelMillerIndices(MillerIndex index1, MillerIndex index2)
{
    double ratio = 0.0;
    if (index2.h != 0.0) {
        ratio = index1.h / index2.h;
    } else if (index2.k != 0.0) {
        ratio = index1.k / index2.k;
    } else if (index2.l != 0.0) {
        ratio = index1.l / index2.l;
    }
    if (ratio == 0.0)
        return false;
    return (index1.h == ratio * index2.h && index1.k == ratio * index2.k
            && index1.l == ratio * index2.l);
}
double SignForCrossProduct(MillerIndexOrientation::QComponent q1,
                           MillerIndexOrientation::QComponent q2)
{
    if ((q1 == MillerIndexOrientation::QX && q2 == MillerIndexOrientation::QY)
        || (q1 == MillerIndexOrientation::QY && q2 == MillerIndexOrientation::QZ)
        || (q1 == MillerIndexOrientation::QZ && q2 == MillerIndexOrientation::QX))
        return 1.0;
    return -1.0;
}
MillerIndexOrientation::QComponent ThirdQComponent(MillerIndexOrientation::QComponent q1,
                                                   MillerIndexOrientation::QComponent q2)
{
    if (q1 != MillerIndexOrientation::QX && q2 != MillerIndexOrientation::QX)
        return MillerIndexOrientation::QX;
    if (q1 != MillerIndexOrientation::QY && q2 != MillerIndexOrientation::QY)
        return MillerIndexOrientation::QY;
    return MillerIndexOrientation::QZ;
}
void FillVectorInRow(Eigen::Matrix3d& mat, kvector_t vec, MillerIndexOrientation::QComponent row)
{
    int i = row == MillerIndexOrientation::QX ? 0 : row == MillerIndexOrientation::QY ? 1 : 2;
    for (int j = 0; j < 3; ++j)
        mat(i, j) = vec[j];
}
} // unnamed namespace
