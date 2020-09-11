// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfo.h
//! @brief     Defines class GroupInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_GROUPINFO_H
#define BORNAGAIN_GUI_COREGUI_MODELS_GROUPINFO_H

#include "Wrap/WinDllMacros.h"
#include <QString>
#include <QStringList>
#include <QVector>

//! Defines info for GroupProperty, i.e. collection of model types, their labels and
//! the name of default item's modelType.

class BA_CORE_API_ GroupInfo
{
public:
    explicit GroupInfo(const QString& groupType = "", bool is_sorted = true);

    void add(const QString& itemType, const QString& itemLabel);

    QString defaultType() const;
    void setDefaultType(const QString& modelType);

    QString groupType() const;

    QStringList itemTypes() const;

    QStringList itemLabels() const;

    bool isValid();

private:
    struct TypeAndLabel {
        QString m_itemType;
        QString m_itemLabel;
    };

    bool containsType(const QString& itemType) const;

    //!< Default model type for given group (i.e. FFCylinder for formfactor group)
    QString m_defaultItemType;
    //!< Unique group name for GroupInfoCatalog
    QString m_groupType;
    //!< Info will be sorted if true, otherwise order of insertion will be preserved
    bool is_sorted;
    QVector<TypeAndLabel> m_info;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_GROUPINFO_H
