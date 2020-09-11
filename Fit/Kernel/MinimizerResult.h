// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerResult.h
//! @brief     Defines class MinimizerResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_KERNEL_MINIMIZERRESULT_H
#define BORNAGAIN_FIT_KERNEL_MINIMIZERRESULT_H

#include "Fit/Kernel/Parameters.h"
#include "Wrap/WinDllMacros.h"
#include <string>

namespace Fit
{

//! Result of minimization round.

class BA_CORE_API_ MinimizerResult
{
public:
    MinimizerResult();

    void setParameters(const Parameters& parameters);
    Parameters parameters() const;

    void setMinValue(double value);
    double minValue() const;

    std::string toString() const;

    void setReport(const std::string& value);

    void setDuration(double value);

    void setNumberOfCalls(int value);

    void setNumberOfGradientCalls(int value);

private:
    double m_min_value;             //!< Found minimum of objective function.
    int m_number_of_calls;          //!< Number of objective function calls.
    int m_number_of_gradient_calls; //!< Number of calls to calculate gradients
    double m_duration;              //!< Duration of minimization in sec.msec
    std::string m_minimizer_report;
    Parameters m_parameters;
};

} // namespace Fit

#endif // BORNAGAIN_FIT_KERNEL_MINIMIZERRESULT_H
