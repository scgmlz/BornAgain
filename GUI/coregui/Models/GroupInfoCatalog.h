// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfoCatalog.h
//! @brief     Defines class GroupInfoCatalog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_GROUPINFOCATALOG_H
#define BORNAGAIN_GUI_COREGUI_MODELS_GROUPINFOCATALOG_H

#include "GUI/coregui/Models/GroupInfo.h"

//! Catalog to hold info for GroupProperty creation.

class BA_CORE_API_ GroupInfoCatalog
{
public:
    GroupInfoCatalog();

    GroupInfo groupInfo(const QString& groupType) const;

    bool containsGroup(const QString& groupType) const;

private:
    void addInfo(const GroupInfo& info);
    QVector<GroupInfo> m_groups;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_GROUPINFOCATALOG_H
