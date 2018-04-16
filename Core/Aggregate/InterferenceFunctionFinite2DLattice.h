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

#ifndef INTERFERENCEFUNCTIONFINITE2DLATTICE_H
#define INTERFERENCEFUNCTIONFINITE2DLATTICE_H

#include "IInterferenceFunction.h"
#include "FTDecayFunctions.h"
#include "Lattice2D.h"

template <class T> class IntegratorReal;

//! Interference function of 2D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionFinite2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunctionFinite2DLattice(const Lattice2D& lattice, unsigned size_1, unsigned size_2);
    InterferenceFunctionFinite2DLattice(double length_1, double length_2, double alpha,
                                        double xi, unsigned size_1, unsigned size_2);
    ~InterferenceFunctionFinite2DLattice() final;

    InterferenceFunctionFinite2DLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    static InterferenceFunctionFinite2DLattice* createSquare(
            double lattice_length, double xi, unsigned size_1, unsigned size_2);
    static InterferenceFunctionFinite2DLattice* createHexagonal(
            double lattice_length, double xi, unsigned size_1, unsigned size_2);

    double evaluate(const kvector_t q) const final;

    unsigned domainSize1() const { return m_size_1; }
    unsigned domainSize2() const { return m_size_2; }

    void setPositionVariance(double sigma2) { m_sigma2 = sigma2; }
    double positionVariance() const { return m_sigma2; }

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const final;

    std::vector<const INode*> getChildren() const override;

private:
    InterferenceFunctionFinite2DLattice(const InterferenceFunctionFinite2DLattice& other);
    void setLattice(const Lattice2D& lattice);

    void init_parameters();
    double interferenceForXi(double xi) const;

    double m_sigma2;
    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<Lattice2D> m_lattice;
    unsigned m_size_1, m_size_2;  //!< Size of the finite lattice in lattice units
    mutable double m_qx;
    mutable double m_qy;
#ifndef SWIG
    std::unique_ptr<IntegratorReal<InterferenceFunctionFinite2DLattice>> mP_integrator;
#endif
};

#endif // INTERFERENCEFUNCTIONFINITE2DLATTICE_H
