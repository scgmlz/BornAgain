// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyStrategy.cpp
//! @brief     Implements class ComponentProxyStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ComponentProxyStrategy.h"
#include "GUI/coregui/Models/ComponentProxyModel.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentUtils.h"

void ComponentProxyStrategy::onDataChanged(SessionModel* source, ComponentProxyModel* proxy)
{
    buildModelMap(source, proxy);
    proxy->layoutChanged();
}

bool ComponentProxyStrategy::processSourceIndex(const QModelIndex& index)
{
    QPersistentModelIndex sourceIndex = {index};

    SessionItem* item = m_source->itemForIndex(index);

    QString tag;
    if (item->parent())
        tag = item->parent()->tagFromItem(item);

    if (!isPropertyRelated(item))
        return false; // not going to visit non-property items

    if (isNewRootItem(item)) {
        processRootItem(item, sourceIndex);

    } else if (isSubGroup(item)) {
        processSubGroupItem(item, sourceIndex);

    } else if (isGroupChildren(item)) {
        processGroupItem(item, sourceIndex);

    } else {
        processDefaultItem(item, sourceIndex);
    }

    return true;
}

//! Returns true if item is property related to exclude top level items (ParticleLayout, Particle
//! etc from the tree).

bool ComponentProxyStrategy::isPropertyRelated(SessionItem* item)
{
    static QStringList propertyRelated = ComponentUtils::propertyRelatedTypes();

    if (m_sourceRootIndex.isValid() && item->parent()->index() == m_sourceRootIndex
        && item->parent()->modelType() != "GroupProperty")
        return propertyRelated.contains(item->modelType()) ? true : false;

    return true;
}

//! Returns true if item should become new root item.
//! This is used when we want to show single item (Layer, Particle) on top of the tree.

bool ComponentProxyStrategy::isNewRootItem(SessionItem* item)
{
    return item->index() == m_sourceRootIndex;
}

//! Makes SessionItem to become the only one item in a tree.

void ComponentProxyStrategy::processRootItem(SessionItem* item,
                                             const QPersistentModelIndex& sourceIndex)
{
    const int nrows = 0; // invisible root item will contain only single item
    QPersistentModelIndex proxyIndex = createProxyIndex(nrows, sourceIndex.column(), item);
    m_sourceToProxy.insert(sourceIndex, proxyIndex);
    m_proxySourceParent.insert(proxyIndex, QModelIndex()); // new parent will be root
}

//! Returns true if item is a group property which in turn is inside of another group property.

bool ComponentProxyStrategy::isSubGroup(SessionItem* item)
{
    const SessionItem* ancestor = ModelPath::ancestor(item->parent(), "GroupProperty");
    if (item->modelType() == "GroupProperty" && ancestor
        && ancestor->modelType() == "GroupProperty") {
        return true;
    }

    return false;
}

//! Returns true if item is a children/grandchildrent of some group item.

bool ComponentProxyStrategy::isGroupChildren(SessionItem* item)
{
    if (item->parent() && item->parent()->modelType() == "GroupProperty")
        return true;

    if (const SessionItem* ancestor = ModelPath::ancestor(item, "GroupProperty")) {
        if (ancestor != item)
            return true;
    }

    return false;
}

//! All properties of current item of group item

void ComponentProxyStrategy::processGroupItem(SessionItem* item,
                                              const QPersistentModelIndex& sourceIndex)
{
    if (const SessionItem* ancestor = ModelPath::ancestor(item, "GroupProperty")) {
        if (ancestor == item)
            return;

        auto groupItem = dynamic_cast<const GroupItem*>(ancestor);
        if (item->parent() == groupItem->currentItem()) {
            QPersistentModelIndex proxyIndex = createProxyIndex(
                parentVisibleRow(*item), sourceIndex.column(), sourceIndex.internalPointer());

            m_sourceToProxy.insert(sourceIndex, proxyIndex);
            m_proxySourceParent.insert(proxyIndex, groupItem->index());
        }
    }
}

//! Process group property which is inside of other group property.

void ComponentProxyStrategy::processSubGroupItem(SessionItem* item,
                                                 const QPersistentModelIndex& sourceIndex)
{
    if (const SessionItem* ancestor = ModelPath::ancestor(item->parent(), "GroupProperty")) {
        auto groupItem = dynamic_cast<const GroupItem*>(ancestor);

        if (item->parent() == groupItem->currentItem()) {
            QPersistentModelIndex proxyIndex = createProxyIndex(
                parentVisibleRow(*item), sourceIndex.column(), sourceIndex.internalPointer());

            m_sourceToProxy.insert(sourceIndex, proxyIndex);
            m_proxySourceParent.insert(proxyIndex, groupItem->index());
        }
    }
}

void ComponentProxyStrategy::processDefaultItem(SessionItem* item,
                                                const QPersistentModelIndex& sourceIndex)
{
    ASSERT(item);
    if (!item->isVisible())
        return;

    QPersistentModelIndex proxyIndex =
        createProxyIndex(parentVisibleRow(*item), sourceIndex.column(), item);

    m_sourceToProxy.insert(sourceIndex, proxyIndex);

    QPersistentModelIndex sourceParent;
    if (sourceIndex.parent().isValid())
        sourceParent = sourceIndex.parent();

    m_proxySourceParent.insert(proxyIndex, sourceParent);
}

int ComponentProxyStrategy::parentVisibleRow(const SessionItem& item)
{
    int result(-1);

    if (!item.parent() || !item.isVisible())
        return result;

    for (auto child : item.parent()->children()) {
        if (child->isVisible() && isPropertyRelated(child))
            ++result;

        if (&item == child)
            return result;
    }

    return result;
}
