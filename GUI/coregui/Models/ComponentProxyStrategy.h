// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyStrategy.h
//! @brief     Defines class ComponentProxyStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_COMPONENTPROXYSTRATEGY_H
#define BORNAGAIN_GUI_COREGUI_MODELS_COMPONENTPROXYSTRATEGY_H

#include "GUI/coregui/Models/ProxyModelStrategy.h"

//! Strategy for ComponentProxyModel which hides extra level of GroupProperty.

class BA_CORE_API_ ComponentProxyStrategy : public ProxyModelStrategy
{
public:
    void onDataChanged(SessionModel* source, ComponentProxyModel* proxy);

protected:
    bool processSourceIndex(const QModelIndex& index);

private:
    bool isPropertyRelated(SessionItem* item);
    bool isNewRootItem(SessionItem* item);
    void processRootItem(SessionItem* item, const QPersistentModelIndex& sourceIndex);
    bool isSubGroup(SessionItem* item);
    bool isGroupChildren(SessionItem* item);
    void processGroupItem(SessionItem* item, const QPersistentModelIndex& sourceIndex);
    void processSubGroupItem(SessionItem* item, const QPersistentModelIndex& sourceIndex);
    void processDefaultItem(SessionItem* item, const QPersistentModelIndex& sourceIndex);

    int parentVisibleRow(const SessionItem& item);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_COMPONENTPROXYSTRATEGY_H
