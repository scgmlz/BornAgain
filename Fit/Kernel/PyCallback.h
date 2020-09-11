// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/PyCallback.h
//! @brief     Defines class PyCallback.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_KERNEL_PYCALLBACK_H
#define BORNAGAIN_FIT_KERNEL_PYCALLBACK_H

#include "Fit/Kernel/Parameters.h"
#include "Wrap/WinDllMacros.h"
#include <vector>

//! Base class to wrap Python callable and pass it to C++. Used in swig interface file,
//! intended to be overloaded from Python.

class BA_CORE_API_ PyCallback
{
public:
    enum CallbackType { SCALAR, RESIDUAL };

    PyCallback(CallbackType callback_type = SCALAR);
    virtual ~PyCallback();

    CallbackType callback_type() const;

    //! Call Python callable and returns its result. Intended to be overloaded in Python.
    //! @param pars: Fit parameters object (intentionally passed by value).
    //! @return value of objective function.
    virtual double call_scalar(Fit::Parameters pars);

    //! Call Python callable and returns its result. Intended to be overloaded in Python.
    //! @param pars: Fit parameters object (intentionally passed by value).
    //! @return vector of residuals
    virtual std::vector<double> call_residuals(Fit::Parameters);

private:
    CallbackType m_callback_type;
};

#endif // BORNAGAIN_FIT_KERNEL_PYCALLBACK_H
