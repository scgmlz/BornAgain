//  ************************************************************************************************
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
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_FITTING_ITERATIONINFO_H
#define BORNAGAIN_CORE_FITTING_ITERATIONINFO_H

#include "Fit/Param/Parameters.h"
#include <map>
#include <string>

//! Stores fit iteration info to track fit flow from various observers.
//! Used in context of FitObjective.

class IterationInfo {
public:
    IterationInfo();

    void update(const mumufit::Parameters& params, double chi2);

    //! Returns current number of minimizer iterations.
    unsigned iterationCount() const;

    double chi2() const;

    mumufit::Parameters parameters() const;

    //! Returns map of fit parameter names and its current values.
    std::map<std::string, double> parameterMap() const;

private:
    double m_chi2;
    mumufit::Parameters m_current_parameters;
    unsigned m_iteration_count;
};

#endif // BORNAGAIN_CORE_FITTING_ITERATIONINFO_H
