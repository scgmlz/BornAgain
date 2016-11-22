// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootObjectiveFuncAdapter.h
//! @brief     Declares class RootObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTOBJECTIVEFUNCADAPTER_H
#define ROOTOBJECTIVEFUNCADAPTER_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include <memory>
#include <vector>

class RootObjectiveFunction;
class RootGradientFunction;

//! Adapts our objective functions to ROOT.
//! @ingroup fitting_internal

class BA_CORE_API_ RootObjectiveFunctionAdapter
{
public:
    RootObjectiveFunctionAdapter();

    void setObjectiveCallback(objective_function_t func);
    void setGradientCallback(gradient_function_t func, int ndatasize);

    void setNumberOfParameters(int nparameters);

    const RootObjectiveFunction* rootChiSquaredFunction();

    const RootGradientFunction* rootGradientFunction();

private:
    double evaluate(const double* pars);
    double evaluate_gradient(const double* pars, unsigned int index, double* gradients);

    objective_function_t m_objective_callback;
    gradient_function_t m_gradient_callback;

    std::unique_ptr<RootObjectiveFunction> m_root_objective_function;
    std::unique_ptr<RootGradientFunction> m_root_gradient_function;

    int m_nparameters;
    int m_ndatasize;
};

#endif // ROOTOBJECTIVEFUNCADAPTER_H
