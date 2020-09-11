// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvas.h
//! @brief     Defines class ColorMapCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAPCANVAS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAPCANVAS_H

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"

class ColorMap;
class FontScalingEvent;
class IntensityDataItem;
class PlotStatusLabel;
class QCustomPlot;

//! The ColorMapCanvas class contains ColorMap for intensity data presentation, and provide
//! control of font size, status string appearance, defines common actions
//! (reset view, save plot, show context menu).

class BA_CORE_API_ ColorMapCanvas : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit ColorMapCanvas(QWidget* parent = nullptr);

    void setItem(SessionItem* intensityDataItem);

    ColorMap* colorMap();
    QCustomPlot* customPlot();

    void setStatusLabelEnabled(bool flag);

public slots:
    void onStatusString(const QString& name);

private:
    ColorMap* m_colorMap;
    FontScalingEvent* m_canvasEvent;
    PlotStatusLabel* m_statusLabel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_COLORMAPCANVAS_H
