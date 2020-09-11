// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorCoherentSum.h
//! @brief     Defines class FormFactorCoherentSum.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_FORMFACTORCOHERENTSUM_H
#define BORNAGAIN_CORE_MULTILAYER_FORMFACTORCOHERENTSUM_H

#include "Core/Basics/Complex.h"
#include "Core/Multilayer/FormFactorCoherentPart.h"
#include "Core/Vector/EigenCore.h"
#include <vector>

class SimulationElement;

//! Information about particle form factor and abundance.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorCoherentSum
{
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

#endif // BORNAGAIN_CORE_MULTILAYER_FORMFACTORCOHERENTSUM_H
