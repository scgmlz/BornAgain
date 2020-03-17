// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagnetic_v2.h
//! @brief     Defines class SpecularMagnetic_v2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARMAGNETICSTRATEGY_H
#define SPECULARMAGNETICSTRATEGY_H

#include "ISpecularStrategy.h"
#include "MatrixRTCoefficients_v2.h"
#include "Vectors3D.h"
#include <vector>

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization.
//! @ingroup algorithms_internal
class SpecularMagneticStrategy : public ISpecularStrategy
{
public:
    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and wavevector k
    std::vector<MatrixRTCoefficients_v2> eval(const std::vector<Slice>& slices,
                                                      const kvector_t& k) const;

    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and a set of kz projections corresponding to each slice
    std::vector<MatrixRTCoefficients_v2> eval(const std::vector<Slice>& slices,
                                                      const std::vector<complex_t>& kzs) const;



private:
    //! Computes frobenius matrices for multilayer solution
    static void calculateTR(MatrixRTCoefficients_v2& coeff);
    static void calculateZeroFieldTR(MatrixRTCoefficients_v2& coeff);


    static void setNoTransmission(MatrixRTCoefficients_v2& coeff);

    //! initializes reflectionless bottom boundary condition.
    void nullifyBottomReflection(MatrixRTCoefficients_v2& coeff) const;

    //! Propagates boundary conditions from the bottom to the top of the layer stack.
    //! Used to compute boundary conditions from the bottom one (with nullified reflection)
    void propagateBackwards(std::vector<MatrixRTCoefficients_v2>& coeff,
                                   const std::vector<Slice>& slices) const;

    //! finds linear coefficients for normalizing transmitted wave to unity.
    //! The left column of the returned matrix corresponds to the coefficients for pure spin-up
    //! wave, while the right column - to the coefficients for the spin-down one.
    Eigen::Matrix2cd findNormalizationCoefficients(const MatrixRTCoefficients_v2& coeff) const;

    //! makes a linear combination of boundary conditions with using the given weights for each
    //! coefficient in the vector.
    void propagateForwards(std::vector<MatrixRTCoefficients_v2>& coeff,
                                  const Eigen::Matrix2cd& weights) const;

};



//class Slice;

//class BA_CORE_API_ SpecularMagnetic_v2
//{
//public:


//};

#endif // SPECULARMAGNETICSTRATEGY_H
