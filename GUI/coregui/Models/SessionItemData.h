// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemData.h
//! @brief     Defines class SessionItemData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMDATA_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMDATA_H

#include <QVariant>
#include <QVector>

//! Handles all data roles for SessionItem.

class SessionItemData
{
public:
    QVector<int> roles() const;

    QVariant data(int role) const;

    bool setData(int role, const QVariant& value);

private:
    class ItemData
    {
    public:
        ItemData(int r = -1, const QVariant& v = {});
        int role;
        QVariant data;
        bool operator==(const ItemData& other) const;
    };

    QVector<ItemData> m_values;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMDATA_H
