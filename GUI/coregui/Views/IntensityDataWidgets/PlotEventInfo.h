// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PlotEventInfo.h
//! @brief     Defines the class PlotEventInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PLOTEVENTINFO_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PLOTEVENTINFO_H

#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h"
#include "Wrap/WinDllMacros.h"
#include <QString>

class ColorMap;
class SpecularPlot;

//! Contains parameters of mouse position in 1D or 2D plot.

class BA_CORE_API_ PlotEventInfo
{
    using PLOT_TYPE = ScientificPlot::PLOT_TYPE;

public:
    PlotEventInfo(PLOT_TYPE type);

    QString statusString() const;

    // setters, getters
    void setInAxesRange(bool flag) { m_in_axes_range = flag; }
    bool inAxesRange() const { return m_in_axes_range; }

    void setLogValueAxis(bool flag) { m_log_valued_axis = flag; }
    bool isLogValueAxis() const { return m_log_valued_axis; }

    void setX(double x) { m_x = x; }
    double x() const { return m_x; }
    void setY(double y) { m_y = y; }
    double y() const { return m_y; }

    void setValue(double value) { m_value = value; }
    double value() const { return m_value; }

    void setNx(int nx) { m_nx = nx; }
    int nx() const { return m_nx; }
    void setNy(int ny) { m_ny = ny; }
    int ny() const { return m_ny; }

private:
    QString valueToString() const;

    bool m_in_axes_range, m_log_valued_axis;
    double m_x, m_y, m_value;
    int m_nx, m_ny;
    PLOT_TYPE m_info_type;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PLOTEVENTINFO_H
