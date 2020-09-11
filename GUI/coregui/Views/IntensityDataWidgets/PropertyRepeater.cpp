// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PropertyRepeater.cpp
//! @brief     Implements class PropertyRepeater
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/IntensityDataWidgets/PropertyRepeater.h"
#include "GUI/coregui/Models/IntensityDataItem.h"

PropertyRepeater::PropertyRepeater(QObject* parent, bool repeat_child_properties)
    : QObject(parent), m_block_repeater(false), m_repeat_child_properties(repeat_child_properties)
{
}

PropertyRepeater::~PropertyRepeater()
{
    for (auto item : m_dataItems)
        item->mapper()->unsubscribe(this);
}

void PropertyRepeater::addItem(SessionItem* sessionItem)
{
    if (!sessionItem || m_dataItems.contains(sessionItem))
        return;

    sessionItem->mapper()->setOnItemDestroy(
        [this](SessionItem* item) { m_dataItems.removeAll(item); }, this);

    sessionItem->mapper()->setOnPropertyChange(
        [this](SessionItem* item, const QString& name) { onPropertyChanged(item, name); }, this);

    if (m_repeat_child_properties) {
        sessionItem->mapper()->setOnChildPropertyChange(
            [this](SessionItem* item, const QString& name) {
                setOnChildPropertyChange(item, name);
            },
            this);
    }
    m_dataItems.push_back(sessionItem);
}

void PropertyRepeater::clear()
{
    for (auto item : m_dataItems)
        item->mapper()->unsubscribe(this);

    m_dataItems.clear();
}

void PropertyRepeater::setActive(bool isActive)
{
    m_block_repeater = !isActive;
}

void PropertyRepeater::onPropertyChanged(SessionItem* item, const QString& propertyName)
{
    if (m_block_repeater)
        return;

    m_block_repeater = true;

    QVariant value = item->getItemValue(propertyName);
    for (auto target : targetItems(item)) {
        target->setItemValue(propertyName, value);
    }
    m_block_repeater = false;
}

void PropertyRepeater::setOnChildPropertyChange(SessionItem* item, const QString& propertyName)
{
    if (m_block_repeater)
        return;

    m_block_repeater = true;

    SessionItem* sourceItem = item->parent();
    QString tag = sourceItem->tagFromItem(item);
    QVariant value = item->getItemValue(propertyName);
    for (auto target : targetItems(sourceItem)) {
        target->getItem(tag)->setItemValue(propertyName, value);
    }
    m_block_repeater = false;
}

//! Returns list of target items to update their properties.

QVector<SessionItem*> PropertyRepeater::targetItems(SessionItem* sourceItem)
{
    QVector<SessionItem*> result = m_dataItems;
    result.removeAll(sourceItem);
    return result;
}
