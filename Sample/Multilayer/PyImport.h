//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Multilayer/PyImport.h
//! @brief     Defines PyImport namespace
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
#ifndef BORNAGAIN_SAMPLE_MULTILAYER_PYIMPORT_H
#define BORNAGAIN_SAMPLE_MULTILAYER_PYIMPORT_H

#ifdef BORNAGAIN_PYTHON

#include <memory>
#include <string>
#include <vector>

class MultiLayer;

namespace PyImport {

////! Returns directory name
// std::string bornagainPythonDir();

//! Creates a multi layer by running python code in embedded interpreter.
//! @param script: Python script
//! @param functionName: A function name in this script which produces a MultiLayer
//! @param path: A path to import BornAgain library. If empty, relies on PYTHONPATH
std::unique_ptr<MultiLayer> createFromPython(const std::string& script,
                                             const std::string& functionName,
                                             const std::string& path = "");

//! Returns list of functions defined in the script.
//! @param script: Python script
//! @param path: A path to import BornAgain library. If empty, relies on PYTHONPATH
std::vector<std::string> listOfFunctions(const std::string& script, const std::string& path = "");
} // namespace PyImport

#endif // BORNAGAIN_PYTHON

#endif // BORNAGAIN_SAMPLE_MULTILAYER_PYIMPORT_H
#endif // USER_API
