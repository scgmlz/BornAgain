// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorWrapper.h
//! @brief     Defines class FormFactorWrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORWRAPPER_H
#define FORMFACTORWRAPPER_H

#include "ICloneable.h"
#include "Complex.h"
#include "EigenCore.h"
#include <memory>

class IFormFactor;
class SimulationElement;
class LayerSpecularInfo;

//! Information about particle form factor and abundance.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorWrapper : public ICloneable
{
public:
    FormFactorWrapper(IFormFactor* ff, double abundance);
    virtual ~FormFactorWrapper();
    virtual FormFactorWrapper* clone() const;

    complex_t evaluate(const SimulationElement& sim_element) const;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const SimulationElement& sim_element) const;
#endif

    IFormFactor* formfactor();
    const IFormFactor* formfactor() const;
    void setSpecularInfo(const LayerSpecularInfo& specular_info);
    double relativeAbundance() const { return m_abundance; }
    void scaleRelativeAbundance(double total_abundance);
    double radialExtension() const;

private:
    std::unique_ptr<IFormFactor> mP_ff;
    std::unique_ptr<LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA
    double m_abundance;
};

#endif // FORMFACTORWRAPPER_H
