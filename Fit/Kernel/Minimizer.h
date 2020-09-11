// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/Minimizer.h
//! @brief     Defines class Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_KERNEL_MINIMIZER_H
#define BORNAGAIN_FIT_KERNEL_MINIMIZER_H

#include "Fit/Kernel/KernelTypes.h"
#include "Fit/Kernel/MinimizerResult.h"
#include "Fit/Kernel/Parameters.h"
#include "Wrap/WinDllMacros.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

class PyCallback;
class IMinimizer;

namespace Fit
{

class Kernel;

//! A main class to run fitting.
//! @ingroup fitting

class BA_CORE_API_ Minimizer
{
public:
    Minimizer();
    ~Minimizer();

    void setMinimizer(const std::string& minimizerName, const std::string& algorithmName = "",
                      const std::string& options = "");

    void setMinimizer(IMinimizer* minimizer);

#ifndef SWIG
    MinimizerResult minimize(fcn_scalar_t fcn, const Parameters& parameters);

    MinimizerResult minimize(fcn_residual_t fcn, const Parameters& parameters);
#endif

    //! Finds minimum of user objective function (to be called from Python).
    MinimizerResult minimize(PyCallback& callback, const Parameters& parameters);

private:
    std::unique_ptr<Kernel> m_kernel;
};

} // namespace Fit

#endif // BORNAGAIN_FIT_KERNEL_MINIMIZER_H
