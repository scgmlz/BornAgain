// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyModel.cpp
//! @brief     Implements class ComponentProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ComponentProxyModel.h"
#include "GUI/coregui/Models/ComponentProxyStrategy.h"
#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include <QSet>
#include <functional>

ComponentProxyModel::ComponentProxyModel(QObject* parent)
    : QAbstractProxyModel(parent), m_model(nullptr)
      //    , m_proxyStrategy(new IndentityProxyStrategy)
      ,
      m_proxyStrategy(new ComponentProxyStrategy)
{
}

void ComponentProxyModel::setSessionModel(SessionModel* model)
{
    beginResetModel();

    if (sourceModel()) {
        disconnect(sourceModel(), &QAbstractItemModel::dataChanged, this,
                   &ComponentProxyModel::sourceDataChanged);
        disconnect(sourceModel(), &QAbstractItemModel::rowsInserted, this,
                   &ComponentProxyModel::sourceRowsInserted);
        disconnect(sourceModel(), &QAbstractItemModel::rowsRemoved, this,
                   &ComponentProxyModel::sourceRowsRemoved);
    }

    QAbstractProxyModel::setSourceModel(model);

    if (sourceModel()) {
        connect(sourceModel(), &QAbstractItemModel::dataChanged, this,
                &ComponentProxyModel::sourceDataChanged);
        connect(sourceModel(), &QAbstractItemModel::rowsInserted, this,
                &ComponentProxyModel::sourceRowsInserted);
        connect(sourceModel(), &QAbstractItemModel::rowsRemoved, this,
                &ComponentProxyModel::sourceRowsRemoved);
    }

    endResetModel();

    m_model = model;
    buildModelMap();
}

void ComponentProxyModel::setRootIndex(const QModelIndex& sourceRootIndex)
{
    m_proxyStrategy->setRootIndex(sourceRootIndex);
    buildModelMap();
}

void ComponentProxyModel::setProxyStrategy(ProxyModelStrategy* strategy)
{
    m_proxyStrategy.reset(strategy);
    buildModelMap();
}

QModelIndex ComponentProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
    if (!proxyIndex.isValid())
        return QModelIndex();

    return m_proxyStrategy->sourceToProxy().key(proxyIndex);
}

QModelIndex ComponentProxyModel::mapFromSource(const QModelIndex& sourceIndex) const
{
    if (!sourceIndex.isValid())
        return QModelIndex();

    return m_proxyStrategy->sourceToProxy().value(sourceIndex);
}

QModelIndex ComponentProxyModel::index(int row, int column, const QModelIndex& parent) const
{
    QModelIndex sourceParent;
    if (parent.isValid())
        sourceParent = mapToSource(parent);

    QMapIterator<QPersistentModelIndex, QPersistentModelIndex> it(
        m_proxyStrategy->proxySourceParent());
    while (it.hasNext()) {
        it.next();
        if (it.value() == sourceParent && it.key().row() == row && it.key().column() == column)
            return it.key();
    }
    return QModelIndex();
}

QModelIndex ComponentProxyModel::parent(const QModelIndex& child) const
{
    QModelIndex sourceParent = m_proxyStrategy->proxySourceParent().value(child);
    if (sourceParent.isValid())
        return mapFromSource(sourceParent);

    return QModelIndex();
}

int ComponentProxyModel::rowCount(const QModelIndex& parent) const
{
    QModelIndex sourceParent;
    if (parent.isValid())
        sourceParent = mapToSource(parent);
    QMapIterator<QPersistentModelIndex, QPersistentModelIndex> it(
        m_proxyStrategy->proxySourceParent());

    QSet<int> rows;
    while (it.hasNext()) {
        it.next();
        if (it.value() == sourceParent)
            rows.insert(it.key().row());
    }
    return rows.size();
}

int ComponentProxyModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    return SessionFlags::MAX_COLUMNS;
}

bool ComponentProxyModel::hasChildren(const QModelIndex& parent) const
{
    QModelIndex source_parent = mapToSource(parent);
    if (parent.isValid() && !source_parent.isValid())
        return false;

    return rowCount(parent) != 0;
}

void ComponentProxyModel::sourceDataChanged(const QModelIndex& topLeft,
                                            const QModelIndex& bottomRight,
                                            const QVector<int>& roles)
{
    ASSERT(topLeft.isValid() ? topLeft.model() == sourceModel() : true);
    ASSERT(bottomRight.isValid() ? bottomRight.model() == sourceModel() : true);

    if (SessionItem* item = m_model->itemForIndex(topLeft)) {
        if (item->modelType() == "GroupProperty")
            updateModelMap();
    }
    dataChanged(mapFromSource(topLeft), mapFromSource(bottomRight), roles);
}

void ComponentProxyModel::sourceRowsInserted(const QModelIndex& parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
    buildModelMap();
}

void ComponentProxyModel::sourceRowsRemoved(const QModelIndex& parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
    buildModelMap();
}

//! Main method to build the map of persistent indeses.

void ComponentProxyModel::buildModelMap()
{
    if (!m_model)
        return;
    m_proxyStrategy->buildModelMap(m_model, this);
    layoutChanged();
}

void ComponentProxyModel::updateModelMap()
{
    m_proxyStrategy->onDataChanged(m_model, this);
}
