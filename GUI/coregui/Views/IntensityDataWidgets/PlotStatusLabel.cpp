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

#include "GUI/coregui/Views/IntensityDataWidgets/PlotStatusLabel.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h"

PlotStatusLabel::PlotStatusLabel(ScientificPlot* plot, QWidget* parent) : StatusLabel(parent)
{
    if (plot)
        addPlot(plot);
}

void PlotStatusLabel::addPlot(ScientificPlot* plot)
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

void PlotStatusLabel::onPlotStatusString(const QString& text)
{
    setText(text);
}

//! Enables/disables showing of label for given plot.

void PlotStatusLabel::setPlotLabelEnabled(ScientificPlot* plot, bool flag)
{
    plot->setMouseTrackingEnabled(flag);
    setConnected(plot, flag);
}

//! Connects with colorMap's status string signal.

void PlotStatusLabel::setConnected(ScientificPlot* plot, bool flag)
{
    if (flag) {
        connect(plot, &ScientificPlot::statusString, this, &PlotStatusLabel::onPlotStatusString,
                Qt::UniqueConnection);
        connect(plot, &ScientificPlot::destroyed, this, &PlotStatusLabel::onPlotDestroyed);
    } else {
        disconnect(plot, &ScientificPlot::statusString, this, &PlotStatusLabel::onPlotStatusString);
    }
}

void PlotStatusLabel::onPlotDestroyed(QObject* obj)
{
    auto it = std::remove_if(m_plots.begin(), m_plots.end(),
                             [obj](ScientificPlot* cm) { return cm == obj; });
    m_plots.erase(it, m_plots.end());
}
