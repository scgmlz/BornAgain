//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Fresnel/FormFactorCoherentPart.h
//! @brief     Defines class FormFactorCoherentPart.
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
#ifndef BORNAGAIN_SAMPLE_FRESNEL_FORMFACTORCOHERENTPART_H
#define BORNAGAIN_SAMPLE_FRESNEL_FORMFACTORCOHERENTPART_H

#include "Base/Types/Complex.h"
#include "Base/Vector/EigenCore.h"
#include <memory>

class IFresnelMap;
class IComputeFF;
class SimulationElement;

//! Information about single particle form factor and specular info of the embedding layer.
//! @ingroup formfactors_internal

class FormFactorCoherentPart {
public:
    FormFactorCoherentPart(IComputeFF* ff);
    FormFactorCoherentPart(const FormFactorCoherentPart& other);
    FormFactorCoherentPart(FormFactorCoherentPart&& other);
    FormFactorCoherentPart& operator=(const FormFactorCoherentPart& other);
    FormFactorCoherentPart& operator=(FormFactorCoherentPart&& other);
    ~FormFactorCoherentPart();

    complex_t evaluate(const SimulationElement& sim_element) const;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const SimulationElement& sim_element) const;
#endif

    void setSpecularInfo(const IFresnelMap* fresnel_map, size_t layer_index);
    double radialExtension() const;

private:
    std::unique_ptr<IComputeFF> m_ff;
    const IFresnelMap* m_fresnel_map;
    size_t m_layer_index;
};

#endif // BORNAGAIN_SAMPLE_FRESNEL_FORMFACTORCOHERENTPART_H
#endif // USER_API
