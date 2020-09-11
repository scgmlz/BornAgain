// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTuningModel.cpp
//! @brief     Implements class ParameterTuningModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ParameterTuningModel.h"
#include "GUI/coregui/Models/FitParameterHelper.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/SessionModel.h"
#include <QMimeData>

ParameterTuningModel::ParameterTuningModel(QObject* parent) : FilterPropertyProxy(2, parent) {}

Qt::ItemFlags ParameterTuningModel::flags(const QModelIndex& proxyIndex) const
{
    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    QModelIndex sourceIndex = toSourceIndex(proxyIndex);
    if (sourceIndex.isValid()) {
        if (sourceIndex.column() == SessionFlags::ITEM_VALUE)
            result |= Qt::ItemIsEditable;

        const QString modelType = sourceIndex.data(SessionFlags::ModelTypeRole).toString();
        if (modelType == "Parameter" && getParameterItem(proxyIndex))
            result |= Qt::ItemIsDragEnabled;
    }
    return result;
}

QMimeData* ParameterTuningModel::mimeData(const QModelIndexList& proxyIndexes) const
{
    QMimeData* mimeData = new QMimeData();

    for (auto proxyIndex : proxyIndexes) {
        if (ParameterItem* parameterItem = getParameterItem(proxyIndex)) {
            QString path = FitParameterHelper::getParameterItemPath(parameterItem);
            mimeData->setData(SessionXML::LinkMimeType, path.toLatin1());
            break;
        }
    }
    return mimeData;
}

//! Returns ParameterItem from given proxy index

ParameterItem* ParameterTuningModel::getParameterItem(const QModelIndex& proxyIndex) const
{
    SessionModel* sessionModel = dynamic_cast<SessionModel*>(sourceModel());
    ASSERT(sessionModel);

    QModelIndex sourceIndex = toSourceIndex(proxyIndex);
    if (sourceIndex.column() == 0) {
        return dynamic_cast<ParameterItem*>(sessionModel->itemForIndex(sourceIndex));
    }
    return nullptr;
}
