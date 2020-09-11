// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionRadialParaCrystal.h
//! @brief     Defines class InterferenceFunctionRadialParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H
#define BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Basics/Complex.h"
#include "Core/Correlations/FTDistributions1D.h"
#include <memory>

//! Interference function of radial paracrystal.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunctionRadialParaCrystal : public IInterferenceFunction
{
public:
    InterferenceFunctionRadialParaCrystal(double peak_distance, double damping_length);
    InterferenceFunctionRadialParaCrystal* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setKappa(double kappa);
    double kappa() const;

    void setDomainSize(double size);
    double domainSize() const { return m_domain_size; }

    complex_t FTPDF(double qpar) const;

    void setProbabilityDistribution(const IFTDistribution1D& pdf);

    double peakDistance() const { return m_peak_distance; }

    double dampingLength() const { return m_damping_length; }

    std::vector<const INode*> getChildren() const override final;

    double randomSample() const { return mP_pdf->createSampler()->randomSample(); }

private:
    double iff_without_dw(const kvector_t q) const override final;
    void init_parameters();

    double m_peak_distance;  //!< the distance to the first neighbor peak
    double m_damping_length; //!< damping length of paracrystal
    //! Fourier transformed probability distribution of the nearest particle
    std::unique_ptr<IFTDistribution1D> mP_pdf;
    bool m_use_damping_length;
    double m_kappa;       //!< Size-spacing coupling parameter
    double m_domain_size; //!< Size of coherence domain
};

#endif // BORNAGAIN_CORE_AGGREGATE_INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H
