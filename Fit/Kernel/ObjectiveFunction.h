// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/ObjectiveFunction.h
//! @brief     Declares class ObjectiveFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H

#include "WinDllMacros.h"
#include "KernelTypes.h"

//! Information about an objective function, i.e. a function that shall be minimized.
//! @ingroup fitting_internal

class BA_CORE_API_ ObjectiveFunction
{
public:
    ObjectiveFunction();

    void setObjectiveFunction(objective_function_t func);
    void setGradientFunction(gradient_function_t func, int ndatasize);

    double evaluate(const std::vector<double>& pars);

    double evaluate_gradient(const std::vector<double>& pars, int index,
                             std::vector<double> &gradient);

    int functionCalls() const { return m_ncalls; }

    int sizeOfData() const { return m_ndatasize; }

private:
    objective_function_t m_objective_function;
    gradient_function_t m_gradient_function;
    int m_ncalls;
    int m_ndatasize;
};

#endif // OBJECTIVEFUNCTION_H
