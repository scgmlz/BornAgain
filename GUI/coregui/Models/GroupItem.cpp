// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupItem.cpp
//! @brief     Implements class GroupItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/GroupItemController.h"
#include "GUI/coregui/utils/GUIHelpers.h"

const QString GroupItem::T_ITEMS = "Item tag";

GroupItem::GroupItem() : SessionItem("GroupProperty")
{
    registerTag(T_ITEMS);
    setDefaultTag(T_ITEMS);

    mapper()->setOnValueChange([this]() { onValueChange(); });
}

GroupItem::~GroupItem() = default;

void GroupItem::setGroupInfo(const GroupInfo& groupInfo)
{
    if (m_controller)
        throw GUIHelpers::Error("GroupItem::setGroup() -> Error. Attempt to set group twice.");

    m_controller = std::make_unique<GroupItemController>(this, groupInfo);
    updateComboValue();
}

SessionItem* GroupItem::currentItem() const
{
    return m_controller ? m_controller->currentItem() : nullptr;
}

QString GroupItem::currentType() const
{
    return m_controller->currentType();
}

SessionItem* GroupItem::setCurrentType(const QString& modelType)
{
    m_controller->setCurrentType(modelType);
    updateComboValue();
    return currentItem();
}

QStringList GroupItem::translateList(const QStringList& list) const
{
    // we do not add here the name of itself
    return list;
}

SessionItem* GroupItem::getItemOfType(const QString& type)
{
    return m_controller->getItemOfType(type);
}

void GroupItem::onValueChange()
{
    if (!value().canConvert<ComboProperty>())
        throw GUIHelpers::Error("GroupItem::onValueChange() -> Error. Wrong property type");

    ComboProperty property = value().value<ComboProperty>();
    if (property.currentIndex() != m_controller->currentIndex()) {
        m_controller->setCurrentIndex(property.currentIndex());
        // because of the delay between ComboProperty change and the change in GroupItem here,
        // we have to emit signals once again to inform other views (i.e. views other than the view
        // were property was changed)
        emitDataChanged(Qt::DisplayRole | Qt::EditRole);
    }
}

void GroupItem::updateComboValue()
{
    setValue(m_controller->createCombo());
}
