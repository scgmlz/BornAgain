// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DParaCrystal.h
//! @brief     Defines class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DPARACRYSTAL_H
#define INTERFERENCEFUNCTION2DPARACRYSTAL_H

#include "Complex.h"
#include "FTDistributions2D.h"
#include "IInterferenceFunction.h"
#include "Lattice2DParameters.h"
#include <memory>

template <class T> class IntegratorReal;
class IFTDistribution2D;

//! Interference function of 2D paracrystal.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DParaCrystal : public IInterferenceFunction
{
public:
    InterferenceFunction2DParaCrystal(
        double length_1, double length_2, double alpha_lattice, double xi = 0.0,
        double damping_length = 0.0);

    ~InterferenceFunction2DParaCrystal() final;

    InterferenceFunction2DParaCrystal* clone() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    std::string to_str(int indent = 0) const final;

    static InterferenceFunction2DParaCrystal* createSquare(
        double peak_distance, double damping_length = 0.0, double domain_size_1 = 0.0,
        double domain_size_2 = 0.0);
    static InterferenceFunction2DParaCrystal* createHexagonal(
        double peak_distance, double damping_length = 0.0, double domain_size_1 = 0.0,
        double domain_size_2 = 0.0);

    void setDomainSizes(double size_1, double size_2);

    void
    setProbabilityDistributions(const IFTDistribution2D& pdf_1, const IFTDistribution2D& pdf_2);

    double evaluate(const kvector_t q) const final;

    std::vector<double> getDomainSizes() const;
    std::vector<const IFTDistribution2D*> getProbabilityDistributions() const;

    void setIntegrationOverXi(bool integrate_xi) { m_integrate_xi = integrate_xi; }
    bool getIntegrationOverXi() const { return m_integrate_xi; }
    double getDampingLength() const { return m_damping_length; }

    Lattice2DParameters getLatticeParameters() const { return m_lattice_params; }

    std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const final;

    double getParticleDensity() const final;

private:
    void init_parameters();
    double interferenceForXi(double xi) const;
    double interference1D(double qx, double qy, double xi, size_t index) const;
    complex_t FTPDF(double qx, double qy, double xi, size_t index) const;
    void transformToPrincipalAxes(
        double qx, double qy, double gamma, double delta, double& q_pa_1, double& q_pa_2) const;

    Lattice2DParameters m_lattice_params; //!< Lattice parameters
    bool m_integrate_xi; //!< Integrate over the orientation xi
    IFTDistribution2D* m_pdfs[2];
    double m_damping_length; //!< Damping length for removing delta function singularity at q=0.
    bool m_use_damping_length; //!< Flag that determines if the damping length should be used.
    double m_domain_sizes[2]; //!< Coherence domain sizes
    mutable double m_qx;
    mutable double m_qy;
#ifndef SWIG
    std::unique_ptr<IntegratorReal<InterferenceFunction2DParaCrystal>> mP_integrator;
#endif
};

#endif // INTERFERENCEFUNCTION2DPARACRYSTAL_H
