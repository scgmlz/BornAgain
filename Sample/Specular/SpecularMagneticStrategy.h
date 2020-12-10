//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularMagneticStrategy.h
//! @brief     Defines class SpecularMagneticStrategy.
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
#ifndef BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICSTRATEGY_H
#define BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICSTRATEGY_H

#include "Sample/RT/MatrixRTCoefficients.h"
#include "Sample/Specular/ISpecularStrategy.h"
#include <memory>
#include <vector>

class Slice;

//! Implements the magnetic Fresnel computation with Nevot-Croce roughness
//!
//! Implements the transfer matrix formalism for the calculation of wave
//! amplitudes of the coherent wave solution in a multilayer with magnetization.
//! For a description, see internal
//! document "Polarized Implementation of the Transfer Matrix Method"
//!
//! @ingroup algorithms_internal
class SpecularMagneticStrategy : public ISpecularStrategy {
public:
    // TODO remove once external test code is not needed anmyore
    // for the moment i need them!
    using coefficient_type = MatrixRTCoefficients;
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
    std::vector<MatrixRTCoefficients> computeTR(const std::vector<Slice>& slices,
                                                const std::vector<complex_t>& kzs) const;

    virtual std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
    computeBackwardsSubmatrices(const MatrixRTCoefficients& coeff_i,
                                const MatrixRTCoefficients& coeff_i1, double sigma) const = 0;

    void calculateUpwards(std::vector<MatrixRTCoefficients>& coeff,
                          const std::vector<Slice>& slices) const;
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_SPECULARMAGNETICSTRATEGY_H
#endif // USER_API
