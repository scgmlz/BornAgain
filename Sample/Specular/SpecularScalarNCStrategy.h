//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularScalarNCStrategy.h
//! @brief     Defines class SpecularScalarNCStrategy.
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
#ifndef BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARNCSTRATEGY_H
#define BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARNCSTRATEGY_H

#include "Sample/Specular/SpecularScalarStrategy.h"

class Slice;

//! Implements Nevot-Croce roughness for a scaler computation.
//!
//! Implements the transition function that includes Nevot-Croce roughness
//! in the computation of the coefficients for coherent wave propagation
//! in a multilayer by applying modified Fresnel coefficients.
//!
//! @ingroup algorithms_internal

class SpecularScalarNCStrategy : public SpecularScalarStrategy {
private:
    //! Roughness is modelled by a Gaussian profile, i.e. Nevot-Croce factors for the
    //! reflection coefficients.
    //! Implementation follows A. Gibaud and G. Vignaud, in X-ray and Neutron Reflectivity, edited
    //! by J. Daillant and A. Gibaud, volume 770 of Lecture Notes in Physics (2009)
    virtual std::pair<complex_t, complex_t> transition(complex_t kzi, complex_t kzi1,
                                                       double sigma) const override;
};

#endif // BORNAGAIN_SAMPLE_SPECULAR_SPECULARSCALARNCSTRATEGY_H
#endif // USER_API
