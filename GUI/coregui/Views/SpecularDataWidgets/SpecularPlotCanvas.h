// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlotCanvas.h
//! @brief     Defines class ColorMapCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARPLOTCANVAS_H
#define SPECULARPLOTCANVAS_H

#include "SessionItemWidget.h"

class PlotStatusLabel;
class QCustomPlot;
class SpecularPlot;

//! The SpecularPlotCanvas class contains SpecularPlot for specular data presentation, and provides
//! status string appearance.

class BA_CORE_API_ SpecularPlotCanvas : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit SpecularPlotCanvas(QWidget* parent = nullptr);

    void setItem(SessionItem* specularDataItem) override;

    SpecularPlot* specularPlot();
    QCustomPlot* customPlot();

    void setStatusLabelEnabled(bool flag);

public slots:
    void onStatusString(const QString& name);

private:
    SpecularPlot* m_plot;
    PlotStatusLabel* m_statusLabel;
};

#endif // SPECULARPLOTCANVAS_H
