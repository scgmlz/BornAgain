//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/Lattice3D.h
//! @brief     Defines class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_LATTICE_LATTICE3D_H
#define BORNAGAIN_SAMPLE_LATTICE_LATTICE3D_H

#include "Param/Node/INode.h"
#include <memory>
#include <vector>

class ISelectionRule;
class Transform3D;

//! A Bravais lattice, characterized by three basis vectors, and optionally an ISelectionRule.

//! @ingroup samples

class Lattice3D : public INode {
public:
    Lattice3D() = delete;
    Lattice3D(const kvector_t a, const kvector_t b, const kvector_t c);
    Lattice3D(const Lattice3D& lattice);
    ~Lattice3D() override;
    Lattice3D& operator=(const Lattice3D&) = delete;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Creates transformed lattice
    Lattice3D transformed(const Transform3D& transform) const;

    //! Initializes cached data
    void initialize();

    //! Returns basis vector a
    kvector_t getBasisVectorA() const { return m_a; }

    //! Returns basis vector b
    kvector_t getBasisVectorB() const { return m_b; }

    //! Returns basis vector c
    kvector_t getBasisVectorC() const { return m_c; }

    //! Returns normalized direction corresponding to the given Miller indices
    kvector_t getMillerDirection(double h, double k, double l) const;

    //! Returns the volume of the unit cell
    double unitCellVolume() const;

    //! Returns the reciprocal basis vectors
    void getReciprocalLatticeBasis(kvector_t& ra, kvector_t& rb, kvector_t& rc) const;

    //! Returns the nearest reciprocal lattice point from a given vector
    ivector_t getNearestReciprocalLatticeVectorCoordinates(const kvector_t q) const;

    //! Returns a list of reciprocal lattice vectors within distance dq of a vector q
    std::vector<kvector_t> reciprocalLatticeVectorsWithinRadius(const kvector_t q, double dq) const;

    //! Sets a selection rule for the reciprocal vectors
    void setSelectionRule(const ISelectionRule& selection_rule);

private:
    void onChange() override;

    void computeReciprocalVectors() const;

    kvector_t m_a, m_b, m_c; //!< Basis vectors in real space
    std::unique_ptr<ISelectionRule> m_selection_rule;

    mutable kvector_t m_ra, m_rb, m_rc; //!< Cache of basis vectors in reciprocal space
};

#endif // BORNAGAIN_SAMPLE_LATTICE_LATTICE3D_H
