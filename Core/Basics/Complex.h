// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Complex.h
//! @brief     Defines complex_t, and a few elementary functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPLEX_H
#define COMPLEX_H

#include <complex>

typedef std::complex<double> complex_t;

//! Returns product I*z, where I is the imaginary unit.
inline complex_t mul_I(complex_t z) { return complex_t(-z.imag(), z.real()); }

//! Returns exp(I*z), where I is the imaginary unit.
inline complex_t exp_I(complex_t z) { return std::exp(complex_t(-z.imag(), z.real())); }

#endif // COMPLEX_H
