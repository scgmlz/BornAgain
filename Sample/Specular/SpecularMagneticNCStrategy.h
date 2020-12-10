//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularMagneticNCStrategy.h
//! @brief     Defines class SpecularMagneticNCStrategy.
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
#ifndef BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICNCSTRATEGY_H
#define BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICNCSTRATEGY_H

#include "Sample/Specular/SpecularMagneticStrategy.h"
#include <memory>
#include <vector>

//! Implements the magnetic Fresnel computation with Nevot-Croce roughness
//!
//! Implements the transfer matrix formalism for the calculation of wave
//! amplitudes of the coherent wave solution in a multilayer with magnetization.
//! For a description, see internal
//! document "Polarized Implementation of the Transfer Matrix Method"
//!
//! @ingroup algorithms_internal
class SpecularMagneticNCStrategy : public SpecularMagneticStrategy {
private:
    std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
    computeRoughnessMatrices(const MatrixRTCoefficients& coeff_i,
                             const MatrixRTCoefficients& coeff_i1, double sigma) const;

    virtual std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
    computeBackwardsSubmatrices(const MatrixRTCoefficients& coeff_i,
                                const MatrixRTCoefficients& coeff_i1, double sigma) const;
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICNCSTRATEGY_H
#endif // USER_API
