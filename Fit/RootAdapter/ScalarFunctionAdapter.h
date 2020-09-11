// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/ScalarFunctionAdapter.h
//! @brief     Defines class ScalarFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_ROOTADAPTER_SCALARFUNCTIONADAPTER_H
#define BORNAGAIN_FIT_ROOTADAPTER_SCALARFUNCTIONADAPTER_H

#include "Fit/Kernel/IFunctionAdapter.h"
#include "Fit/Kernel/KernelTypes.h"
#include "Fit/Kernel/Parameters.h"
#include <functional>
#include <memory>
#include <vector>

class RootScalarFunction;

namespace Fit
{

//! Converts user objective function to chi2 like function which ROOT expects.

//! More precisely, ROOT call to std::function<double(const double*)> will cause
//! the call of user function std::function<double(std::vector<double>)>, where
//! function input parameters will be current values fit parameters.

class ScalarFunctionAdapter : public IFunctionAdapter
{
public:
    ScalarFunctionAdapter(fcn_scalar_t func, const Parameters& parameters);

    const RootScalarFunction* rootObjectiveFunction();

private:
    fcn_scalar_t m_fcn; // user function to minimize
    Parameters m_parameters;
    std::unique_ptr<RootScalarFunction> m_root_objective;
};

} //  namespace Fit

#endif // BORNAGAIN_FIT_ROOTADAPTER_SCALARFUNCTIONADAPTER_H
