// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Macros.h
//! @brief     Workarounds concerning diagnostic warnings.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MACROS_H
#define MACROS_H

/*
Macros below serve for temporary switching off specific warnings.
It should be used to get rid from warnings coming from the third party library (like boost).

Usage:
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_ON(unused-parameter);

For the gcc 4.6 macros have same behavior as
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic pop

Be aware, that macros has different behavior for gcc<4.2, 4.2<=gcc<4.6; gcc>=4.6
See origin and explanations at
http://dbp-consulting.com/tutorials/SuppressingGCCWarnings.html
and then
http://gcc.gnu.org/onlinedocs/gcc-4.4.7/gcc/Diagnostic-Pragmas.html
*/

#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#define GCC_DIAG_STR(s) #s
#define GCC_DIAG_JOINSTR(x, y) GCC_DIAG_STR(x##y)
#define GCC_DIAG_DO_PRAGMA(x) _Pragma(#x)
#define GCC_DIAG_PRAGMA(x) GCC_DIAG_DO_PRAGMA(GCC diagnostic x)
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#define GCC_DIAG_OFF(x)                                                                            \
    GCC_DIAG_PRAGMA(push)                                                                          \
    GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W, x))
#define GCC_DIAG_ON(x) GCC_DIAG_PRAGMA(pop)
#else
#define GCC_DIAG_OFF(x) GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W, x))
#define GCC_DIAG_ON(x) GCC_DIAG_PRAGMA(warning GCC_DIAG_JOINSTR(-W, x))
#endif
#else
#define GCC_DIAG_OFF(x)
#define GCC_DIAG_ON(x)
#endif

#endif // MACROS_H
