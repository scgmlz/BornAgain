//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularMagneticTanhStrategy.h
//! @brief     Defines class SpecularMagneticTanhStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICTANHSTRATEGY_H
#define BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICTANHSTRATEGY_H

#include "Sample/Specular/SpecularMagneticStrategy.h"

//! Implements the magnetic Fresnel computation with the analytical Tanh roughness
//!
//! Implements the transfer matrix formalism for the calculation of wave
//! amplitudes of the coherent wave solution in a multilayer with magnetization.
//! For a description, see internal
//! document "Polarized Implementation of the Transfer Matrix Method"
//!
//! @ingroup algorithms_internal
class SpecularMagneticTanhStrategy : public SpecularMagneticStrategy {
private:
    virtual std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
    computeBackwardsSubmatrices(const MatrixRTCoefficients& coeff_i,
                                const MatrixRTCoefficients& coeff_i1, double sigma) const;

    Eigen::Matrix2cd computeRoughnessMatrix(const MatrixRTCoefficients& coeff, double sigma,
                                            bool inverse = false) const;
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICTANHSTRATEGY_H
#endif // USER_API
