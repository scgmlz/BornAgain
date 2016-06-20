// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/IView.cpp
//! @brief     Implements class IView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IView.h"
#include "SessionGraphicsItem.h"
#include "ModelMapper.h"
#include <QString>
#include <QDebug>

IView::IView(QGraphicsItem *parent) : QGraphicsObject(parent), m_item(0)
{
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}

IView::~IView()
{
    if(m_item)
        m_item->mapper()->unsubscribe(this);
}

void IView::setParameterizedItem(SessionItem *item)
{
    Q_ASSERT(item);
    Q_ASSERT(m_item == nullptr);

    m_item = item;
    setX(m_item->getItemValue(SessionGraphicsItem::P_XPOS).toReal());
    setY(m_item->getItemValue(SessionGraphicsItem::P_YPOS).toReal());

    m_item->mapper()->setOnPropertyChange(
                [this] (const QString &name)
    {
        onPropertyChange(name);
    }, this);

    m_item->mapper()->setOnSiblingsChange(
                [this]()
    {
         onSiblingsChange();
    }, this);

    m_item->mapper()->setOnItemDestroy(
                [this](SessionItem *) {
        m_item = 0;
    }, this);


    update_appearance();
}

void IView::addView(IView *, int )
{
}

void IView::onChangedX()
{
    Q_ASSERT(m_item);
    m_item->setItemValue(SessionGraphicsItem::P_XPOS, x());
}

void IView::onChangedY()
{
    Q_ASSERT(m_item);
    m_item->setItemValue(SessionGraphicsItem::P_YPOS, y());
}

//! updates visual appearance of the item (color, icons, size etc)
void IView::update_appearance()
{
    update();
}

void IView::onPropertyChange(const QString &propertyName)
{
    Q_ASSERT(m_item);
    if (propertyName == SessionGraphicsItem::P_XPOS) {
        setX(m_item->getItemValue(SessionGraphicsItem::P_XPOS).toReal());
    } else if (propertyName == SessionGraphicsItem::P_YPOS) {
        setY(m_item->getItemValue(SessionGraphicsItem::P_YPOS).toReal());
    }
}

void IView::onSiblingsChange()
{
    update_appearance();
}
