//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Fresnel/FormFactorCoherentSum.h
//! @brief     Defines class FormFactorCoherentSum.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_FRESNEL_FORMFACTORCOHERENTSUM_H
#define BORNAGAIN_SAMPLE_FRESNEL_FORMFACTORCOHERENTSUM_H

#include "Sample/Fresnel/FormFactorCoherentPart.h"
#include <vector>

class SimulationElement;

//! Information about particle form factor and abundance.
//! @ingroup formfactors_internal

class FormFactorCoherentSum {
public:
    FormFactorCoherentSum(double abundance);

    void addCoherentPart(const FormFactorCoherentPart& part);

    complex_t evaluate(const SimulationElement& sim_element) const;

#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const SimulationElement& sim_element) const;
#endif

    double relativeAbundance() const { return m_abundance; }
    void scaleRelativeAbundance(double total_abundance);
    double radialExtension() const;

private:
    FormFactorCoherentSum(const std::vector<FormFactorCoherentPart>& parts, double abundance);
    std::vector<FormFactorCoherentPart> m_parts;
    double m_abundance;
};

#endif // BORNAGAIN_SAMPLE_FRESNEL_FORMFACTORCOHERENTSUM_H
#endif // USER_API
