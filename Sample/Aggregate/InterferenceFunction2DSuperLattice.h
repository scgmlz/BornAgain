//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunction2DSuperLattice.h
//! @brief     Defines class InterferenceFunction2DSuperLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION2DSUPERLATTICE_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION2DSUPERLATTICE_H

#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Lattice/Lattice2D.h"

//! Interference function of a 2D superlattice with a configurable interference function for
//! each lattice site.
//! @ingroup interference

class InterferenceFunction2DSuperLattice : public IInterferenceFunction {
public:
    InterferenceFunction2DSuperLattice(const Lattice2D& lattice, unsigned size_1, unsigned size_2);
    InterferenceFunction2DSuperLattice(double length_1, double length_2, double alpha, double xi,
                                       unsigned size_1, unsigned size_2);
    ~InterferenceFunction2DSuperLattice() override;

    InterferenceFunction2DSuperLattice* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setSubstructureIFF(const IInterferenceFunction& sub_iff);
    const IInterferenceFunction& substructureIFF() const;

    double evaluate(const kvector_t q, double outer_iff = 1.0) const override;
    unsigned domainSize1() const { return m_size_1; }
    unsigned domainSize2() const { return m_size_2; }

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    std::vector<const INode*> getChildren() const override;

private:
    double iff_without_dw(const kvector_t q) const override;

    double interferenceForXi(double xi) const;

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<Lattice2D> m_lattice;
    std::unique_ptr<IInterferenceFunction> m_substructure; //!< IFF of substructure
    unsigned m_size_1, m_size_2; //!< Size of the finite lattice in lattice units
    mutable double m_outer_iff;
    mutable double m_qx;
    mutable double m_qy;
    mutable double m_xi;
};

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION2DSUPERLATTICE_H
