//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/Kernel.h
//! @brief     Defines class Kernel.
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
#ifndef BORNAGAIN_FIT_KERNEL_KERNEL_H
#define BORNAGAIN_FIT_KERNEL_KERNEL_H

#include "Fit/Minimizer/MinimizerResult.h"
#include "Fit/Minimizer/Types.h"
#include "Fit/Tools/WallclockTimer.h"
#include <functional>
#include <memory>
#include <vector>

class IMinimizer;

namespace mumufit {

//! A main class to run fitting.
//! @ingroup fitting

class Kernel {
public:
    Kernel();
    ~Kernel();

    void setMinimizer(const std::string& minimizerName, const std::string& algorithmName = "",
                      const std::string& options = "");

    void setMinimizer(IMinimizer* minimizer);

    MinimizerResult minimize(fcn_scalar_t fcn, const Parameters& parameters);
    MinimizerResult minimize(fcn_residual_t fcn, const Parameters& parameters);

private:
    void setParameters(const Parameters& parameters);

    Parameters m_parameters;
    std::unique_ptr<IMinimizer> m_minimizer;
    WallclockTimer m_timer;
};

} // namespace mumufit

#endif // BORNAGAIN_FIT_KERNEL_KERNEL_H
#endif // USER_API
