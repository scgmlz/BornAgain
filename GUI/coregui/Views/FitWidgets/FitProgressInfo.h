// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitProgressInfo.h
//! @brief     Defines class FitProgressInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITPROGRESSINFO_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITPROGRESSINFO_H

#include "Wrap/WinDllMacros.h"
#include <string>
#include <vector>

//! The FitProgressInfo class contains all essential information about fit progress.
//! It is send from GUIFitObserver to FitSuiteWidget on every nth iteration.

class BA_CORE_API_ FitProgressInfo
{
public:
    FitProgressInfo();

    double chi2() const { return m_chi2; }
    int iterationCount() const { return m_iteration_count; }
    std::vector<double> parValues() const { return m_values; }
    std::string logInfo() const { return m_log_info; }
    std::vector<double> simValues() const { return m_sim_values; }

    friend class GUIFitObserver;

private:
    double m_chi2;
    int m_iteration_count;
    std::vector<double> m_values;
    std::string m_log_info;
    std::vector<double> m_sim_values;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_FITWIDGETS_FITPROGRESSINFO_H
