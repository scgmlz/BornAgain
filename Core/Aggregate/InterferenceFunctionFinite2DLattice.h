// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionFinite2DLattice.h
//! @brief     Defines class InterferenceFunctionFinite2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONFINITE2DLATTICE_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONFINITE2DLATTICE_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Lattice/Lattice2D.h"

//! Interference function of a finite 2D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionFinite2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunctionFinite2DLattice(const Lattice2D& lattice, unsigned N_1, unsigned N_2);
    InterferenceFunctionFinite2DLattice(double length_1, double length_2, double alpha, double xi,
                                        unsigned N_1, unsigned N_2);
    ~InterferenceFunctionFinite2DLattice() final;

    InterferenceFunctionFinite2DLattice* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    static InterferenceFunctionFinite2DLattice* createSquare(double lattice_length, double xi,
                                                             unsigned N_1, unsigned N_2);
    static InterferenceFunctionFinite2DLattice* createHexagonal(double lattice_length, double xi,
                                                                unsigned N_1, unsigned N_2);

    unsigned numberUnitCells1() const { return m_N_1; }
    unsigned numberUnitCells2() const { return m_N_2; }

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const override final;

    std::vector<const INode*> getChildren() const override final;

private:
    double iff_without_dw(const kvector_t q) const override final;
    void setLattice(const Lattice2D& lattice);

    double interferenceForXi(double xi) const;

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<Lattice2D> mP_lattice;
    unsigned m_N_1, m_N_2; //!< Size of the finite lattice in lattice units
    mutable double m_qx;
    mutable double m_qy;
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONFINITE2DLATTICE_H
