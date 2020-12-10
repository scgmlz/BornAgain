//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/Ripples.h
//! @brief     Declares computations in namespace ripples.
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
#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_RIPPLES_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_RIPPLES_H

#include "Base/Types/Complex.h"

//! Computations for elongated particles.
namespace ripples {

complex_t factor_x_box(complex_t q, double l);
complex_t factor_x_Gauss(complex_t q, double l);
complex_t factor_x_Lorentz(complex_t q, double l);

complex_t profile_yz_bar(complex_t qy, complex_t qz, double width, double height);
complex_t profile_yz_cosine(complex_t qy, complex_t qz, double width, double height);
complex_t profile_yz_triangular(complex_t qy, complex_t qz, double width, double height,
                                double asymmetry);

} // namespace ripples

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_RIPPLES_H
#endif // USER_API
