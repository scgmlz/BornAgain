//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Slice/KzComputation.h
//! @brief     Declares functions in namespace KzComputation.
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
#ifndef BORNAGAIN_SAMPLE_SLICE_KZCOMPUTATION_H
#define BORNAGAIN_SAMPLE_SLICE_KZCOMPUTATION_H

#include "Base/Types/Complex.h"
#include "Base/Vector/Vectors3D.h"
#include <vector>

class Slice;

//! Namespace containing functions for computing kz values for given multilayer and k (or kz) value
//! on the surface of the sample.
//! @ingroup samples_internal

namespace KzComputation {
/* Computes kz values from known k vector and slices with the following assumptions:
 * - the beam penetrates fronting medium from a side
 * - the wavelength is known for a distant point in vacuum (ref. index = 1)
 * - the incident angle is known for the sample surface
 *
 * This function is used in GISAS and off-spec computations mainly for back-compatibility
 * reasons and should be replaced with computeKzFromRefIndices.
 */
std::vector<complex_t> computeReducedKz(const std::vector<Slice>& slices, kvector_t k);

/* Computes kz values from kz of the incoming beam known at a distant point in vacuum.
 * It is assumed, that the beam penetrates fronting medium from a side.
 */
std::vector<complex_t> computeKzFromSLDs(const std::vector<Slice>& slices, double kz);

/* Computes kz values from k-vector of the incoming beam known at a distant point in vacuum.
 * It is assumed, that the beam penetrates fronting medium from a side.
 */
std::vector<complex_t> computeKzFromRefIndices(const std::vector<Slice>& slices, kvector_t k);
} // namespace KzComputation

#endif // BORNAGAIN_SAMPLE_SLICE_KZCOMPUTATION_H
#endif // USER_API
