//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Material/MaterialUtils.h
//! @brief     Declares functions in namespace MaterialUtils
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
#ifndef BORNAGAIN_SAMPLE_MATERIAL_MATERIALUTILS_H
#define BORNAGAIN_SAMPLE_MATERIAL_MATERIALUTILS_H

#include "Sample/Material/Material.h"

//! A number of materials-related helper functions for internal use
//! @ingroup materials

namespace MaterialUtils {

//! Function for calculating the reduced potential, used for obtaining the Fresnel coefficients
//! (non-polarized material case)

complex_t ScalarReducedPotential(complex_t n, kvector_t k, double n_ref);

//! Function for calculating the reduced potential, used for obtaining the Fresnel coefficients
//! (polarized material case)

Eigen::Matrix2cd PolarizedReducedPotential(complex_t n, kvector_t b_field, kvector_t k,
                                           double n_ref);

// Utility to compute magnetization correction for reduced potential and scattering length density.
// Used with T = double, complex_t.

template <typename T>
Eigen::Matrix2cd MagnetizationCorrection(complex_t unit_factor, double magnetic_factor,
                                         BasicVector3D<T> polarization);

//! Checks if all non-default materials in _materials_ are of the same type and returns this type.
//! If several types of materials are involved, InvalidMaterialType identifier is returned.

MATERIAL_TYPES checkMaterialTypes(const std::vector<const Material*>& materials);

} // namespace MaterialUtils

#endif // BORNAGAIN_SAMPLE_MATERIAL_MATERIALUTILS_H
#endif // USER_API
