// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ProxyModelStrategy.h
//! @brief     Defines class ProxyModelStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PROXYMODELSTRATEGY_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PROXYMODELSTRATEGY_H

#include "Wrap/WinDllMacros.h"
#include <QPersistentModelIndex>

class SessionModel;
class ComponentProxyModel;
class SessionItem;

//! Base class for proxy strategies in ComponentProxyModel.

class BA_CORE_API_ ProxyModelStrategy
{
public:
    using map_t = QMap<QPersistentModelIndex, QPersistentModelIndex>;

    ProxyModelStrategy();
    virtual ~ProxyModelStrategy() = default;

    void buildModelMap(SessionModel* source, ComponentProxyModel* proxy);
    virtual void onDataChanged(SessionModel* source, ComponentProxyModel* proxy);

    const map_t& sourceToProxy();
    const map_t& proxySourceParent();

    void setRootIndex(const QModelIndex& sourceRootIndex);

protected:
    QModelIndex createProxyIndex(int nrow, int ncol, void* adata);
    virtual bool processSourceIndex(const QModelIndex& index) = 0;

    //!< Mapping of proxy model indices to indices in source model
    QMap<QPersistentModelIndex, QPersistentModelIndex> m_sourceToProxy;
    //!< Mapping of proxy model indices to indices of parent in source model
    QMap<QPersistentModelIndex, QPersistentModelIndex> m_proxySourceParent;

    QPersistentModelIndex m_sourceRootIndex;
    SessionModel* m_source;
    ComponentProxyModel* m_proxy;
};

//! Strategy for ComponentProxyModel which makes it identical to source model.

class BA_CORE_API_ IndentityProxyStrategy : public ProxyModelStrategy
{
protected:
    bool processSourceIndex(const QModelIndex& index);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PROXYMODELSTRATEGY_H
