//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/LibFF/SomeFormFactors.h
//! @brief     Declares namespace someff with some form factor functions.
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
#ifndef BORNAGAIN_SAMPLE_LIBFF_SOMEFORMFACTORS_H
#define BORNAGAIN_SAMPLE_LIBFF_SOMEFORMFACTORS_H

#include "Base/Types/Complex.h"
#include "Base/Vector/Vectors3D.h"

//! Some form factor functions.

namespace someff {

complex_t ffSphere(cvector_t q, double R);

} // namespace someff

#endif // BORNAGAIN_SAMPLE_LIBFF_SOMEFORMFACTORS_H
#endif // USER_API
