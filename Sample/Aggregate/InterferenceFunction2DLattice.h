//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/InterferenceFunction2DLattice.h
//! @brief     Defines class InterferenceFunction2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION2DLATTICE_H
#define BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION2DLATTICE_H

#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Correlations/FTDecay1D.h"
#include "Sample/Correlations/FTDecay2D.h"
#include "Sample/Lattice/Lattice2D.h"

//! Interference function of a 2D lattice.
//! @ingroup interference

class InterferenceFunction2DLattice : public IInterferenceFunction {
public:
    InterferenceFunction2DLattice(const Lattice2D& lattice);
    ~InterferenceFunction2DLattice() override;

    InterferenceFunction2DLattice* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void setDecayFunction(const IFTDecayFunction2D& decay);

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const override;

    std::vector<const INode*> getChildren() const override;

    void onChange() override;

private:
    double iff_without_dw(const kvector_t q) const override;

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

#endif // BORNAGAIN_SAMPLE_AGGREGATE_INTERFERENCEFUNCTION2DLATTICE_H
