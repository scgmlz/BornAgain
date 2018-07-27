// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DLattice.h
//! @brief     Defines class InterferenceFunction2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DLATTICE_H
#define INTERFERENCEFUNCTION2DLATTICE_H

#include "IInterferenceFunction.h"
#include "FTDecayFunctions.h"
#include "Lattice2D.h"

template <class T> class IntegratorReal;

//! Interference function of 2D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DLattice(const Lattice2D& lattice);
    InterferenceFunction2DLattice(double length_1, double length_2, double alpha, double xi=0.0);
    ~InterferenceFunction2DLattice() final;

    InterferenceFunction2DLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    static InterferenceFunction2DLattice* createSquare(double lattice_length, double xi = 0.0);
    static InterferenceFunction2DLattice* createHexagonal(double lattice_length, double xi = 0.0);

    void setDecayFunction(const IFTDecayFunction2D& decay);

    double evaluate(const kvector_t q) const final;

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const final;

    std::vector<const INode*> getChildren() const override;

    void onChange() override final;

private:
    InterferenceFunction2DLattice(const InterferenceFunction2DLattice& other);
    void setLattice(const Lattice2D& lattice);

    void init_parameters();
    double interferenceForXi(double xi) const;

    //! Returns interference from a single reciprocal lattice vector
    double interferenceAtOneRecLatticePoint(double qx, double qy) const;

    //! Returns reciprocal coordinates in the coordinate system rotated by the angle gamma
    std::pair<double, double> rotateOrthonormal(double qx, double qy, double gamma) const;

    //! Returns qx,qy coordinates of q - qint, where qint is a reciprocal lattice vector
    //! bounding the reciprocal unit cell to which q belongs
    std::pair<double, double> calculateReciprocalVectorFraction(
            double qx, double qy, double xi) const;

    //! Initializes the x,y coordinates of the a*,b* reciprocal bases
    void initialize_rec_vectors();

    //! Initializes factors needed in each calculation
    void initialize_calc_factors();

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<IFTDecayFunction2D> m_decay;
    std::unique_ptr<Lattice2D> m_lattice;
    Lattice2D::ReciprocalBases m_sbase;  //!< reciprocal lattice is stored without xi
    int m_na, m_nb; //!< determines the number of reciprocal lattice points to use
    mutable double m_qx;
    mutable double m_qy;
#ifndef SWIG
    std::unique_ptr<IntegratorReal<InterferenceFunction2DLattice>> mP_integrator;
#endif
};

#endif // INTERFERENCEFUNCTION2DLATTICE_H
