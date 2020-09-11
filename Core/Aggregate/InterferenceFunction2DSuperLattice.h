// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DSuperLattice.h
//! @brief     Defines class InterferenceFunction2DSuperLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DSUPERLATTICE_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DSUPERLATTICE_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Lattice/Lattice2D.h"

//! Interference function of a 2D superlattice with a configurable interference function for
//! each lattice site.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DSuperLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DSuperLattice(const Lattice2D& lattice, unsigned size_1, unsigned size_2);
    InterferenceFunction2DSuperLattice(double length_1, double length_2, double alpha, double xi,
                                       unsigned size_1, unsigned size_2);
    ~InterferenceFunction2DSuperLattice() final;

    InterferenceFunction2DSuperLattice* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setSubstructureIFF(const IInterferenceFunction& sub_iff);
    const IInterferenceFunction& substructureIFF() const;

    static InterferenceFunction2DSuperLattice* createSquare(double lattice_length, double xi,
                                                            unsigned size_1, unsigned size_2);
    static InterferenceFunction2DSuperLattice* createHexagonal(double lattice_length, double xi,
                                                               unsigned size_1, unsigned size_2);

    double evaluate(const kvector_t q, double outer_iff = 1.0) const override final;
    unsigned domainSize1() const { return m_size_1; }
    unsigned domainSize2() const { return m_size_2; }

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    std::vector<const INode*> getChildren() const override final;

private:
    double iff_without_dw(const kvector_t q) const override final;
    void setLattice(const Lattice2D& lattice);

    double interferenceForXi(double xi) const;

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<Lattice2D> mP_lattice;
    std::unique_ptr<IInterferenceFunction> mP_substructure; //!< IFF of substructure
    unsigned m_size_1, m_size_2; //!< Size of the finite lattice in lattice units
    mutable double m_outer_iff;
    mutable double m_qx;
    mutable double m_qy;
    mutable double m_xi;
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DSUPERLATTICE_H
