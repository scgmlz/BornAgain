// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DParaCrystal.h
//! @brief     Defines class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DPARACRYSTAL_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DPARACRYSTAL_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Basics/Complex.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "Core/Lattice/Lattice2D.h"
#include <memory>

class IFTDistribution2D;

//! Interference function of a 2D paracrystal.
//! @ingroup interference

class InterferenceFunction2DParaCrystal : public IInterferenceFunction
{
public:
    InterferenceFunction2DParaCrystal(const Lattice2D& lattice, double damping_length,
                                      double domain_size_1, double domain_size_2);

    InterferenceFunction2DParaCrystal(double length_1, double length_2, double alpha, double xi,
                                      double damping_length);

    ~InterferenceFunction2DParaCrystal() final;

    InterferenceFunction2DParaCrystal* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    static InterferenceFunction2DParaCrystal* createSquare(double lattice_length,
                                                           double damping_length,
                                                           double domain_size_1,
                                                           double domain_size_2);
    static InterferenceFunction2DParaCrystal* createHexagonal(double lattice_length,
                                                              double damping_length,
                                                              double domain_size_1,
                                                              double domain_size_2);

    void setDomainSizes(double size_1, double size_2);

    void setProbabilityDistributions(const IFTDistribution2D& pdf_1,
                                     const IFTDistribution2D& pdf_2);

    void setDampingLength(double damping_length);

    std::vector<double> domainSizes() const;

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }
    double dampingLength() const { return m_damping_length; }

    const Lattice2D& lattice() const;

    double getParticleDensity() const override final;

    std::vector<const INode*> getChildren() const override final;

    const IFTDistribution2D* pdf1() const { return m_pdf1.get(); }

    const IFTDistribution2D* pdf2() const { return m_pdf2.get(); }

private:
    double iff_without_dw(const kvector_t q) const override final;
    void setLattice(const Lattice2D& lattice);

    double interferenceForXi(double xi) const;
    double interference1D(double qx, double qy, double xi, size_t index) const;
    complex_t FTPDF(double qx, double qy, double xi, size_t index) const;
    void transformToPrincipalAxes(double qx, double qy, double gamma, double delta, double& q_pa_1,
                                  double& q_pa_2) const;

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<IFTDistribution2D> m_pdf1, m_pdf2;
    std::unique_ptr<Lattice2D> m_lattice; // TODO ASAP name as in other i-fcts
    double m_damping_length;  //!< Damping length for removing delta function singularity at q=0.
    double m_domain_sizes[2]; //!< Coherence domain sizes
    mutable double m_qx;
    mutable double m_qy;
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTION2DPARACRYSTAL_H
