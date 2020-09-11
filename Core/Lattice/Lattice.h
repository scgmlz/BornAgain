// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice.h
//! @brief     Defines class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_LATTICE_LATTICE_H
#define BORNAGAIN_CORE_LATTICE_LATTICE_H

#include "Core/Parametrization/INode.h"
#include "Core/Vector/Vectors3D.h"
#include <vector>

class ISelectionRule;
class Transform3D;

//! A lattice with three basis vectors.
//! @ingroup samples

class BA_CORE_API_ Lattice : public INode
{
public:
    Lattice();
    Lattice(const kvector_t a1, const kvector_t a2, const kvector_t a3);
    Lattice(const Lattice& lattice);
    ~Lattice() override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Create transformed lattice
    Lattice createTransformedLattice(const Transform3D& transform) const;

    //! Initializes cached data
    void initialize() const;

    //! Returns basis vector a
    kvector_t getBasisVectorA() const { return m_a; }

    //! Returns basis vector b
    kvector_t getBasisVectorB() const { return m_b; }

    //! Returns basis vector c
    kvector_t getBasisVectorC() const { return m_c; }

    //! Resets the basis vectors
    void resetBasis(const kvector_t a1, const kvector_t a2, const kvector_t a3);

    //! Returns normalized direction corresponding to the given Miller indices
    kvector_t getMillerDirection(double h, double k, double l) const;

    //! Returns the volume of the unit cell
    double volume() const;

    //! Returns the reciprocal basis vectors
    void getReciprocalLatticeBasis(kvector_t& b1, kvector_t& b2, kvector_t& b3) const;

    //! Returns the nearest lattice point from a given vector
    ivector_t getNearestLatticeVectorCoordinates(const kvector_t vector_in) const;

    //! Returns the nearest reciprocal lattice point from a given vector
    ivector_t getNearestReciprocalLatticeVectorCoordinates(const kvector_t vector_in) const;

    //! Computes a list of reciprocal lattice vectors within a specified distance of a given vector
    std::vector<kvector_t> reciprocalLatticeVectorsWithinRadius(const kvector_t input_vector,
                                                                double radius) const;

    //! Sets a selection rule for the reciprocal vectors
    void setSelectionRule(const ISelectionRule& p_selection_rule);

    //! Returns a primitive cubic (cP) lattice with edge length a.
    static Lattice createCubicLattice(double a);

    //! Returns a face-centered cubic (cF) lattice with edge length a.
    static Lattice createFCCLattice(double a);

    //! Returns a primitive hexagonal (hP) lattice with hexagonal edge a and height c.
    static Lattice createHexagonalLattice(double a, double c);

    //! TODO: Clarify how this is meant: HCP is not a Bravais lattice.
    static Lattice createHCPLattice(double a, double c);

    //! Returns a primitive tetragonal (tP) lattice with square base edge a and height c.
    static Lattice createTetragonalLattice(double a, double c);

    //! Returns a body-centered cubic (cI) lattice with edge length a.
    //! TODO: Clarify meaning of c
    static Lattice createBCTLattice(double a, double c);

    void onChange() override;

private:
    Lattice& operator=(const Lattice& lattice);

    void registerBasisVectors();

    std::vector<kvector_t> vectorsWithinRadius(const kvector_t input_vector,
                                               const ivector_t& nearest_coords, double radius,
                                               const kvector_t v1, const kvector_t v2,
                                               const kvector_t v3, const kvector_t rec1,
                                               const kvector_t rec2, const kvector_t rec3) const;

    void computeReciprocalVectors() const;
    static void computeInverseVectors(const kvector_t v1, const kvector_t v2, const kvector_t v3,
                                      kvector_t o1, kvector_t o2, kvector_t o3);
    ISelectionRule* mp_selection_rule;
    kvector_t m_a, m_b, m_c;            //!< Basis vectors in real space
    mutable kvector_t m_ra, m_rb, m_rc; //!< Cache of basis vectors in reciprocal space
    //! Boolean indicating if the reciprocal vectors are already initialized in the cache
    mutable bool m_cache_ok;
};

#endif // BORNAGAIN_CORE_LATTICE_LATTICE_H
