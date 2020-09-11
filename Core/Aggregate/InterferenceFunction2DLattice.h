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

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DLATTICE_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DLATTICE_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Correlations/FTDecay1D.h"
#include "Core/Correlations/FTDecay2D.h"
#include "Core/Lattice/Lattice2D.h"

//! Interference function of a 2D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DLattice(double length_1, double length_2, double alpha, double xi);
    InterferenceFunction2DLattice(const Lattice2D& lattice);
    ~InterferenceFunction2DLattice() final;

    InterferenceFunction2DLattice* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    static InterferenceFunction2DLattice* createSquare(double lattice_length, double xi);
    static InterferenceFunction2DLattice* createHexagonal(double lattice_length, double xi);

    void setDecayFunction(const IFTDecayFunction2D& decay);

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const override final;

    std::vector<const INode*> getChildren() const override final;

    void onChange() override final;

private:
    double iff_without_dw(const kvector_t q) const override final;
    void setLattice(const Lattice2D& lattice);

    double interferenceForXi(double xi) const;

    //! Returns interference from a single reciprocal lattice vector
    double interferenceAtOneRecLatticePoint(double qx, double qy) const;

    //! Returns reciprocal coordinates in the coordinate system rotated by the angle gamma
    std::pair<double, double> rotateOrthonormal(double qx, double qy, double gamma) const;

    //! Returns qx,qy coordinates of q - qint, where qint is a reciprocal lattice vector
    //! bounding the reciprocal unit cell to which q belongs
    std::pair<double, double> calculateReciprocalVectorFraction(double qx, double qy,
                                                                double xi) const;

    //! Initializes the x,y coordinates of the a*,b* reciprocal bases
    void initialize_rec_vectors();

    //! Initializes factors needed in each calculation
    void initialize_calc_factors();

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<IFTDecayFunction2D> m_decay;
    std::unique_ptr<Lattice2D> m_lattice;
    Lattice2D::ReciprocalBases m_sbase; //!< reciprocal lattice is stored without xi
    int m_na, m_nb; //!< determines the number of reciprocal lattice points to use
    mutable double m_qx;
    mutable double m_qy;
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DLATTICE_H
