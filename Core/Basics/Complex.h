// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Complex.h
//! @brief     Defines complex_t, and a few elementary functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_COMPLEX_H
#define BORNAGAIN_CORE_BASICS_COMPLEX_H

#include <complex>

typedef std::complex<double> complex_t;

//! Returns product I*z, where I is the imaginary unit.
inline complex_t mul_I(complex_t z)
{
    return complex_t(-z.imag(), z.real());
}

//! Returns exp(I*z), where I is the imaginary unit.
inline complex_t exp_I(complex_t z)
{
    return std::exp(complex_t(-z.imag(), z.real()));
}

#endif // BORNAGAIN_CORE_BASICS_COMPLEX_H
