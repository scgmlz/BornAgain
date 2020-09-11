// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/ObjectiveFunctionAdapter.h
//! @brief     Declares class ObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_ROOTADAPTER_OBJECTIVEFUNCTIONADAPTER_H
#define BORNAGAIN_FIT_ROOTADAPTER_OBJECTIVEFUNCTIONADAPTER_H

#include "Fit/Kernel/KernelTypes.h"
#include "Wrap/WinDllMacros.h"
#include <memory>

class RootScalarFunction;
class RootResidualFunction;

namespace Fit
{

class IFunctionAdapter;
class Parameters;

//! Converts user objective function to function ROOT expects.
//! Handles time of life of function objects.

class ObjectiveFunctionAdapter
{
public:
    ObjectiveFunctionAdapter();
    ~ObjectiveFunctionAdapter();

    const RootScalarFunction* rootObjectiveFunction(fcn_scalar_t fcn, const Parameters& parameters);

    const RootResidualFunction* rootResidualFunction(fcn_residual_t fcn,
                                                     const Parameters& parameters);

    int numberOfCalls() const;
    int numberOfGradientCalls() const;

private:
    std::unique_ptr<IFunctionAdapter> m_adapter;
};

} // namespace Fit

#endif // BORNAGAIN_FIT_ROOTADAPTER_OBJECTIVEFUNCTIONADAPTER_H
