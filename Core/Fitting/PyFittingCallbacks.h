//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/PyFittingCallbacks.h
//! @brief     Defines family of PyFittingCallbacks classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_FITTING_PYFITTINGCALLBACKS_H
#define BORNAGAIN_CORE_FITTING_PYFITTINGCALLBACKS_H

//! Collection of wrapper classes to call Python callable from C++.

#include "Fit/Param/Parameters.h"

class ISimulation;

//! Builds simulation object using a Python callable.
//! Base class to wrap Python callable and pass it to C++. Used in swig interface file,
//! intended to be overloaded from Python.

class PyBuilderCallback {
public:
    PyBuilderCallback();
    virtual ~PyBuilderCallback();

    virtual ISimulation* build_simulation(mumufit::Parameters);
};

class FitObjective;

//! Observer for FitObjective based on Python callable.
//! Base class to wrap Python callable and pass it to C++. Used in swig interface file,
//! intended to be overloaded from Python.

class PyObserverCallback {
public:
    PyObserverCallback();
    virtual ~PyObserverCallback();

    virtual void update(const FitObjective&);
};

#endif // BORNAGAIN_CORE_FITTING_PYFITTINGCALLBACKS_H
