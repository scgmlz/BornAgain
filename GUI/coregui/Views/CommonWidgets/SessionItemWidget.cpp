// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/SessionItemWidget.cpp
//! @brief     Declares class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/SessionItemWidget.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/CommonWidgets/SessionItemController.h"

SessionItemWidget::SessionItemWidget(QWidget* parent)
    : QWidget(parent), m_itemController(new SessionItemController(this))
{
    m_itemController->setSubscribeCallback([this]() { subscribeToItem(); });
    m_itemController->setUnsubscribeCallback([this]() { unsubscribeFromItem(); });
}

SessionItemWidget::~SessionItemWidget() = default;

void SessionItemWidget::setItem(SessionItem* item)
{
    m_itemController->setItem(item);

    if (isVisible())
        m_itemController->subscribe();
}

QList<QAction*> SessionItemWidget::actionList()
{
    return QList<QAction*>();
}

SessionItem* SessionItemWidget::currentItem()
{
    return const_cast<SessionItem*>(static_cast<const SessionItemWidget*>(this)->currentItem());
}

const SessionItem* SessionItemWidget::currentItem() const
{
    return m_itemController->currentItem();
}

void SessionItemWidget::showEvent(QShowEvent*)
{
    m_itemController->subscribe();
}

void SessionItemWidget::hideEvent(QHideEvent*)
{
    m_itemController->unsubscribe();
}
