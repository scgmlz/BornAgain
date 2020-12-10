//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularScalarTanhStrategy.h
//! @brief     Defines class SpecularScalarTanhStrategy.
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
#ifndef BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARTANHSTRATEGY_H
#define BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARTANHSTRATEGY_H

#include "Sample/Specular/SpecularScalarStrategy.h"

class Slice;

//! Implements an tanh transition function to model roughness in a scaler computation.
//!
//! Implements the transition function that includes the analytical roughness model
//! of an tanh interface transition in the computation of the coefficients for
//! coherent wave propagation in a multilayer by applying modified Fresnel coefficients.
//!
//! @ingroup algorithms_internal
class SpecularScalarTanhStrategy : public SpecularScalarStrategy {
private:
    //! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
    virtual std::pair<complex_t, complex_t> transition(complex_t kzi, complex_t kzi1,
                                                       double sigma) const override;
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARTANHSTRATEGY_H
#endif // USER_API
