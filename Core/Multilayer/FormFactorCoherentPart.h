// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorCoherentPart.h
//! @brief     Defines class FormFactorCoherentPart.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_FORMFACTORCOHERENTPART_H
#define BORNAGAIN_CORE_MULTILAYER_FORMFACTORCOHERENTPART_H

#include "Core/Basics/Complex.h"
#include "Core/Vector/EigenCore.h"
#include <memory>

class IFresnelMap;
class IFormFactor;
class SimulationElement;

//! Information about single particle form factor and specular info of the embedding layer.
//! @ingroup formfactors_internal

class FormFactorCoherentPart
{
public:
    FormFactorCoherentPart(IFormFactor* p_ff);
    FormFactorCoherentPart(const FormFactorCoherentPart& other);
    FormFactorCoherentPart(FormFactorCoherentPart&& other);
    FormFactorCoherentPart& operator=(const FormFactorCoherentPart& other);
    FormFactorCoherentPart& operator=(FormFactorCoherentPart&& other);
    ~FormFactorCoherentPart();

    complex_t evaluate(const SimulationElement& sim_element) const;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const SimulationElement& sim_element) const;
#endif

    void setSpecularInfo(const IFresnelMap* p_fresnel_map, size_t layer_index);
    double radialExtension() const;

private:
    std::unique_ptr<IFormFactor> mP_ff;
    const IFresnelMap* mp_fresnel_map;
    size_t m_layer_index;
};

#endif // BORNAGAIN_CORE_MULTILAYER_FORMFACTORCOHERENTPART_H
