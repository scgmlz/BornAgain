//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/RootScalarFunction.h
//! @brief     Defines classes RootScalarFunction
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
#ifndef BORNAGAIN_FIT_ADAPTER_ROOTSCALARFUNCTION_H
#define BORNAGAIN_FIT_ADAPTER_ROOTSCALARFUNCTION_H

#include "Fit/Minimizer/Types.h"

#ifdef _WIN32
#include <Math/Functor.h>
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <Math/Functor.h>
#pragma GCC diagnostic pop
#endif

//! The chi2 function for use in minimizers.
//! @ingroup fitting_internal

class RootScalarFunction : public ROOT::Math::Functor {
public:
    RootScalarFunction(root_scalar_t fcn, int ndims);
};

#endif // BORNAGAIN_FIT_ADAPTER_ROOTSCALARFUNCTION_H
#endif // USER_API
