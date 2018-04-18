#include "DescriptedPlot.h"
#include "MouseMoveEvent.h"
#include <qcustomplot.h>

DescriptedPlot::DescriptedPlot(QWidget* parent)
    : SessionItemWidget(parent)
    , m_mouse_move_event(new MouseMoveEvent(this))
{
}

DescriptedPlot::~DescriptedPlot() = default;

double DescriptedPlot::xAxisCoordToPixel(double axis_coordinate) const
{
    return customPlot()->xAxis->coordToPixel(axis_coordinate);
}

double DescriptedPlot::yAxisCoordToPixel(double axis_coordinate) const
{
    return customPlot()->yAxis->coordToPixel(axis_coordinate);
}

double DescriptedPlot::pixelToXaxisCoord(double pixel) const
{
    return customPlot()->xAxis->pixelToCoord(pixel);
}

double DescriptedPlot::pixelToYaxisCoord(double pixel) const
{
    return customPlot()->yAxis->pixelToCoord(pixel);
}

void DescriptedPlot::setMouseTrackingEnabled(bool enable)
{
    m_mouse_move_event->setMouseTrackingEnabled(enable);
}

bool DescriptedPlot::axesRangeContains(double xpos, double ypos) const
{
    return customPlot()->xAxis->range().contains(xpos)
           && customPlot()->yAxis->range().contains(ypos);
}
