// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfo.cpp
//! @brief     Defines class GroupInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/GroupInfo.h"
#include "GUI/coregui/utils/GUIHelpers.h"

GroupInfo::GroupInfo(const QString& groupType, bool is_sorted)
    : m_groupType(groupType), is_sorted(is_sorted)
{
}

void GroupInfo::add(const QString& itemType, const QString& itemLabel)
{
    if (groupType().isEmpty())
        throw GUIHelpers::Error("GroupInfo::add() -> Error. Empty group name");

    if (containsType(itemType))
        throw GUIHelpers::Error("GroupInfo::add() -> Error. "
                                "Model type '"
                                + itemType + "' already exists.");

    m_info.push_back({itemType, itemLabel});

    if (is_sorted)
        std::sort(m_info.begin(), m_info.end(),
                  [](TypeAndLabel a, TypeAndLabel b) { return a.m_itemType < b.m_itemType; });
}

QString GroupInfo::defaultType() const
{
    if (m_defaultItemType == "" && m_info.size() != 0)
        return m_info[0].m_itemType;
    return m_defaultItemType;
}

void GroupInfo::setDefaultType(const QString& modelType)
{
    if (!containsType(modelType))
        throw GUIHelpers::Error("GroupInfo::add() -> Error. No such type '" + modelType + "'");

    m_defaultItemType = modelType;
}

QString GroupInfo::groupType() const
{
    return m_groupType;
}

QStringList GroupInfo::itemTypes() const
{
    QStringList result;
    for (auto& pair : m_info)
        result.append(pair.m_itemType);

    return result;
}

QStringList GroupInfo::itemLabels() const
{
    QStringList result;
    for (auto& pair : m_info)
        result.append(pair.m_itemLabel);

    return result;
}

bool GroupInfo::isValid()
{
    return !m_groupType.isEmpty();
}

bool GroupInfo::containsType(const QString& itemType) const
{
    for (auto& pair : m_info)
        if (itemType == pair.m_itemType)
            return true;

    return false;
}
