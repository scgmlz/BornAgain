// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskGraphicsProxy.cpp
//! @brief     Implements class MaskGraphicsProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskGraphicsProxy.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include "GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.h"
#include <QGraphicsSceneMouseEvent>

MaskGraphicsProxy::MaskGraphicsProxy()
    : m_colorMap(new ColorMap), m_sceneAdaptor(0), m_send_signals_to_colormap(false)
{
    resize(1200, 1000);
    setInZoomMode(true);
}

MaskGraphicsProxy::~MaskGraphicsProxy()
{
    // no need to delete m_colorMap, base QGraphicsProxyWidget will take care about it
    if (m_sceneAdaptor)
        m_sceneAdaptor->setColorMapPlot(0);
}

void MaskGraphicsProxy::setIntensityItem(IntensityDataItem* intensityDataItem)
{
    m_colorMap->setItem(intensityDataItem);
    if (widget() != m_colorMap)
        setWidget(m_colorMap);
}

void MaskGraphicsProxy::setSceneAdaptor(ISceneAdaptor* sceneAdaptor)
{
    if (m_sceneAdaptor)
        m_sceneAdaptor->setColorMapPlot(0);

    m_sceneAdaptor = dynamic_cast<ColorMapSceneAdaptor*>(sceneAdaptor);

    if (m_sceneAdaptor)
        m_sceneAdaptor->setColorMapPlot(m_colorMap);
}

//! Sets widget to zoom mode, when signals (zoom wheel, mouse clicks) are send down to
//! ColorMap plot. In non-zoom mode, widget doesn't react on clicks.
void MaskGraphicsProxy::setInZoomMode(bool value)
{
    m_send_signals_to_colormap = value;
    if (value) {
        setAcceptedMouseButtons(Qt::LeftButton);
    } else {
        setAcceptedMouseButtons(Qt::NoButton);
    }
}

ColorMap* MaskGraphicsProxy::colorMap()
{
    return m_colorMap;
}

void MaskGraphicsProxy::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!m_send_signals_to_colormap)
        return;
    QGraphicsProxyWidget::mousePressEvent(event);
    event->accept();
}

void MaskGraphicsProxy::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (!m_send_signals_to_colormap)
        return;
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}

void MaskGraphicsProxy::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    if (!m_send_signals_to_colormap)
        return;
    QGraphicsProxyWidget::wheelEvent(event);
}

void MaskGraphicsProxy::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (!m_send_signals_to_colormap)
        return;
    QGraphicsProxyWidget::mouseMoveEvent(event);
}
