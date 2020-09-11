// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PlotStatusLabel.h
//! @brief     Defines class PlotStatusLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PLOTSTATUSLABEL_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PLOTSTATUSLABEL_H

#include "GUI/coregui/Views/CommonWidgets/StatusLabel.h"
#include <QList>

class ScientificPlot;
class QResizeEvent;

//! The PlotStatusLabel class shows status string as reported by DescriptedPlot in a frame.
//! Can work with more than one DescriptedPlot. Provides automatic adjustment of font size,
//! depending on available space in parent layout. Also doesn't trigger layout resize,
//! being happy with place it has.

class BA_CORE_API_ PlotStatusLabel : public StatusLabel
{
    Q_OBJECT
public:
    PlotStatusLabel(ScientificPlot* plot, QWidget* parent = nullptr);

    void addPlot(ScientificPlot* plot);

    void setLabelEnabled(bool flag);

    void reset();

public slots:
    void onPlotStatusString(const QString& text);

private slots:
    void onPlotDestroyed(QObject* obj);

private:
    void setPlotLabelEnabled(ScientificPlot* plot, bool flag);
    void setConnected(ScientificPlot* plot, bool flag);

    QList<ScientificPlot*> m_plots;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INTENSITYDATAWIDGETS_PLOTSTATUSLABEL_H
