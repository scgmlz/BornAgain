//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularScalarStrategy.h
//! @brief     Defines class SpecularScalarStrategy.
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
#ifndef BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARSTRATEGY_H
#define BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARSTRATEGY_H

#include "Sample/RT/ScalarRTCoefficients.h"
#include "Sample/Specular/ISpecularStrategy.h"
#include <memory>
#include <vector>

class Slice;

//! Implements the scalar Fresnel computation
//!
//! Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer.
//!
//! Inherited by SpecularScalarNCStrategy, SpecularScalarTanhStrategy
//!
//! @ingroup algorithms_internal
class SpecularScalarStrategy : public ISpecularStrategy {
public:
    // TODO remove once external test code is not needed anmyore
    // for the moment i need them!
    using coefficient_type = ScalarRTCoefficients;
    using coefficient_pointer_type = std::unique_ptr<const coefficient_type>;
    using coeffs_t = std::vector<coefficient_pointer_type>;

    //! Computes refraction angles and transmission/reflection coefficients
    //! for given coherent wave propagation in a multilayer.
    virtual ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices,
                                                const kvector_t& k) const override;

    virtual ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices,
                                                const std::vector<complex_t>& kz) const override;

private:
    virtual std::pair<complex_t, complex_t> transition(complex_t kzi, complex_t kzi1,
                                                       double sigma) const = 0;

    std::vector<ScalarRTCoefficients> computeTR(const std::vector<Slice>& slices,
                                                const std::vector<complex_t>& kz) const;

    static void setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer);

    void calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff,
                              const std::vector<Slice>& slices,
                              const std::vector<complex_t>& kz) const;
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARSTRATEGY_H
#endif // USER_API
