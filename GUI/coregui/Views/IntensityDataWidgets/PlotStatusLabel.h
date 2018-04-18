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

#ifndef PLOTSTATUSLABEL_H
#define PLOTSTATUSLABEL_H

#include "StatusLabel.h"
#include <QList>

class DescriptedPlot;
class QResizeEvent;

//! The PlotStatusLabel class shows status string as reported by DescriptedPlot in a frame.
//! Can work with more than one DescriptedPlot. Provides automatic adjustment of font size,
//! depending on available space in parent layout. Also doesn't trigger layout resize,
//! being happy with place it has.

class BA_CORE_API_ PlotStatusLabel : public StatusLabel
{
    Q_OBJECT
public:
    PlotStatusLabel(DescriptedPlot* plot, QWidget* parent = nullptr);

    void addPlot(DescriptedPlot* plot);

    void setLabelEnabled(bool flag);

    void reset();

public slots:
    void onPlotStatusString(const QString& text);

private slots:
    void onPlotDestroyed(QObject* obj);

private:
    void setPlotLabelEnabled(DescriptedPlot* plot, bool flag);
    void setConnected(DescriptedPlot* plot, bool flag);

    QList<DescriptedPlot*> m_plots;
};

#endif // PLOTSTATUSLABEL_H
