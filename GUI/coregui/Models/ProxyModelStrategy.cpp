// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ProxyModelStrategy.cpp
//! @brief     Implements class ProxyModelStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ProxyModelStrategy.h"
#include "GUI/coregui/Models/ComponentProxyModel.h"
#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/SessionModel.h"

ProxyModelStrategy::ProxyModelStrategy() : m_source(nullptr), m_proxy(nullptr) {}

void ProxyModelStrategy::buildModelMap(SessionModel* source, ComponentProxyModel* proxy)
{
    m_sourceToProxy.clear();
    m_proxySourceParent.clear();
    m_source = source;
    m_proxy = proxy;

    ModelUtils::iterate_if(m_sourceRootIndex, source, [=](const QModelIndex& index) -> bool {
        return processSourceIndex(index);
    });

    // kind of hack since we have to visit col=1 which has QModelIndex() parent
    if (m_sourceRootIndex.isValid())
        processSourceIndex(m_sourceRootIndex.sibling(m_sourceRootIndex.row(), 1));
}

void ProxyModelStrategy::onDataChanged(SessionModel* source, ComponentProxyModel* proxy)
{
    Q_UNUSED(source);
    Q_UNUSED(proxy);
    // we do not expect here change of model layout
}

const ProxyModelStrategy::map_t& ProxyModelStrategy::sourceToProxy()
{
    return m_sourceToProxy;
}

const ProxyModelStrategy::map_t& ProxyModelStrategy::proxySourceParent()
{
    return m_proxySourceParent;
}

void ProxyModelStrategy::setRootIndex(const QModelIndex& sourceRootIndex)
{
    m_sourceRootIndex = QPersistentModelIndex(sourceRootIndex);
}

//! Method to ask proxy to create an index using friendship of ProxyModelStrategy
//! and ComponentProxyModel.

QModelIndex ProxyModelStrategy::createProxyIndex(int nrow, int ncol, void* adata)
{
    ASSERT(m_proxy);
    return m_proxy->createIndex(nrow, ncol, adata);
}

//! Builds one-to-one mapping for source and proxy.

bool IndentityProxyStrategy::processSourceIndex(const QModelIndex& index)
{
    QPersistentModelIndex proxyIndex =
        createProxyIndex(index.row(), index.column(), index.internalPointer());
    m_sourceToProxy.insert(QPersistentModelIndex(index), proxyIndex);

    QPersistentModelIndex sourceParent;
    if (index.parent().isValid())
        sourceParent = index.parent();

    m_proxySourceParent.insert(proxyIndex, sourceParent);

    return true;
}
