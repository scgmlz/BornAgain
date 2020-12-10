//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Py/PyUtils.h
//! @brief     Defines PyUtils namespace
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
#ifndef BORNAGAIN_BASE_PY_PYEMBEDDEDUTILS_H
#define BORNAGAIN_BASE_PY_PYEMBEDDEDUTILS_H

#ifdef BORNAGAIN_PYTHON

#include "Base/Py/PyObject.h"
#include <memory>
#include <string>
#include <vector>

class MultiLayer;

namespace PyUtils {

//! Converts PyObject into string, if possible, or throws exception.
std::string toString(PyObject* obj);

//! Converts PyObject into vector of strings, if possible, or throws exception.
std::vector<std::string> toVectorString(PyObject* obj);

//! Converts char to string. In the case of nullptr will return an empty string.
std::string toString(char* c);
std::string toString(wchar_t* c);

//! Imports BornAgain from given location. If path is empty, tries to rely on PYTHONPATH.
void import_bornagain(const std::string& path = "");

//! Returns multi-line string representing PATH, PYTHONPATH, sys.path and other info.
std::string pythonRuntimeInfo();

//! Returns string representing python stack trace.
std::string pythonStackTrace();

PyObject* createNumpyArray(const std::vector<double>& data);

} // namespace PyUtils

#endif // BORNAGAIN_PYTHON

#endif // BORNAGAIN_BASE_PY_PYEMBEDDEDUTILS_H
#endif // USER_API
