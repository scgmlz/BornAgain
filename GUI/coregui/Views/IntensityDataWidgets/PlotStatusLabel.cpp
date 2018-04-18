// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PlotStatusLabel.cpp
//! @brief     Implements class PlotStatusLabel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PlotStatusLabel.h"
#include "DescriptedPlot.h"

PlotStatusLabel::PlotStatusLabel(DescriptedPlot* plot, QWidget* parent) : StatusLabel(parent)
{
    if (plot)
        addPlot(plot);
}

void PlotStatusLabel::addPlot(DescriptedPlot* plot)
{
    if (m_plots.contains(plot))
        return;

    m_plots.push_back(plot);
    setPlotLabelEnabled(plot, true);
}

//! Enables/disables label. If disabled, all colorMaps are disconnected and label is hiding.

void PlotStatusLabel::setLabelEnabled(bool flag)
{
    for (auto colorMap : m_plots)
        setPlotLabelEnabled(colorMap, flag);

    setEnabled(flag);
}

//! Disconnects all color maps from the label.

void PlotStatusLabel::reset()
{
    for (auto colorMap : m_plots)
        setPlotLabelEnabled(colorMap, false);

    m_plots.clear();
}

void PlotStatusLabel::onPlotStatusString(const QString& text) { setText(text); }

//! Enables/disables showing of label for given plot.

void PlotStatusLabel::setPlotLabelEnabled(DescriptedPlot* plot, bool flag)
{
    plot->setMouseTrackingEnabled(flag);
    setConnected(plot, flag);
}

//! Connects with colorMap's status string signal.

void PlotStatusLabel::setConnected(DescriptedPlot* plot, bool flag)
{
    if (flag) {
        connect(plot, &DescriptedPlot::statusString, this,
                &PlotStatusLabel::onPlotStatusString, Qt::UniqueConnection);
        connect(plot, &DescriptedPlot::destroyed, this, &PlotStatusLabel::onPlotDestroyed);
    } else {
        disconnect(plot, &DescriptedPlot::statusString, this, &PlotStatusLabel::onPlotStatusString);
    }
}

void PlotStatusLabel::onPlotDestroyed(QObject* obj)
{
    auto it = std::remove_if(m_plots.begin(), m_plots.end(),
                             [obj](DescriptedPlot* cm) { return cm == obj; });
    m_plots.erase(it, m_plots.end());
}
