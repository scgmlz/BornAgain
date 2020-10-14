// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Utils/Assert.h
//! @brief     Defines the macro ASSERT.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_BASE_UTILS_ASSERT_H
#define BORNAGAIN_BASE_UTILS_ASSERT_H

// ASSERT must be declared as a macro, not a function, in order for the error
// message to correctly report the source line where the assertion failed.

#ifdef HAVE_QT

#include <QtGlobal>
#define ASSERT(condition)                                                                          \
    if (!(condition))                                                                              \
    qFatal("Assertion %s failed in %s, line %d", (#condition), __FILE__, __LINE__)

#else // HAVE_QT undefined

#include <cassert>
#define ASSERT(condition) assert(condition)

#endif // HAVE_QT

#endif // BORNAGAIN_BASE_UTILS_ASSERT_H
