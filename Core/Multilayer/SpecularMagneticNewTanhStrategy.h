// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticNewTanhStrategy.h
//! @brief     Defines class SpecularMagneticNewTanhStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICNEWTANHSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICNEWTANHSTRATEGY_H

#include "Core/Multilayer/SpecularMagneticNewStrategy.h"
#include "Core/RT/MatrixRTCoefficients_v3.h"

//! Implements the magnetic Fresnel computation with the analytical Tanh roughness
//!
//! Implements the transfer matrix formalism for the calculation of wave
//! amplitudes of the coherent wave solution in a multilayer with magnetization.
//! For a description, see internal
//! document "Polarized Implementation of the Transfer Matrix Method"
//!
//! @ingroup algorithms_internal
class SpecularMagneticNewTanhStrategy : public SpecularMagneticNewStrategy
{
private:
    virtual std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
    computeBackwardsSubmatrices(const MatrixRTCoefficients_v3& coeff_i,
                                const MatrixRTCoefficients_v3& coeff_i1, double sigma) const;

    Eigen::Matrix2cd computeRoughnessMatrix(const MatrixRTCoefficients_v3& coeff, double sigma,
                                            bool inverse = false) const;
};

#endif // BORNAGAIN_CORE_MULTILAYER_SPECULARMAGNETICNEWTANHSTRATEGY_H
