// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialFactoryFuncs.h
//! @brief     Factory functions used to create material instances.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALFACTORYFUNCS_H_
#define MATERIALFACTORYFUNCS_H_

#include "Material.h"

struct HomogeneousRegion;

//! @ingroup materials

BA_CORE_API_ Material HomogeneousMaterial();

//! @ingroup materials

BA_CORE_API_ Material HomogeneousMaterial(const std::string& name, double delta, double beta,
                                              kvector_t magnetization = kvector_t());

//! @ingroup materials

//! Constructs a material with _name_, _refractive_index_ and _magnetization_ (in A/m).
//! Alternatively,
//! \f$\delta\f$ and \f$\beta\f$ for refractive index \f$n = 1 - \delta + i \beta\f$ can be passed
//! directly.
//! With no parameters given, constructs default (vacuum) material with \f$n = 1\f$ and zero
//! magnetization.
BA_CORE_API_ Material HomogeneousMaterial(const std::string& name, complex_t refractive_index,
                                              kvector_t magnetization = kvector_t());

//! @ingroup materials

BA_CORE_API_ Material MaterialBySLD();

//! @ingroup materials

//! Constructs a wavelength-independent material with a given complex-valued
//! scattering length density (SLD).
//! SLD values for a wide variety of materials can be found on
//! https://sld-calculator.appspot.com/
//! and
//! https://www.ncnr.nist.gov/resources/activation/
//! By convention, SLD imaginary part is treated as negative by default, which corresponds to
//! attenuation of the signal.
//! With no parameters given, MaterialBySLD constructs default (vacuum) material with zero sld
//! and zero magnetization.
//! @param name: material name
//! @param sld_real: real part of the scattering length density, inverse square angstroms
//! @param sld_imag: imaginary part of the scattering length density, inverse square angstroms
//! @param magnetization: magnetization (in A/m)
BA_CORE_API_ Material MaterialBySLD(const std::string& name, double sld_real, double sld_imag,
                                    kvector_t magnetization = kvector_t());

#ifndef SWIG

//! @ingroup materials

//! Creates averaged material. Square refractive index of returned material is arithmetic mean over
//! _regions_ and _layer_mat_. Magnetization (if present) is averaged linearly.
BA_CORE_API_ Material CreateAveragedMaterial(const Material& layer_mat,
                                             const std::vector<HomogeneousRegion>& regions);

#endif //SWIG

#endif /* MATERIALFACTORYFUNCS_H_ */
