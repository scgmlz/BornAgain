// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FilterPropertyProxy.cpp
//! @brief     Implements class FilterPropertyProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FilterPropertyProxy.h"
#include "GUI/coregui/Models/SessionModel.h"

int FilterPropertyProxy::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_columns;
}

QModelIndex FilterPropertyProxy::toSourceIndex(QModelIndex index)
{
    FilterPropertyProxy* proxy =
        dynamic_cast<FilterPropertyProxy*>(const_cast<QAbstractItemModel*>(index.model()));
    if (proxy)
        return proxy->mapToSource(index);
    return index;
}

bool FilterPropertyProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
    if (!sourceParent.isValid())
        return true;
    const QString modelType = index.data(SessionFlags::ModelTypeRole).toString();
    if (modelType == "Property" || modelType == "GroupProperty" || modelType == "Vector")
        return false;

    return true; //! sourceModel()->data(index, Qt::DisplayRole).isValid();
}
