// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.cpp
//! @brief     Implements class ScientificPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlotEvent.h"
#include <qcustomplot.h>

ScientificPlot::ScientificPlot(QWidget* parent, PLOT_TYPE plot_type)
    : SessionItemWidget(parent), m_plot_type(plot_type), m_event(new ScientificPlotEvent(this))
{
}

ScientificPlot::~ScientificPlot() = default;

double ScientificPlot::xAxisCoordToPixel(double axis_coordinate) const
{
    return customPlot()->xAxis->coordToPixel(axis_coordinate);
}

double ScientificPlot::yAxisCoordToPixel(double axis_coordinate) const
{
    return customPlot()->yAxis->coordToPixel(axis_coordinate);
}

double ScientificPlot::pixelToXaxisCoord(double pixel) const
{
    return customPlot()->xAxis->pixelToCoord(pixel);
}

double ScientificPlot::pixelToYaxisCoord(double pixel) const
{
    return customPlot()->yAxis->pixelToCoord(pixel);
}

void ScientificPlot::setMouseTrackingEnabled(bool enable)
{
    m_event->setMouseTrackingEnabled(enable);
}

bool ScientificPlot::axesRangeContains(double xpos, double ypos) const
{
    return customPlot()->xAxis->range().contains(xpos)
           && customPlot()->yAxis->range().contains(ypos);
}
