// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskAllView.cpp
//! @brief     Implements MaskAllView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskAllView.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorHelper.h"
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

MaskAllView::MaskAllView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void MaskAllView::update_view()
{
    //    prepareGeometryChange();
    m_bounding_rect = m_adaptor->viewportRectangle();
    update();
}

void MaskAllView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    //    painter->setRenderHints(QPainter::Antialiasing);
    QColor color(250, 250, 240, 150);
    painter->setBrush(color);
    painter->drawRect(m_bounding_rect);

    if (isSelected()) {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(m_bounding_rect);
    }
}
