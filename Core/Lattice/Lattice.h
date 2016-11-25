// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice.h
//! @brief     Defines class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE_H
#define LATTICE_H

#include "Vectors3D.h"
#include <vector>

class ISelectionRule;
class Transform3D;

//! A lattice with three basis vectors.
//! @ingroup samples

class BA_CORE_API_ Lattice
{
public:
    Lattice() = delete;
    Lattice(const kvector_t a1, const kvector_t a2, const kvector_t a3);
    Lattice(const Lattice& lattice);
    ~Lattice();

    //! Create transformed lattice
    Lattice createTransformedLattice(const Transform3D& transform) const;

    //! Initializes cached data
    void initialize() const;

    //! Returns basis vector a
    kvector_t getBasisVectorA() const { return m_a1; }

    //! Returns basis vector b
    kvector_t getBasisVectorB() const { return m_a2; }

    //! Returns basis vector c
    kvector_t getBasisVectorC() const { return m_a3; }

    //! Returns the volume of the unit cell
    double getVolume() const;

    //! Returns the reciprocal basis vectors
    void getReciprocalLatticeBasis(kvector_t b1, kvector_t b2, kvector_t b3) const;

    //! Returns the nearest lattice point from a given vector
    ivector_t getNearestLatticeVectorCoordinates(const kvector_t vector_in) const;

    //! Returns the nearest reciprocal lattice point from a given vector
    ivector_t getNearestReciprocalLatticeVectorCoordinates(const kvector_t vector_in) const;

    //! Computes a list of reciprocal lattice vectors within a specified distance of a given vector
    std::vector<kvector_t>
    reciprocalLatticeVectorsWithinRadius(const kvector_t input_vector, double radius) const;

    //! Sets a selection rule for the reciprocal vectors
    void setSelectionRule(const ISelectionRule& p_selection_rule);

    static Lattice createFCCLattice(double a);

    static Lattice createTrigonalLattice(double a, double c);

private:
    Lattice& operator=(const Lattice& lattice);

    std::vector<kvector_t> vectorsWithinRadius(
        const kvector_t input_vector, const ivector_t& nearest_coords, double radius,
        const kvector_t v1, const kvector_t v2, const kvector_t v3, const kvector_t rec1,
        const kvector_t rec2, const kvector_t rec3) const;

    void computeReciprocalVectors() const;
    static void computeInverseVectors(
        const kvector_t v1, const kvector_t v2, const kvector_t v3, kvector_t o1, kvector_t o2,
        kvector_t o3);
    ISelectionRule* mp_selection_rule;
    kvector_t m_a1, m_a2, m_a3; //!< Basis vectors in real space
    mutable kvector_t m_b1, m_b2, m_b3; //!< Cache of basis vectors in reciprocal space
    //! Boolean indicating if the reciprocal vectors are already initialized in the cache
    mutable bool m_cache_ok;
};

#endif // LATTICE_H
