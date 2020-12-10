//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/IFunctionAdapter.h
//! @brief     Defines interface IFunctionAdapter.
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
#ifndef BORNAGAIN_FIT_ADAPTER_IFUNCTIONADAPTER_H
#define BORNAGAIN_FIT_ADAPTER_IFUNCTIONADAPTER_H

namespace mumufit {

//! Base class for objective function adapters, which converts user functions
//! to minimize into the function which minimization machinery expects.

class IFunctionAdapter {
public:
    IFunctionAdapter();
    virtual ~IFunctionAdapter();

    int numberOfCalls() const;
    int numberOfGradientCalls() const;

protected:
    int m_number_of_calls;
    int m_number_of_gradient_calls;
};

} // namespace mumufit

#endif // BORNAGAIN_FIT_ADAPTER_IFUNCTIONADAPTER_H
#endif // USER_API
