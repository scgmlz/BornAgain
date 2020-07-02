// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootScalarFunction.h
//! @brief     Defines classes RootScalarFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ROOTSCALARFUNCTION_H
#define ROOTSCALARFUNCTION_H

#include "KernelTypes.h"

#ifdef _WIN32
#include "Math/Functor.h"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/Functor.h"
#pragma GCC diagnostic pop
#endif

//! The chi2 function for use in minimizers.
//! @ingroup fitting_internal

class RootScalarFunction : public ROOT::Math::Functor
{
public:
    RootScalarFunction(root_scalar_t fcn, int ndims);
};

#endif // ROOTSCALARFUNCTION_H
