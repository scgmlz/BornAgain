//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/ScalarFunctionAdapter.h
//! @brief     Defines class ScalarFunctionAdapter.
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
#ifndef BORNAGAIN_FIT_ADAPTER_SCALARFUNCTIONADAPTER_H
#define BORNAGAIN_FIT_ADAPTER_SCALARFUNCTIONADAPTER_H

#include "Fit/Adapter/IFunctionAdapter.h"
#include "Fit/Minimizer/Types.h"
#include "Fit/Param/Parameters.h"
#include <functional>
#include <memory>
#include <vector>

class RootScalarFunction;

namespace mumufit {

//! Converts user objective function to chi2 like function which ROOT expects.

//! More precisely, ROOT call to std::function<double(const double*)> will cause
//! the call of user function std::function<double(std::vector<double>)>, where
//! function input parameters will be current values fit parameters.

class ScalarFunctionAdapter : public IFunctionAdapter {
public:
    ScalarFunctionAdapter(fcn_scalar_t func, const Parameters& parameters);

    const RootScalarFunction* rootObjectiveFunction();

private:
    fcn_scalar_t m_fcn; // user function to minimize
    Parameters m_parameters;
    std::unique_ptr<RootScalarFunction> m_root_objective;
};

} //  namespace mumufit

#endif // BORNAGAIN_FIT_ADAPTER_SCALARFUNCTIONADAPTER_H
#endif // USER_API
