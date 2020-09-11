// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.h
//! @brief     Defines class IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_MINIMIZER_IMINIMIZER_H
#define BORNAGAIN_FIT_MINIMIZER_IMINIMIZER_H

#include "Fit/Kernel/KernelTypes.h"
#include "Fit/Kernel/MinimizerResult.h"
#include "Wrap/WinDllMacros.h"
#include <string>

namespace Fit
{
class Parameters;
}

//! Pure virtual interface for all kind minimizers.
//! @ingroup fitting_internal

class BA_CORE_API_ IMinimizer
{
public:
    IMinimizer();
    virtual ~IMinimizer();

    IMinimizer(const IMinimizer& other) = delete;
    IMinimizer& operator=(const IMinimizer& other) = delete;

    //! return name of the minimizer
    virtual std::string minimizerName() const = 0;

    //! return name of the minimization algorithm
    virtual std::string algorithmName() const = 0;

    //! run minimization
    virtual Fit::MinimizerResult minimize_scalar(fcn_scalar_t, Fit::Parameters);
    virtual Fit::MinimizerResult minimize_residual(fcn_residual_t, Fit::Parameters);

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear() {}

    //! Returns minimum function value
    virtual double minValue() const;

    //! Sets option string to the minimizer
    virtual void setOptions(const std::string& options);

#ifndef SWIG
    //! Returns true if minimizer computations are residual-based, false otherwise
    virtual bool requiresResiduals() { return false; }
#endif // SWIG
};

#endif // BORNAGAIN_FIT_MINIMIZER_IMINIMIZER_H
