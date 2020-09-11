// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootScalarFunction.cpp
//! @brief     Implements class RootScalarFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/RootScalarFunction.h"

RootScalarFunction::RootScalarFunction(root_scalar_t fcn, int ndims)
    : ROOT::Math::Functor(fcn, static_cast<unsigned int>(ndims))
{
}
