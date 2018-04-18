// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/MouseMoveEvent.cpp
//! @brief     Implements class MouseMoveEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MouseMoveEvent.h"
#include "DescriptedPlot.h"
#include "PlotStatusDescriptors.h"
#include <QMouseEvent>
#include <qcustomplot.h>

MouseMoveEvent::MouseMoveEvent(DescriptedPlot* descriptedPlot)
    : QObject(descriptedPlot), m_plot(descriptedPlot)
{
}

//! Sets tracking of the mouse for parent DescriptedPlot

void MouseMoveEvent::setMouseTrackingEnabled(bool enable)
{
    m_plot->setMouseTracking(enable);
    customPlot()->setMouseTracking(enable);

    if (enable)
        connect(customPlot(), &QCustomPlot::mouseMove,
                this, &MouseMoveEvent::onCustomMouseMove, Qt::UniqueConnection);
    else
        disconnect(customPlot(), &QCustomPlot::mouseMove,
                this, &MouseMoveEvent::onCustomMouseMove);
}

//! Constructs status string on mouse move event coming from QCustomPlot. String is emitted
//! if mouse is in axes's viewport rectangle. Once mouse goes out of it, an
//! empty string is emitted once again.

void MouseMoveEvent::onCustomMouseMove(QMouseEvent* event)
{
    auto currentPos = currentPlotDescriptor(event);

    if (currentPos->inAxesRange()) {
        descriptedPlot()->statusString(currentPos->statusString());

        if (!m_prevPos || !m_prevPos->inAxesRange())
            enteringPlot();

        positionChanged(currentPos->x(), currentPos->y());
    } else if (m_prevPos && m_prevPos->inAxesRange()) {
        descriptedPlot()->statusString(QString());
        leavingPlot();
    }

    m_prevPos = std::move(currentPos);
}

DescriptedPlot* MouseMoveEvent::descriptedPlot()
{
    return m_plot;
}

const DescriptedPlot* MouseMoveEvent::descriptedPlot() const
{
    return m_plot;
}

QCustomPlot* MouseMoveEvent::customPlot()
{
    return m_plot->customPlot();
}

//! Constructs current position of the data.

std::unique_ptr<IPlotDescriptor> MouseMoveEvent::currentPlotDescriptor(QMouseEvent* event) const
{
    double x = descriptedPlot()->pixelToXaxisCoord(event->pos().x());
    double y = descriptedPlot()->pixelToYaxisCoord(event->pos().y());
    return descriptedPlot()->plotDescriptor(x, y);
}
