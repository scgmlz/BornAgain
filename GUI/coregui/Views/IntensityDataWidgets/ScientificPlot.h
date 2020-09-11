// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h
//! @brief     Declares class ScientificPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_SCIENTIFICPLOT_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_SCIENTIFICPLOT_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include <memory>

class PlotEventInfo;
class QCustomPlot;
class ScientificPlotEvent;

//! Common interface for plot-descriptor interaction

class BA_CORE_API_ ScientificPlot : public SessionItemWidget
{
    Q_OBJECT

public:
    enum class PLOT_TYPE { Plot1D, Plot2D };

    explicit ScientificPlot(QWidget* parent, PLOT_TYPE plot_type);
    ~ScientificPlot() override;

    //! Returns plot descriptor corresponding to given axes coordinates.
    virtual PlotEventInfo eventInfo(double xpos, double ypos) const = 0;

    virtual QCustomPlot* customPlot() = 0;
    virtual const QCustomPlot* customPlot() const = 0;

    ScientificPlotEvent* plotEvent() { return m_event; }

    //! transform axes coordinates to CustomPlot widget coordinates
    double xAxisCoordToPixel(double axis_coordinate) const;
    double yAxisCoordToPixel(double axis_coordinate) const;

    //! transform widget coordinates to axes coordinates
    double pixelToXaxisCoord(double pixel) const;
    double pixelToYaxisCoord(double pixel) const;

    //! Tracks move events (used when showing profile histograms and printing status string)
    void setMouseTrackingEnabled(bool enable);

    //! Returns true if axes rectangle contains given in axes coordinates.
    bool axesRangeContains(double xpos, double ypos) const;

    //! Returns the type of current plot
    PLOT_TYPE plotType() const { return m_plot_type; }

signals:
    void statusString(const QString& text);

private:
    PLOT_TYPE m_plot_type;
    ScientificPlotEvent* m_event;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_SCIENTIFICPLOT_H
