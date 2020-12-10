//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/LegacyRT/SpecularMagneticStrategy_v1.h
//! @brief     Defines class SpecularMagneticStrategy_v1.
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
#ifndef BORNAGAIN_CORE_LEGACY_SPECULARMAGNETICSTRATEGY_V1_H
#define BORNAGAIN_CORE_LEGACY_SPECULARMAGNETICSTRATEGY_V1_H

#include "MatrixRTCoefficients_v1.h"
#include "Sample/Specular/ISpecularStrategy.h"
#include <memory>
#include <vector>

class Slice;

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization.
//! @ingroup algorithms_internal

class SpecularMagneticStrategy_v1 : public ISpecularStrategy {
public:
    // TODO remove once external test code is not needed anmyore
    // for the moment i need them!
    using coefficient_type = MatrixRTCoefficients_v1;
    using coefficient_pointer_type = std::unique_ptr<const coefficient_type>;
    using coeffs_t = std::vector<coefficient_pointer_type>;

    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and wavevector k
    ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices, const kvector_t& k) const;

    ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices,
                                        const std::vector<complex_t>& kz) const;

}; // class SpecularMagneticStrategy_v1

#endif // BORNAGAIN_CORE_LEGACY_SPECULARMAGNETICSTRATEGY_V1_H
#endif // USER_API
