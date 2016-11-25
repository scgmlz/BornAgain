// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DLattice.h
//! @brief     Defines class InterferenceFunction2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DLATTICE_H
#define INTERFERENCEFUNCTION2DLATTICE_H

#include "FTDecayFunctions.h"
#include "IInterferenceFunction.h"
#include "Lattice2DParameters.h"

//! Interference function of 2D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DLattice(double length_1, double length_2, double angle, double xi = 0.0);
    ~InterferenceFunction2DLattice() final;

    InterferenceFunction2DLattice* clone() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    static InterferenceFunction2DLattice* createSquare(double lattice_length, double xi = 0.0);
    static InterferenceFunction2DLattice* createHexagonal(double lattice_length, double xi = 0.0);

    void setDecayFunction(const IFTDecayFunction2D& pdf);

    const IFTDecayFunction2D* getDecayFunction() const { return mp_pdf; }

    double evaluate(const kvector_t q) const final;

    Lattice2DParameters getLatticeParameters() const { return m_lattice_params; }

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const final;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const final;

protected:
    void onChange() override final;

private:
    //! Returns interference from a single reciprocal lattice vector
    double interferenceAtOneRecLatticePoint(double qx, double qy) const;

    //! Returns reciprocal coordinates in the principal axis system
    void transformToPrincipalAxes(
        double qx, double qy, double gamma, double delta, double& q_pa_1, double& q_pa_2) const;

    //! Returns qx,qy coordinates of q - qint, where qint is a reciprocal lattice vector
    //! bounding the reciprocal unit cell to which q belongs
    void
    calculateReciprocalVectorFraction(double qx, double qy, double& qx_frac, double& qy_frac) const;

    Lattice2DParameters m_lattice_params;
    IFTDecayFunction2D* mp_pdf;
    static const int nmax = 20; //!< maximum value for qx*Lambdax and qy*lambday

    InterferenceFunction2DLattice(const Lattice2DParameters& lattice_params);

    void init_parameters();

    //! Initializes the x,y coordinates of the a*,b* reciprocal bases
    void initialize_rec_vectors();

    //! Initializes factors needed in each calculation
    void initialize_calc_factors();

    double m_asx, m_asy; //!< x,y coordinates of a*
    double m_bsx, m_bsy; //!< x,y coordinates of b*
    int m_na, m_nb; //!< determines the number of reciprocal lattice points to use
};

#endif // INTERFERENCEFUNCTION2DLATTICE_H
