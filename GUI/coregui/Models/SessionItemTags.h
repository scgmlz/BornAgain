// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemTags.h
//! @brief     Defines class SessionItemTags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMTAGS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMTAGS_H

#include "Wrap/WinDllMacros.h"
#include <QString>
#include <QStringList>
#include <QVector>

//! Holds all tag info for SessionItem.

class BA_CORE_API_ SessionItemTags
{
public:
    bool registerTag(const QString& name, int min, int max, const QStringList& modelTypes);

    bool isValid(const QString& tagName, const QString& modelType = "") const;

    QStringList modelTypesForTag(const QString& tagName) const;

    int tagStartIndex(const QString& tagName) const;

    int indexFromTagRow(const QString& tagName, int row) const;
    int insertIndexFromTagRow(const QString& tagName, int row);

    QString tagFromIndex(int index) const;

    int childCount(const QString& tagName);
    int childMax(const QString& tagName);

    void addChild(const QString& tagName);
    void removeChild(const QString& tagName);

    bool isSingleItemTag(const QString& tagName);

    bool maximumReached(const QString& tagName) const;

private:
    struct TagInfo {
        QString name;
        int min{0};
        int max{-1};
        int childCount{0};
        QStringList modelTypes;
    };

    TagInfo& tagInfo(const QString& tagName);
    const TagInfo& tagInfo(const QString& tagName) const;

    QVector<TagInfo> m_tags;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMTAGS_H
