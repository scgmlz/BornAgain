// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupItemController.h
//! @brief     Defines class GroupItemController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_GROUPITEMCONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_MODELS_GROUPITEMCONTROLLER_H

#include "GUI/coregui/Models/GroupInfo.h"
#include <QStringList>
#include <QVariant>

class SessionItem;

//! Provides logic for manipulating items belonging to GroupItem parent.

class BA_CORE_API_ GroupItemController
{
public:
    GroupItemController(SessionItem* groupItem, GroupInfo groupInfo);

    SessionItem* currentItem();

    QString currentType() const;
    void setCurrentType(const QString& type);

    SessionItem* getItemOfType(const QString& type);

    int currentIndex() const;
    void setCurrentIndex(int index);

    QVariant createCombo() const;

private:
    QStringList itemTypes() const;
    QStringList itemLabels() const;
    SessionItem* addItem(const QString& item_type);
    SessionItem* createCorrespondingItem();
    int toIndex(const QString& type) const;
    QString toString(int currentIndex) const;

    SessionItem* m_groupItem;
    QString m_current_type;
    GroupInfo m_groupInfo;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_GROUPITEMCONTROLLER_H
