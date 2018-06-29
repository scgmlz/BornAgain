// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/PyBuilderCallback.h
//! @brief     Defines class PyBuilderCallback.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PYBUILDERCALLBACK_H
#define PYBUILDERCALLBACK_H

#include "Parameters.h"
#include "WinDllMacros.h"
#include <vector>

class Simulation;

//! Builds simulation object using a Python callable.
//! Base class to wrap Python callable and pass it to C++. Used in swig interface file,
//! intended to be overloaded from Python.

class BA_CORE_API_ PyBuilderCallback
{
public:
    PyBuilderCallback();
    virtual ~PyBuilderCallback();

    virtual Simulation* build_simulation(Fit::Parameters);

};

#endif //  PYBUILDERCALLBACK_H
