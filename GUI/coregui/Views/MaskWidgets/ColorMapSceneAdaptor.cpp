// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.cpp
//! @brief     Implements class ColorMapSceneAdaptor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"

ColorMapSceneAdaptor::ColorMapSceneAdaptor() : m_plot(0) {}

qreal ColorMapSceneAdaptor::toSceneX(qreal mask_x) const
{
    return m_plot ? m_plot->xAxisCoordToPixel(mask_x) : mask_x;
}

qreal ColorMapSceneAdaptor::toSceneY(qreal mask_y) const
{
    return m_plot ? m_plot->yAxisCoordToPixel(mask_y) : mask_y;
}

qreal ColorMapSceneAdaptor::fromSceneX(qreal scene_x) const
{
    return m_plot ? m_plot->pixelToXaxisCoord(scene_x) : scene_x;
}

qreal ColorMapSceneAdaptor::fromSceneY(qreal scene_y) const
{
    return m_plot ? m_plot->pixelToYaxisCoord(scene_y) : scene_y;
}

void ColorMapSceneAdaptor::setColorMapPlot(ColorMap* plot)
{
    m_plot = plot;
    if (m_plot)
        m_plot->installEventFilter(this);
}

bool ColorMapSceneAdaptor::eventFilter(QObject* object, QEvent* event)
{
    Q_UNUSED(object);
    if (event->type() == QEvent::Resize || event->type() == QEvent::UpdateRequest) {
        m_viewport_rectangle = m_plot->viewportRectangleInWidgetCoordinates();
        emit update_request();
        return false;
    }
    return true;
}

const QRectF& ColorMapSceneAdaptor::viewportRectangle() const
{
    return m_viewport_rectangle;
}
