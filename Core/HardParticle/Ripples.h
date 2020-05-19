// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/Ripples.h
//! @brief     Declares computations in namespace ripples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Complex.h"

//! Computations for elongated particles.
namespace ripples {

complex_t factor_x_box(complex_t q, double l);
complex_t factor_x_Gauss(complex_t q, double l);
complex_t factor_x_Lorentz(complex_t q, double l);

} // namespace ripples
