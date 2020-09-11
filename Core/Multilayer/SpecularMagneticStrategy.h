// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticStrategy.h
//! @brief     Defines class SpecularMagneticStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICSTRATEGY_H

#include "Core/Multilayer/ISpecularStrategy.h"
#include "Core/RT/MatrixRTCoefficients_v2.h"
#include "Core/Vector/Vectors3D.h"
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
class BA_CORE_API_ SpecularMagneticStrategy : public ISpecularStrategy
{
public:
    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and wavevector k
    ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices, const kvector_t& k) const;

    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and a set of kz projections corresponding to each slice
    ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices,
                                        const std::vector<complex_t>& kz) const;

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
    static void propagateBackwards(std::vector<MatrixRTCoefficients_v2>& coeff,
                                   const std::vector<Slice>& slices);

    //! finds linear coefficients for normalizing transmitted wave to unity.
    //! The left column of the returned matrix corresponds to the coefficients for pure spin-up
    //! wave, while the right column - to the coefficients for the spin-down one.
    static Eigen::Matrix2cd findNormalizationCoefficients(const MatrixRTCoefficients_v2& coeff);

    //! makes a linear combination of boundary conditions with using the given weights for each
    //! coefficient in the vector.
    static void propagateForwards(std::vector<MatrixRTCoefficients_v2>& coeff,
                                  const Eigen::Matrix2cd& weights);
};

#endif // BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICSTRATEGY_H
