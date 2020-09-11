// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelMapper.cpp
//! @brief     Implements class ModelMapper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SessionModel.h"

ModelMapper::ModelMapper(QObject* parent)
    : QObject(parent), m_active(true), m_model(nullptr), m_item(nullptr)
{
}

void ModelMapper::setItem(SessionItem* item)
{
    if (item) {
        m_item = item;
        setModel(item->model());
    }
}

void ModelMapper::setOnValueChange(std::function<void(void)> f, const void* caller)
{
    m_onValueChange.push_back(call_t(f, caller));
}

void ModelMapper::setOnPropertyChange(std::function<void(QString)> f, const void* caller)
{
    auto ff = [=](SessionItem* /*item*/, const QString& property) { f(property); };
    m_onPropertyChange.push_back(call_item_str_t(ff, caller));
}

void ModelMapper::setOnPropertyChange(std::function<void(SessionItem*, QString)> f,
                                      const void* caller)
{
    m_onPropertyChange.push_back(call_item_str_t(f, caller));
}

//! Calls back on child property change, report childItem and property name.

void ModelMapper::setOnChildPropertyChange(std::function<void(SessionItem*, QString)> f,
                                           const void* caller)
{
    m_onChildPropertyChange.push_back(call_item_str_t(f, caller));
}

//! Calls back when parent has changed, reports newParent.
//! If newParent=0, the item is about being to be removed from children. Method parent()
//! will still report old parent.
//! If newParent!=0, it is just the same as parent().

void ModelMapper::setOnParentChange(std::function<void(SessionItem*)> f, const void* caller)
{
    m_onParentChange.push_back(call_item_t(f, caller));
}

//! Calls back when number of children has changed, reports newChild.
//! newChild == nullptr denotes the case when number of children has decreased.

void ModelMapper::setOnChildrenChange(std::function<void(SessionItem*)> f, const void* caller)
{
    m_onChildrenChange.push_back(call_item_t(f, caller));
}

void ModelMapper::setOnSiblingsChange(std::function<void()> f, const void* caller)
{
    m_onSiblingsChange.push_back(call_t(f, caller));
}

//! Calls back on any change in children (number of children or their properties),
//! reports childItem.
//! childItem == nullptr denotes the case when child was removed.

void ModelMapper::setOnAnyChildChange(std::function<void(SessionItem*)> f, const void* caller)
{
    m_onAnyChildChange.push_back(call_item_t(f, caller));
}

void ModelMapper::setOnItemDestroy(std::function<void(SessionItem*)> f, const void* caller)
{
    m_onItemDestroy.push_back(call_item_t(f, caller));
}

void ModelMapper::setOnAboutToRemoveChild(std::function<void(SessionItem*)> f, const void* caller)
{
    m_onAboutToRemoveChild.push_back(call_item_t(f, caller));
}

//! Cancells all subscribtion of given caller
void ModelMapper::unsubscribe(const void* caller)
{
    clean_container(m_onValueChange, caller);
    clean_container(m_onPropertyChange, caller);
    clean_container(m_onChildPropertyChange, caller);
    clean_container(m_onParentChange, caller);
    clean_container(m_onChildrenChange, caller);
    clean_container(m_onSiblingsChange, caller);
    clean_container(m_onAnyChildChange, caller);
    clean_container(m_onItemDestroy, caller);
    clean_container(m_onAboutToRemoveChild, caller);
}

void ModelMapper::setModel(SessionModel* model)
{
    if (m_model) {
        disconnect(m_model, &SessionModel::dataChanged, this, &ModelMapper::onDataChanged);
        disconnect(m_model, &SessionModel::rowsInserted, this, &ModelMapper::onRowsInserted);
        disconnect(m_model, &SessionModel::rowsAboutToBeRemoved, this,
                   &ModelMapper::onBeginRemoveRows);
        disconnect(m_model, &SessionModel::rowsRemoved, this, &ModelMapper::onRowRemoved);
    }
    m_model = model;
    if (m_model) {
        connect(m_model, &SessionModel::dataChanged, this, &ModelMapper::onDataChanged);
        connect(m_model, &SessionModel::rowsInserted, this, &ModelMapper::onRowsInserted);
        connect(m_model, &SessionModel::rowsAboutToBeRemoved, this,
                &ModelMapper::onBeginRemoveRows);
        connect(m_model, &SessionModel::rowsRemoved, this, &ModelMapper::onRowRemoved);
    }
}

int ModelMapper::nestlingDepth(SessionItem* item, int level)
{
    if (item == nullptr || item == m_model->rootItem())
        return -1;
    if (item == m_item)
        return level;

    return nestlingDepth(item->parent(), level + 1);
}

