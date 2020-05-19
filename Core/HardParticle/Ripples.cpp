// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/Ripples.cpp
//! @brief     Implements computations in namespace ripples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Ripples.h"
#include "MathFunctions.h"

complex_t ripples::factor_x_box(complex_t q, double r)
{
    return r * MathFunctions::sinc(q*r/2.0);
}

complex_t ripples::factor_x_Gauss(complex_t q, double r)
{
    return r * exp(-q*r/8.0);
}

complex_t ripples::factor_x_Lorentz(complex_t q, double r)
{
    return r / (1.0 + (q*r)*(q*r));
}
