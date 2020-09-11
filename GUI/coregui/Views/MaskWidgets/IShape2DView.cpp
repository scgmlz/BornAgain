// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/IShape2DView.cpp
//! @brief     Implements class IShape2DView.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/MaskWidgets/ISceneAdaptor.h"
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

IShape2DView::IShape2DView()
    : m_item(nullptr), m_adaptor(nullptr), m_block_on_property_change(false)
{
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}

IShape2DView::~IShape2DView()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

QRectF IShape2DView::boundingRect() const
{
    return m_bounding_rect;
}

void IShape2DView::setParameterizedItem(SessionItem* item)
{
    if (m_item == item) {
        return;

    } else {
        if (m_item)
            m_item->mapper()->unsubscribe(this);

        m_item = item;
        if (!m_item)
            return;

        m_item->mapper()->setOnPropertyChange(
            [this](const QString& name) { onItemPropertyChange(name); }, this);

        m_item->mapper()->setOnItemDestroy([this](SessionItem*) { m_item = 0; }, this);
    }
}

SessionItem* IShape2DView::parameterizedItem()
{
    return m_item;
}

void IShape2DView::setSceneAdaptor(const ISceneAdaptor* adaptor)
{
    ASSERT(adaptor);

    if (m_adaptor != adaptor) {
        if (m_adaptor)
            disconnect(m_adaptor, SIGNAL(update_request()), this, SLOT(update_view()));

        m_adaptor = adaptor;
        connect(m_adaptor, SIGNAL(update_request()), this, SLOT(update_view()),
                Qt::UniqueConnection);
        update_view();
    }
}

double IShape2DView::par(const QString& property_name) const
{
    return m_item->getItemValue(property_name).toReal();
}

qreal IShape2DView::toSceneX(const QString& property_name) const
{
    return toSceneX(m_item->getItemValue(property_name).toReal());
}

qreal IShape2DView::toSceneX(qreal value) const
{
    return m_adaptor ? m_adaptor->toSceneX(value) : value;
}

qreal IShape2DView::toSceneY(const QString& property_name) const
{
    return toSceneY(m_item->getItemValue(property_name).toReal());
}

qreal IShape2DView::toSceneY(qreal value) const
{
    return m_adaptor ? m_adaptor->toSceneY(value) : value;
}

qreal IShape2DView::fromSceneX(qreal value) const
{
    return m_adaptor ? m_adaptor->fromSceneX(value) : value;
}

qreal IShape2DView::fromSceneY(qreal value) const
{
    return m_adaptor ? m_adaptor->fromSceneY(value) : value;
}

void IShape2DView::addView(IShape2DView* childView, int /* row */)
{
    if (!childItems().contains(childView))
        childView->setParentItem(this);
}

void IShape2DView::setBlockOnProperty(bool value)
{
    m_block_on_property_change = value;
}

bool IShape2DView::blockOnProperty() const
{
    return m_block_on_property_change;
}

void IShape2DView::onItemPropertyChange(const QString& propertyName)
{
    if (m_block_on_property_change)
        return;

    m_block_on_property_change = true;

    bool schedule_update = false;
    if (propertyName == MaskItem::P_MASK_VALUE) {
        schedule_update = true;
    } else if (propertyName == MaskItem::P_IS_VISIBLE) {
        this->setVisible(parameterizedItem()->getItemValue(MaskItem::P_IS_VISIBLE).toBool());
        schedule_update = true;
    }

    onPropertyChange(propertyName);

    if (schedule_update)
        update();

    m_block_on_property_change = false;
}
