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

#ifndef BORNAGAIN_CORE_MATERIAL_MATERIALFACTORYFUNCS_H
#define BORNAGAIN_CORE_MATERIAL_MATERIALFACTORYFUNCS_H

#include "Core/Material/Material.h"

struct HomogeneousRegion;

//! @ingroup materials

Material HomogeneousMaterial();

//! @ingroup materials

Material HomogeneousMaterial(const std::string& name, double delta, double beta,
                             kvector_t magnetization = {});

//! @ingroup materials

//! Constructs a material with _name_, _refractive_index_ and _magnetization_ (in A/m).
//! Alternatively,
//! \f$\delta\f$ and \f$\beta\f$ for refractive index \f$n = 1 - \delta + i \beta\f$ can be passed
//! directly.
//! With no parameters given, constructs default (vacuum) material with \f$n = 1\f$ and zero
//! magnetization.
Material HomogeneousMaterial(const std::string& name, complex_t refractive_index,
                             kvector_t magnetization = {});

//! @ingroup materials

Material MaterialBySLD();

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
Material MaterialBySLD(const std::string& name, double sld_real, double sld_imag,
                       kvector_t magnetization = {});

#endif // BORNAGAIN_CORE_MATERIAL_MATERIALFACTORYFUNCS_H
