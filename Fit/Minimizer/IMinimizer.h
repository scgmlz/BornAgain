//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.h
//! @brief     Defines interface IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_FIT_MINIMIZER_IMINIMIZER_H
#define BORNAGAIN_FIT_MINIMIZER_IMINIMIZER_H

#include "Fit/Minimizer/MinimizerResult.h"
#include "Fit/Minimizer/Types.h"
#include <string>

namespace mumufit {
class Parameters;
}

//! Abstract base class for all kind minimizers.
//! @ingroup fitting_internal

class IMinimizer {
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
    virtual mumufit::MinimizerResult minimize_scalar(fcn_scalar_t, mumufit::Parameters);
    virtual mumufit::MinimizerResult minimize_residual(fcn_residual_t, mumufit::Parameters);

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear() {}

    //! Returns minimum function value
    virtual double minValue() const;

    //! Sets option string to the minimizer
    virtual void setOptions(const std::string& options);

#ifndef SWIG
    //! Returns true if minimizer computations are residual-based, false otherwise
    virtual bool requiresResiduals() { return false; }
#endif // USER_API
};

#endif // BORNAGAIN_FIT_MINIMIZER_IMINIMIZER_H
