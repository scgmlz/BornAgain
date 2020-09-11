// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ScientificPlotEvent.cpp
//! @brief     Implements class ScientificPlotEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/ScientificPlotEvent.h"
#include <QMouseEvent>
#include <qcustomplot.h>

ScientificPlotEvent::ScientificPlotEvent(ScientificPlot* scientific_plot)
    : QObject(scientific_plot), m_plot(scientific_plot), m_prevPos(scientific_plot->plotType())
{
}

ScientificPlotEvent::~ScientificPlotEvent() = default;

//! Sets tracking of the mouse for parent DescriptedPlot

void ScientificPlotEvent::setMouseTrackingEnabled(bool enable)
{
    m_plot->setMouseTracking(enable);
    customPlot()->setMouseTracking(enable);

    if (enable)
        connect(customPlot(), &QCustomPlot::mouseMove, this,
                &ScientificPlotEvent::onCustomMouseMove, Qt::UniqueConnection);
    else
        disconnect(customPlot(), &QCustomPlot::mouseMove, this,
                   &ScientificPlotEvent::onCustomMouseMove);
}

//! Constructs status string on mouse move event coming from QCustomPlot. String is emitted
//! if mouse is in axes's viewport rectangle. Once mouse goes out of it, an
//! empty string is emitted once again.

void ScientificPlotEvent::onCustomMouseMove(QMouseEvent* event)
{
    auto currentPos = currentPlotDescriptor(event);

    if (currentPos.inAxesRange()) {
        scientificPlot()->statusString(currentPos.statusString());

        if (!m_prevPos.inAxesRange())
            enteringPlot();

        positionChanged(currentPos.x(), currentPos.y());
    } else if (m_prevPos.inAxesRange()) {
        scientificPlot()->statusString(QString());
        leavingPlot();
    }

    m_prevPos = std::move(currentPos);
}

ScientificPlot* ScientificPlotEvent::scientificPlot()
{
    return m_plot;
}

const ScientificPlot* ScientificPlotEvent::scientificPlot() const
{
    return m_plot;
}

QCustomPlot* ScientificPlotEvent::customPlot()
{
    return m_plot->customPlot();
}

//! Constructs current position of the data.

PlotEventInfo ScientificPlotEvent::currentPlotDescriptor(QMouseEvent* event) const
{
    double x = scientificPlot()->pixelToXaxisCoord(event->pos().x());
    double y = scientificPlot()->pixelToYaxisCoord(event->pos().y());
    return scientificPlot()->eventInfo(x, y);
}
