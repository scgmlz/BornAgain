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

#ifndef MINIMIZER_H
#define MINIMIZER_H

#include "KernelTypes.h"
#include "MinimizerResult.h"
#include "Parameters.h"
#include "WinDllMacros.h"
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

#endif // MINIMIZER_H
