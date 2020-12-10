//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Py/PyCore.h
//! @brief     Includes python header and takes care of warnings.
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
#ifndef BORNAGAIN_BASE_PY_PYCORE_H
#define BORNAGAIN_BASE_PY_PYCORE_H

#ifdef BORNAGAIN_PYTHON

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include <Python.h>
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#define NO_IMPORT_ARRAY
#include <numpy/arrayobject.h>

#include "auto/Wrap/swig_runtime.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif // BORNAGAIN_PYTHON

#endif // BORNAGAIN_BASE_PY_PYCORE_H
#endif // USER_API
