//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/LegacyRT/SpecularMagneticStrategy_v2.h
//! @brief     Defines class SpecularMagneticStrategy_v2.
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
#ifndef BORNAGAIN_CORE_LEGACY_SPECULARMAGNETICSTRATEGY_V2_H
#define BORNAGAIN_CORE_LEGACY_SPECULARMAGNETICSTRATEGY_V2_H

#include "MatrixRTCoefficients_v2.h"
#include "Sample/Specular/ISpecularStrategy.h"
#include <memory>
#include <vector>

class Slice;

//! Implements the magnetic Fresnel computation without roughness
//!
//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization.
//! For a detailed description see internal document "Polarized Specular Reflectometry"
//!
//! @ingroup algorithms_internal
class SpecularMagneticStrategy_v2 : public ISpecularStrategy {
public:
    // TODO remove once external test code is not needed anmyore
    // for the moment i need them!
    using coefficient_type = MatrixRTCoefficients_v2;
    using coefficient_pointer_type = std::unique_ptr<const coefficient_type>;
    using coeffs_t = std::vector<coefficient_pointer_type>;

    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and wavevector k
    ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices, const kvector_t& k) const;

    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and a set of kz projections corresponding to each slice
    ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices,
                                        const std::vector<complex_t>& kz) const;

private:
    static std::vector<MatrixRTCoefficients_v2> computeTR(const std::vector<Slice>& slices,
                                                          const std::vector<complex_t>& kzs);

    //! Computes frobenius matrices for multilayer solution
    static void calculateTR(MatrixRTCoefficients_v2& coeff);
    static void calculateZeroFieldTR(MatrixRTCoefficients_v2& coeff);

    static void setNoTransmission(MatrixRTCoefficients_v2& coeff);

    //! initializes reflectionless bottom boundary condition.
    static void nullifyBottomReflection(MatrixRTCoefficients_v2& coeff);

    //! Propagates boundary conditions from the bottom to the top of the layer stack.
    //! Used to compute boundary conditions from the bottom one (with nullified reflection)
    //! simultaneously propagates amplitudes forward again
    //! Due to the use of temporary objects this is combined into one function now
    static void propagateBackwardsForwards(std::vector<MatrixRTCoefficients_v2>& coeff,
                                           const std::vector<Slice>& slices);

    //! finds linear coefficients for normalizing transmitted wave to unity.
    //! The left column of the returned matrix corresponds to the coefficients for pure spin-up
    //! wave, while the right column - to the coefficients for the spin-down one.
    static std::pair<Eigen::Matrix2cd, complex_t>
    findNormalizationCoefficients(const MatrixRTCoefficients_v2& coeff);
};

#endif // BORNAGAIN_CORE_LEGACY_SPECULARMAGNETICSTRATEGY_V2_H
#endif // USER_API
