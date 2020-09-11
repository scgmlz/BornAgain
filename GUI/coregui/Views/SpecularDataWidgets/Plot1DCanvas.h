// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/Plot1DCanvas.h
//! @brief     Defines class Plot1DCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_PLOT1DCANVAS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_PLOT1DCANVAS_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class FontScalingEvent;
class PlotStatusLabel;
class QCustomPlot;
class Plot1D;

//! The Plot1DCanvas class contains SpecularPlotWithDataView
//! for specular data presentation, and provides
//! status string appearance.

class BA_CORE_API_ Plot1DCanvas : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit Plot1DCanvas(QWidget* parent = nullptr);

    void setItem(SessionItem* dataItemView) override;

    Plot1D* plot1D();
    QCustomPlot* customPlot();

    void setStatusLabelEnabled(bool flag);

public slots:
    void onStatusString(const QString& name);

private:
    Plot1D* m_plot;
    FontScalingEvent* m_canvasEvent;
    PlotStatusLabel* m_statusLabel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SPECULARDATAWIDGETS_PLOT1DCANVAS_H
