// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelUtils.cpp
//! @brief     Implements ModelUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include <QAbstractItemModel>
#include <QModelIndex>

QStringList ModelUtils::topItemNames(SessionModel* model, const QString& modelType)
{
    QStringList result;

    for (auto item : model->topItems())
        if (modelType.isEmpty())
            result.append(item->itemName());
        else if (modelType == item->modelType())
            result.append(item->itemName());

    return result;
}

void ModelUtils::iterate(const QModelIndex& index, const QAbstractItemModel* model,
                         const std::function<void(const QModelIndex&)>& fun)
{
    if (index.isValid())
        fun(index);

    if (!model->hasChildren(index))
        return;

    for (int i = 0; i < model->rowCount(index); ++i)
        for (int j = 0; j < model->columnCount(index); ++j)
            iterate(model->index(i, j, index), model, fun);
}

void ModelUtils::iterate_if(const QModelIndex& index, const QAbstractItemModel* model,
                            const std::function<bool(const QModelIndex&)>& fun)
{
    bool proceed_with_children(true);
    if (index.isValid())
        proceed_with_children = fun(index);

    if (!model->hasChildren(index) || !proceed_with_children)
        return;

    for (int i = 0; i < model->rowCount(index); ++i)
        for (int j = 0; j < model->columnCount(index); ++j)
            iterate_if(model->index(i, j, index), model, fun);
}
