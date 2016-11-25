// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionRadialParaCrystal.h
//! @brief     Defines class InterferenceFunctionRadialParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H
#define INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H

#include "Complex.h"
#include "FTDistributions1D.h"
#include "IInterferenceFunction.h"
#include <memory>

//! Interference function of radial paracrystal.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionRadialParaCrystal : public IInterferenceFunction
{
public:
    InterferenceFunctionRadialParaCrystal(double peak_distance, double damping_length = 0.0);
    InterferenceFunctionRadialParaCrystal* clone() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    std::string to_str(int indent = 0) const final;

    void setKappa(double kappa) { m_kappa = kappa; }
    double getKappa() const final { return m_kappa; }

    void setDomainSize(double size) { m_domain_size = size; }
    double getDomainSize() const { return m_domain_size; }

    double evaluate(const kvector_t q) const final;
    // TODO: replace these with strategy pattern for different algorithms
    complex_t FTPDF(double qpar) const;

    void setProbabilityDistribution(const IFTDistribution1D& pdf);
    const IFTDistribution1D* getProbabilityDistribution() const { return mP_pdf.get(); }

    double getPeakDistance() const { return m_peak_distance; }

    double getDampingLength() const { return m_damping_length; }

private:
    void init_parameters();

    double m_peak_distance; //!< the distance to the first neighbor peak
    double m_damping_length; //!< damping length of paracrystal
    //! Fourier transformed probability distribution of the nearest particle
    std::unique_ptr<IFTDistribution1D> mP_pdf;
    bool m_use_damping_length;
    double m_kappa; //!< Size-spacing coupling parameter
    double m_domain_size; //!< Size of coherence domain
};

#endif // INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H