void ModelMapper::callOnValueChange()
{
    if (m_active && m_onValueChange.size() > 0)
        for (auto f : m_onValueChange)
            f.first();
}

void ModelMapper::callOnPropertyChange(const QString& name)
{
    if (m_active)
        for (auto f : m_onPropertyChange)
            f.first(m_item, name);
}

void ModelMapper::callOnChildPropertyChange(SessionItem* item, const QString& name)
{
    if (m_active)
        for (auto f : m_onChildPropertyChange)
            f.first(item, name);
}

void ModelMapper::callOnParentChange(SessionItem* new_parent)
{
    if (m_active)
        for (auto f : m_onParentChange)
            f.first(new_parent);
}

void ModelMapper::callOnChildrenChange(SessionItem* item)
{
    if (m_active)
        for (auto f : m_onChildrenChange)
            f.first(item);
}

void ModelMapper::callOnSiblingsChange()
{
    if (m_active)
        for (auto f : m_onSiblingsChange)
            f.first();
}

void ModelMapper::callOnAnyChildChange(SessionItem* item)
{
    if (m_active)
        for (auto f : m_onAnyChildChange)
            f.first(item);
}

void ModelMapper::callOnAboutToRemoveChild(SessionItem* item)
{
    if (m_active)
        for (auto f : m_onAboutToRemoveChild)
            f.first(item);
}

//! Notifies subscribers if an item owning given mapper is about to be destroyed
void ModelMapper::callOnItemDestroy()
{
    if (m_active)
        for (auto f : m_onItemDestroy)
            f.first(m_item);
}

void ModelMapper::clearMapper()
{
    m_item = nullptr;
    setModel(nullptr);
    m_onValueChange.clear();
    m_onPropertyChange.clear();
    m_onChildPropertyChange.clear();
    m_onParentChange.clear();
    m_onChildrenChange.clear();
    m_onSiblingsChange.clear();
    m_onAnyChildChange.clear();
    m_onItemDestroy.clear();
    m_onAboutToRemoveChild.clear();
}

void ModelMapper::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                                const QVector<int>& /*roles*/)
{
    if (topLeft.parent() != bottomRight.parent())
        return; // range must be from the same parent

    SessionItem* item = m_model->itemForIndex(topLeft);

    int nestling = nestlingDepth(item);
    if (nestling == 0)
        callOnValueChange();

    if (nestling == 1) {
        // something happened with our children
        if (SessionItem* item = m_model->itemForIndex(topLeft)) {
            // only care f
            const QString tag = m_item->tagFromItem(item);
            if (!tag.isEmpty()) {
                callOnPropertyChange(tag);
            }
        }
    }
    if (nestling > 1) {
        if (SessionItem* parent = item->parent()) {
            const QString tag = parent->tagFromItem(item);
            if (!tag.isEmpty()) {
                callOnChildPropertyChange(parent, tag);
            }
        }
    }
    if (nestling > 0)
        callOnAnyChildChange(item);
}

void ModelMapper::onRowsInserted(const QModelIndex& parent, int first, int /*last*/)
{
    SessionItem* newChild = m_model->itemForIndex(m_model->index(first, 0, parent));

    int nestling = nestlingDepth(newChild);

    if (newChild)
        if (m_item == newChild)
            callOnParentChange(m_model->itemForIndex(parent));
    if (nestling == 1)
        callOnChildrenChange(newChild);
    if (SessionItem* parent = newChild->parent()) {
        QVector<SessionItem*> items = parent->getChildrenOfType(newChild->modelType());
        for (auto sibling : items)
            if (m_item == sibling)
                callOnSiblingsChange();
    }
    if (nestling > 0) {
        callOnAnyChildChange(newChild);
    }
}

void ModelMapper::onBeginRemoveRows(const QModelIndex& parent, int first, int /*last*/)
{
    SessionItem* oldChild = m_model->itemForIndex(m_model->index(first, 0, parent));

    int nestling = nestlingDepth(m_model->itemForIndex(parent));

    if (oldChild) {
        if (m_item == oldChild)
            callOnParentChange(nullptr);
        if (nestling == 0)
            callOnAboutToRemoveChild(oldChild);
    }

    if (m_item == oldChild)
        m_aboutToDelete = m_model->index(first, 0, parent);
}

void ModelMapper::onRowRemoved(const QModelIndex& parent, int first, int /*last*/)
{
    int nestling = nestlingDepth(m_model->itemForIndex(parent));

    if (nestling >= 0 || m_model->itemForIndex(parent) == m_item->parent()) {
        callOnAnyChildChange(nullptr);
        callOnSiblingsChange();
    }
    if (nestling == 0)
        callOnChildrenChange(nullptr);

    if (m_aboutToDelete.isValid() && m_aboutToDelete == m_model->index(first, 0, parent))
        clearMapper();
}
