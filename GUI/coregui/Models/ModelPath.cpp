// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelPath.cpp
//! @brief     Implements class ModelPath
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/SessionModel.h"

QString ModelPath::getPathFromIndex(const QModelIndex& index)
{
    if (index.isValid()) {
        QStringList namePath;
        QModelIndex cur = index;
        while (cur.isValid()) {
            namePath << cur.data().toString();
            cur = cur.parent();
        }
        std::reverse(namePath.begin(), namePath.end());
        return namePath.join("/");
    }
    return "";
}

// TODO cover with unit tests and simplify

QModelIndex ModelPath::getIndexFromPath(const SessionModel* model, const QString& path)
{
    if (model) {
        QStringList parts = path.split("/");
        SessionItem* t = model->rootItem();
        for (int i = 0; i < parts.length(); i++) {
            if (t->modelType() == "JobItem" && parts[i] == "GISASInstrument") {
                t = t->getItem(JobItem::T_INSTRUMENT);
                continue;
            }
            for (int j = 0; j < t->numberOfChildren(); j++) {
                if (t->childAt(j)->itemName() == parts[i]) {
                    t = t->childAt(j);
                    break;
                }
            }
        }
        return t->index();
    }
    return QModelIndex();
}

//! returns an item from relative path wrt to given parent

SessionItem* ModelPath::getItemFromPath(const QString& relPath, const SessionItem* parent)
{
    ASSERT(parent);
    QString fullPath = getPathFromIndex(parent->index()) + "/" + relPath;
    return parent->model()->itemForIndex(ModelPath::getIndexFromPath(parent->model(), fullPath));
}

//! Iterates through all the model and returns true if item is found. This is to

bool ModelPath::isValidItem(SessionModel* model, SessionItem* item, const QModelIndex& parent)
{
    for (int i_row = 0; i_row < model->rowCount(parent); ++i_row) {
        QModelIndex index = model->index(i_row, 0, parent);
        SessionItem* curr = model->itemForIndex(index);
        if (curr == item)
            return true;

        bool isvalid = isValidItem(model, item, index);
        if (isvalid)
            return isvalid;
    }
    return false;
}

//! Returns ancestor of given modelType for given item.
//! For example, returns corresponding jobItem owning ParameterItem via ParameterContainer.

const SessionItem* ModelPath::ancestor(const SessionItem* item, const QString& requiredModelType)
{
    const SessionItem* cur = item;
    while (cur && cur->modelType() != requiredModelType)
        cur = cur->parent();

    return cur;
}

//! Returns translation of item path to domain name

QString ModelPath::itemPathTranslation(const SessionItem& item, const SessionItem* topItem)
{
    QStringList pathList;
    const SessionItem* current(&item);
    while (current && current != topItem) {
        pathList = current->translateList(pathList);
        current = current->parent();
    }
    std::reverse(pathList.begin(), pathList.end());
    return pathList.join("/");
}
