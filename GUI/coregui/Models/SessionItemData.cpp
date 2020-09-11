// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemData.cpp
//! @brief     Implements class SessionItemData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SessionItemData.h"
#include "GUI/coregui/Models/SessionItemUtils.h"

SessionItemData::ItemData::ItemData(int r, const QVariant& v) : role(r), data(v) {}

bool SessionItemData::ItemData::operator==(const SessionItemData::ItemData& other) const
{
    return role == other.role && SessionItemUtils::IsTheSame(data, other.data);
}

QVector<int> SessionItemData::roles() const
{
    QVector<int> result;
    for (const auto& value : m_values)
        result.push_back(value.role);
    return result;
}

QVariant SessionItemData::data(int role) const
{
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
    for (const auto& value : m_values) {
        if (value.role == role)
            return value.data;
    }
    return QVariant();
}

//! Sets the data for given role. Returns true if data was changed.

bool SessionItemData::setData(int role, const QVariant& value)
{
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
    for (auto it = m_values.begin(); it != m_values.end(); ++it) {
        if (it->role == role) {
            if (value.isValid()) {
                if (SessionItemUtils::IsTheSame(it->data, value))
                    return false;
                it->data = value;
            } else {
                m_values.erase(it);
            }
            return true;
        }
    }
    m_values.push_back(ItemData(role, value));
    return true;
}
