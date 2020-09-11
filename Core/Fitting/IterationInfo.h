// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IterationInfo.h
//! @brief     Defines class IterationInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_FITTING_ITERATIONINFO_H
#define BORNAGAIN_CORE_FITTING_ITERATIONINFO_H

#include "Fit/Kernel/Parameters.h"
#include "Wrap/WinDllMacros.h"
#include <map>
#include <string>

//! Stores fit iteration info to track fit flow from various observers.
//! Used in context of FitObjective.

class BA_CORE_API_ IterationInfo
{
public:
    IterationInfo();

    void update(const Fit::Parameters& params, double chi2);

    //! Returns current number of minimizer iterations.
    unsigned iterationCount() const;

    double chi2() const;

    Fit::Parameters parameters() const;

    //! Returns map of fit parameter names and its current values.
    std::map<std::string, double> parameterMap() const;

private:
    double m_chi2;
    Fit::Parameters m_current_parameters;
    unsigned m_iteration_count;
};

#endif // BORNAGAIN_CORE_FITTING_ITERATIONINFO_H
