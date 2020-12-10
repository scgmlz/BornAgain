//  ************************************************************************************************
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
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_BASE_UTILS_ASSERT_H
#define BORNAGAIN_BASE_UTILS_ASSERT_H

// ASSERT must be declared as a macro, not a function, in order for the error
// message to correctly report the source line where the assertion failed.

// For an alternative implementation that calls qFatal, see Base/Utils/Assert.h < 29oct20.

#include <sstream>
#include <stdexcept>

#define ASSERT(condition)                                                                          \
    if (!(condition)) {                                                                            \
        std::stringstream msg;                                                                     \
        msg << "Assertion " << (#condition) << " failed in " << __FILE__ << ", line " << __LINE__; \
        throw std::runtime_error(msg.str());                                                       \
    }

#endif // BORNAGAIN_BASE_UTILS_ASSERT_H
#endif // USER_API
