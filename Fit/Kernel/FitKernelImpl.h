// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/FitKernelImpl.h
//! @brief     Defines class FitKernelImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITKERNELIMPL_H
#define FITKERNELIMPL_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include "FitParameterSet.h"
#include "ObjectiveFunction.h"
#include "TimeInterval.h"
#include <memory>

class IMinimizer;
class FitParameter;

//! The implementation of class FitKernel.
//! @ingroup fitting_internal

class BA_CORE_API_ FitKernelImpl
{
public:
    FitKernelImpl();
    ~FitKernelImpl();

    void clear();

    //! Sets minimizer
    void setMinimizer(IMinimizer* minimizer);

    //! Adds fit parameter
    void addFitParameter(FitParameter* par);

    void setObjectiveFunction(objective_function_t func);

    void setGradientFunction(gradient_function_t func, int ndatasize);

    void minimize();

    //! Reports results of minimization in the form of multi-line string.
    std::string reportResults() const;

    FitParameterSet* fitParameters();

    IMinimizer* minimizer();

    //! Number of objective function calls.
    int functionCalls() const;

private:
    FitParameterSet m_fit_parameters;
    std::unique_ptr<IMinimizer> m_minimizer;
    ObjectiveFunction m_objective_function;
    TimeInterval m_time_interval;
};

#endif // FITKERNELIMPL_H
